#include <QSystemTrayIcon>

#pragma once

class QAction;

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject* parent = nullptr);
    virtual ~TrayIcon();


private:
    void initTrayIcon();
    void initMenu();

    void startGuiCapture();

    QMenu* m_menu;
};
