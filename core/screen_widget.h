//
// Created by wangyz38535 on 2023/10/12.
//

#ifndef FIRESHOT_SCREEN_WIDGET_H
#define FIRESHOT_SCREEN_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QPainter>

#include "screen_list.h"
#include "screen_workspace.h"

class ScreenWidgets : public QWidget {
    Q_OBJECT

public:
    ScreenWidgets(QWidget *parent = nullptr);
    ~ScreenWidgets();

    void start(std::shared_ptr<ScreenList> list, int index);
    void cleanup();

    Workspace* workspace();
    void finishConfirmArea();

protected:
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent *event) override;

private:
    QString m_status;  //unknown, active, giveup
    std::shared_ptr<ScreenList> m_screenlist;
    Workspace m_workspace;
};


#endif //FIRESHOT_SCREEN_WIDGET_H
