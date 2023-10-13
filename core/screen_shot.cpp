//
// Created by wangyz38535 on 2023/10/12.
//
#include <QVBoxLayout>
#include "utils/spdlog_wrapper.h"
#include "screen_shot.h"
#include "fireshot.h"
#include "screen_catcher.h"

ScreenShot::ScreenShot(FireShot *lpFireShot) : QObject(lpFireShot),
    m_lpFireShot(lpFireShot),
    m_lpWidgets(new QList<ScreenWidgets*>),
    m_lpUnusedWidgets(new QList<ScreenWidgets*>)
{

}

ScreenShot::~ScreenShot() {
    SPD_FUNCTION();
}

void ScreenShot::cleanup() {

}

void ScreenShot::rasie() {

}

void ScreenShot::CaptureScreen(QWidget *parent) {
    SPD_FUNCTION();
    // 每次开始截图之前将原先截图数据都放置到非可用列表中，后期考虑多线程情况需要进行加锁
    std::copy(m_lpWidgets->begin(), m_lpWidgets->end(), std::back_inserter(*m_lpUnusedWidgets));
    m_lpWidgets->clear();

    // 获取所有截图信息
    auto screenCaptureList = ScreenCatcher::CatchScreen();

    // 构造截图的界面
    for (int32_t index = 0; index < screenCaptureList.size(); ++index) {
        auto screenList = screenCaptureList[index];

        std::shared_ptr<ScreenList> alone(new ScreenList(list));
        ScreenWidgets* w = nullptr;
        if (m_lpUnusedWidgets->empty()) {
            SPD_DEBUG("New screen list & widget");
            w = new ScreenWidgets(parent);
            connect(w->workspace(), &Workspace::quitShot, this, &ScreenShot::finishShot, Qt::DirectConnection);
            connect(w->workspace(), &Workspace::finishConfirmArea, this, &ScreenShot::finishConfirmArea, Qt::DirectConnection);
        }


    }




}

void ScreenShot::finishShot(int code) {
    SPD_FUNCTION();
    for (auto &w : *m_lpWidgets) {
        w->hide();
    }

    emit ShotDone(this);



}

void ScreenShot::finishConfirmArea() {
    SPD_FUNCTION();
    for (auto &w : *m_lpWidgets) {
        w->finishConfirmArea();
    }

}
