#include "flameshotdaemon.h"

#include "abstractlogger.h"
#include "confighandler.h"
#include "flameshot.h"
#include "pinwidget.h"
#include "screenshotsaver.h"
#include "src/utils/globalvalues.h"
#include "src/widgets/capture/capturewidget.h"
#include "src/widgets/trayicon.h"
#include <QApplication>
#include <QClipboard>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QPixmap>
#include <QRect>


#ifdef Q_OS_WIN
#include "src/core/globalshortcutfilter.h"
#endif

/**
 * @brief A way of accessing the flameshot daemon both from the daemon itself,
 * and from subcommands.
 *
 * The daemon is necessary in order to:
 * - Host the system tray,
 * - Listen for hotkey events that will trigger captures,
 * - Host pinned screenshot widgets,
 * - Host the clipboard on X11, where the clipboard gets lost once flameshot
 *   quits.
 *
 * If the `autoCloseIdleDaemon` option is true, the daemon will close as soon as
 * it is not needed to host pinned screenshots and the clipboard. On Windows,
 * this option is disabled and the daemon always persists, because the system
 * tray is currently the only way to interact with flameshot there.
 *
 * Both the daemon and non-daemon flameshot processes use the same public API,
 * which is implemented as static methods. In the daemon process, this class is
 * also instantiated as a singleton, so it can listen to D-Bus calls via the
 * sigslot mechanism. The instantiation is done by calling `start` (this must be
 * done only in the daemon process). Any instance (as opposed to static) members
 * can only be used if the current process is a daemon.
 *
 * @note The daemon will be automatically launched where necessary, via D-Bus.
 * This applies only to Linux.
 */
FireshotDaemon::FireshotDaemon()
  : m_persist(false)
  , m_hostingClipboard(false)
  , m_clipboardSignalBlocked(false)
  , m_trayIcon(nullptr)
{
    connect(
      QApplication::clipboard(), &QClipboard::dataChanged, this, [this]() {
          if (!m_hostingClipboard || m_clipboardSignalBlocked) {
              m_clipboardSignalBlocked = false;
              return;
          }
          m_hostingClipboard = false;
          quitIfIdle();
      });
#ifdef Q_OS_WIN
    m_persist = true;
#else
    m_persist = !ConfigHandler().autoCloseIdleDaemon();
    connect(ConfigHandler::getInstance(),
            &ConfigHandler::fileChanged,
            this,
            [this]() {
                ConfigHandler config;
                enableTrayIcon(!config.disabledTrayIcon());
                m_persist = !config.autoCloseIdleDaemon();
            });
#endif

}

void FireshotDaemon::start()
{
    if (!m_instance) {
        m_instance = new FireshotDaemon();
        // Tray icon needs FireshotDaemon::instance() to be non-null
        m_instance->initTrayIcon();
        qApp->setQuitOnLastWindowClosed(false);
    }
}

void FireshotDaemon::createPin(const QPixmap& capture, QRect geometry)
{
    if (instance()) {
        instance()->attachPin(capture, geometry);
        return;
    }

}

void FireshotDaemon::copyToClipboard(const QPixmap& capture)
{
    if (instance()) {
        instance()->attachScreenshotToClipboard(capture);
        return;
    }

}

void FireshotDaemon::copyToClipboard(const QString& text,
                                     const QString& notification)
{
    if (instance()) {
        instance()->attachTextToClipboard(text, notification);
        return;
    }
}

/**
 * @brief Is this instance of flameshot hosting any windows as a daemon?
 */
bool FireshotDaemon::isThisInstanceHostingWidgets()
{
    return instance() && !instance()->m_widgets.isEmpty();
}

void FireshotDaemon::sendTrayNotification(const QString& text,
                                          const QString& title,
                                          const int timeout)
{
    if (m_trayIcon) {
        m_trayIcon->showMessage(
          title, text, QIcon(GlobalValues::iconPath()), timeout);
    }
}

/**
 * @brief Return the daemon instance.
 *
 * If this instance of flameshot is the daemon, a singleton instance of
 * `FireshotDaemon` is returned. As a side effect`start` will called if it
 * wasn't called earlier. If this instance of flameshot is not the daemon,
 * `nullptr` is returned.
 *
 * This strategy is used because the daemon needs to receive signals from D-Bus,
 * for which an instance of a `QObject` is required. The singleton serves as
 * that object.
 */
FireshotDaemon* FireshotDaemon::instance()
{
    // Because we don't use DBus on MacOS, each instance of flameshot is its own
    // mini-daemon, responsible for hosting its own persistent widgets (e.g.
    // pins).
    return m_instance;
}

/**
 * @brief Quit the daemon if it has nothing to do and the 'persist' flag is not
 * set.
 */
void FireshotDaemon::quitIfIdle()
{
    if (m_persist) {
        return;
    }
    if (!m_hostingClipboard && m_widgets.isEmpty()) {
        qApp->exit(0);
    }
}

// SERVICE METHODS

void FireshotDaemon::attachPin(const QPixmap& pixmap, QRect geometry)
{
    auto* pinWidget = new PinWidget(pixmap, geometry);
    m_widgets.append(pinWidget);
    connect(pinWidget, &QObject::destroyed, this, [=]() {
        m_widgets.removeOne(pinWidget);
        quitIfIdle();
    });

    pinWidget->show();
    pinWidget->activateWindow();
}

void FireshotDaemon::attachScreenshotToClipboard(const QPixmap& pixmap)
{
    m_hostingClipboard = true;
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->blockSignals(true);
    // This variable is necessary because the signal doesn't get blocked on
    // windows for some reason
    m_clipboardSignalBlocked = true;
    saveToClipboard(pixmap);
    clipboard->blockSignals(false);
}

void FireshotDaemon::attachTextToClipboard(const QString& text,
                                           const QString& notification)
{
    // Must send notification before clipboard modification on linux
    if (!notification.isEmpty()) {
        AbstractLogger::info() << notification;
    }

    m_hostingClipboard = true;
    QClipboard* clipboard = QApplication::clipboard();

    clipboard->blockSignals(true);
    // This variable is necessary because the signal doesn't get blocked on
    // windows for some reason
    m_clipboardSignalBlocked = true;
    clipboard->setText(text);
    clipboard->blockSignals(false);
}

void FireshotDaemon::initTrayIcon()
{
#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    if (!ConfigHandler().disabledTrayIcon()) {
        enableTrayIcon(true);
    }
#elif defined(Q_OS_WIN)
    enableTrayIcon(true);

    GlobalShortcutFilter* nativeFilter = new GlobalShortcutFilter(this);
    qApp->installNativeEventFilter(nativeFilter);
    connect(nativeFilter, &GlobalShortcutFilter::printPressed, this, [this]() {
        Flameshot::instance()->gui();
    });
#endif
}

void FireshotDaemon::enableTrayIcon(bool enable)
{
    if (enable) {
        if (m_trayIcon == nullptr) {
            m_trayIcon = new TrayIcon();
        } else {
            m_trayIcon->show();
            return;
        }
    } else if (m_trayIcon) {
        m_trayIcon->hide();
    }
}


void FireshotDaemon::checkDBusConnection(const QDBusConnection& connection)
{
    if (!connection.isConnected()) {
        AbstractLogger::error() << tr("Unable to connect via DBus");
        qApp->exit(1);
    }
}

void FireshotDaemon::call(const QDBusMessage& m)
{
    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    checkDBusConnection(sessionBus);
    sessionBus.call(m);
}

// STATIC ATTRIBUTES
FireshotDaemon* FireshotDaemon::m_instance = nullptr;
