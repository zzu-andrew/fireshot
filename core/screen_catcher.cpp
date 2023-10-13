//
// Created by wangyz38535 on 2023/10/13.
//

#include "screen_catcher.h"
#include <QApplication>
#include <QDesktopWidget>

#include "utils/spdlog_wrapper.h"

QList<QList<ScreenInfo>> ScreenCatcher::CatchScreen() {
    QList<ScreenInfo> result;
    QList<QScreen*> screenList = QApplication::screens();
    for (auto & screen : screenList) {
        auto pixelRatio = screen->devicePixelRatio();
        QRect screenRect = screen->geometry();
        // 抓取一张屏幕图片
        QPixmap screenPixmap = screen->grabWindow(QApplication::desktop()->winId(), screenRect.x(), screenRect.y(),
                                                  static_cast<int>(screenRect.width()/pixelRatio),
                                                  static_cast<int>(screenRect.height()/pixelRatio));
        SPD_INFO("screenPix radios{0}, height{1}, width{2}", pixelRatio, screenPixmap.size().height(), screenPixmap.size().rwidth());

        ScreenInfo screenInfo;
        screenInfo.object = screen;
        screenInfo.boundary = screenRect;
        screenInfo.pixmap = screenPixmap;
        result.append(screenInfo);
    }

    QList<QList<ScreenInfo>> results;

    for (auto& screenInfo : result) {
        QList<ScreenInfo> one;
        one.append(screenInfo);
        results.append(one);
    }

    return results;
}
