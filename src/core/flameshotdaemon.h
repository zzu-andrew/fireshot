#pragma once

#include <QByteArray>
#include <QObject>
#include <QtDBus/QDBusAbstractAdaptor>

class QPixmap;
class QRect;
class QDBusMessage;
class QDBusConnection;
class TrayIcon;
class CaptureWidget;

class FlameshotDaemon : public QObject
{
    Q_OBJECT
public:
    static void start();
    static FlameshotDaemon* instance();
    static void createPin(const QPixmap& capture, QRect geometry);
    static void copyToClipboard(const QPixmap& capture);
    static void copyToClipboard(const QString& text,
                                const QString& notification = "");
    static bool isThisInstanceHostingWidgets();

    void sendTrayNotification(
      const QString& text,
      const QString& title = QStringLiteral("Flameshot Info"),
      const int timeout = 5000);

private:
    FlameshotDaemon();
    void quitIfIdle();
    void attachPin(const QPixmap& pixmap, QRect geometry);
    void attachScreenshotToClipboard(const QPixmap& pixmap);

    void attachTextToClipboard(const QString& text,
                               const QString& notification);

    void initTrayIcon();
    void enableTrayIcon(bool enable);

private:
    static void checkDBusConnection(const QDBusConnection& connection);
    static void call(const QDBusMessage& m);

    bool m_persist;
    bool m_hostingClipboard;
    bool m_clipboardSignalBlocked;
    QList<QWidget*> m_widgets;
    TrayIcon* m_trayIcon;


    static FlameshotDaemon* m_instance;
};
