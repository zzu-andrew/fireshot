//
// Created by wangyz38535 on 2023/10/12.
//


#include "screen_widget.h"
#include "utils/spdlog_wrapper.h"
#include "uti"

#define UNVISIABLE_X -819200
#define UNVISIABLE_Y -819200

ScreenWidgets::ScreenWidgets(QWidget *parent) : QWidget(parent) {

}

ScreenWidgets::~ScreenWidgets() {

}


ScreenWidgets::ScreenWidgets(QWidget* parent)
        : QWidget(parent)
        , m_screenlist(nullptr)
        , m_status("unknown")
{
#ifndef USE_SPDLOG_
    setWindowFlags(Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
#endif // USE_SPDLOG_
}


void ScreenWidgets::start(std::shared_ptr<ScreenList> list, int index)
{
    SPD_FUNCTION();

    QRect geometry = list->allBoundary(true);
    setGeometry(geometry);

    showFullScreen();

    raise();
    activateWindow();

    setCursor(Qt::ArrowCursor);

    m_screenlist = list;
}

void ScreenWidgets::cleanup()
{
    SPD_FUNCTION();
    hide();

    SPD_TRACE("is visable = {0} && w: {1}, h: {2} @ {3}", this->isVisible(), size().width(), size().height(), __FUNCTION__);

    m_status = "unknown";

    update();
}


void ScreenWidgets::finishConfirmArea()
{
    //if (m_workspace->areaConfirmed() == true)
    //    m_status = "active";
    //else
    //    m_status = "giveup";
}

void ScreenWidgets::showEvent(QShowEvent* event)
{
    SPD_FUNCTION();

    raise();
    activateWindow();

    setMouseTracking(true);

    QWidget::showEvent(event);
    SPD_WARN("is visable = {0} && x: {1}, y: {2}, w: {3}, h: {4} @ {5} --- {6}"
            , this->isVisible(), pos().x(), pos().y(), size().width(), size().height(), m_status.toStdString().c_str()
            , __FUNCTION__);
}

void ScreenWidgets::hideEvent(QHideEvent* event)
{
    setMouseTracking(false);

    resize(0, 0);

    QWidget::hideEvent(event);

    SPD_INFO("is visable = {0} && x: {1}, y: {2}, w: {3}, h: {4} @ {5} --- {6}"
            , this->isVisible(), pos().x(), pos().y(), size().width(), size().height(), m_status.toStdString().c_str()
            , __FUNCTION__);
}

void ScreenWidgets::closeEvent(QCloseEvent* event)
{
    //event->ignore();

    SPD_TRACE("{0} stat = {1}", __FUNCTION__, m_status.toStdString().c_str());

    hide();
}

void ScreenWidgets::mousePressEvent(QMouseEvent* event)
{
}

void ScreenWidgets::mouseMoveEvent(QMouseEvent* event)
{
    SPD_TRACE("{0} stat = {1}", __FUNCTION__, m_status.toStdString().c_str());
}

void ScreenWidgets::mouseReleaseEvent(QMouseEvent* event)
{
    //m_workspace->onMouseRelease(event);
}

void ScreenWidgets::keyPressEvent(QKeyEvent* event)
{
}

void ScreenWidgets::paintEvent(QPaintEvent* event)
{
    SPD_FUNCTION();

    Q_UNUSED(event);

    QPainter painter(this);

}

void ScreenWidgets::enterEvent(QEvent* event)
{
    SPD_FUNCTION();
    QWidget::enterEvent(event);
}

void ScreenWidgets::leaveEvent(QEvent* event)
{
    SPD_FUNCTION();
    //     if (m_workspace->areaConfirmed() == false)
    //     {
    //         m_workspace->setAreaBoundary(QRect(0,0,0,0));
    //         update();
    //     }

    QWidget::leaveEvent(event);
}



