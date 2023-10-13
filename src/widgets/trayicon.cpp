#include "trayicon.h"

#include "src/core/flameshot.h"
#include "src/utils/globalvalues.h"

#include "src/utils/confighandler.h"
#include <QApplication>
#include <QMenu>
#include <QTimer>
#include <QUrl>

#include <QDebug>

TrayIcon::TrayIcon(QObject* parent)
  : QSystemTrayIcon(parent)
{
    initMenu();

    setToolTip(QStringLiteral("FireShot"));

    setContextMenu(m_menu);
    QIcon icon =
      QIcon::fromTheme("flameshot-tray", QIcon(GlobalValues::iconPathPNG()));
    setIcon(icon);


    connect(this, &TrayIcon::activated, this, [this](ActivationReason r) {
        qDebug() << r ;
        if (r == Trigger) {
            startGuiCapture();
        }
    });

#ifdef Q_OS_WIN
    // Ensure proper removal of tray icon when program quits on Windows.
    connect(qApp, &QCoreApplication::aboutToQuit, this, &TrayIcon::hide);
#endif

    show(); // TODO needed?

    if (ConfigHandler().showStartupLaunchMessage()) {
        showMessage(
          "Flameshot",
          QObject::tr(
            "Hello, I'm here! Click icon in the tray to take a screenshot or "
            "click with a right button to see more options."),
          icon,
          3000);
    }

    connect(ConfigHandler::getInstance(),
            &ConfigHandler::fileChanged,
            this,
            [this]() {});
}

TrayIcon::~TrayIcon()
{
    delete m_menu;
}

void TrayIcon::initMenu()
{
    m_menu = new QMenu();

    auto* captureAction = new QAction(tr("&Take Screenshot"), this);
    connect(captureAction, &QAction::triggered, this, [this]() {
        // Wait 400 ms to hide the QMenu
        QTimer::singleShot(400, this, [this]() {
            startGuiCapture();
        });
    });
    auto* launcherAction = new QAction(tr("&Open Launcher"), this);
    connect(launcherAction,
            &QAction::triggered,
            Flameshot::instance(),
            &Flameshot::launcher);
    auto* configAction = new QAction(tr("&Configuration"), this);
    connect(configAction,
            &QAction::triggered,
            Flameshot::instance(),
            &Flameshot::config);
    auto* infoAction = new QAction(tr("&About"), this);
    connect(
      infoAction, &QAction::triggered, Flameshot::instance(), &Flameshot::info);


    QAction* quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    // recent screenshots
    QAction* recentAction = new QAction(tr("&Latest Uploads"), this);
    connect(recentAction,
            &QAction::triggered,
            Flameshot::instance(),
            &Flameshot::history);

    m_menu->addAction(captureAction);
    m_menu->addAction(launcherAction);
    m_menu->addSeparator();
    m_menu->addAction(recentAction);
    m_menu->addSeparator();
    m_menu->addAction(configAction);
    m_menu->addSeparator();

    m_menu->addAction(infoAction);
    m_menu->addSeparator();
    m_menu->addAction(quitAction);
}


void TrayIcon::startGuiCapture()
{
    Flameshot::instance()->gui();

}
