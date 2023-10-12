#include <QApplication>
#include <QPushButton>
#include <QSystemTrayIcon>

#include "utils/spdlog_wrapper.h"
#include "fireshot.h"


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    // close all windows not close app
    QGuiApplication::setQuitOnLastWindowClosed(false);
    spdlog::SpdlogInit("FireShot", "logs/log.log", 23, 57, 0, 0);
    SPD_TRACE("start");

    // 查看系统是否支持托盘功能
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        SPD_ERROR("system tray disabled");
        return 1;
    }

    FireShot fireShot;
    fireShot.show();

    return QApplication::exec();
}
