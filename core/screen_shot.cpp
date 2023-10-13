//
// Created by wangyz38535 on 2023/10/12.
//
#include "utils/spdlog_wrapper.h"
#include "screen_shot.h"
#include "fireshot.h"

ScreenShot::ScreenShot(FireShot *lpFireShot) : QObject(lpFireShot), m_lpFireShot(lpFireShot)
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

}

void ScreenShot::finishShot(int code) {

}

void ScreenShot::finishConfirmArea() {

}
