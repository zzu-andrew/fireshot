//
// Created by wangyz38535 on 2023/10/12.
//

#ifndef FIRESHOT_SCREEN_SHOT_H
#define FIRESHOT_SCREEN_SHOT_H

#include <QObject>
#include <QWidget>
#include <QList>
//#include "widget.h"

class FireShot;

class ScreenShot : public QObject {
    Q_OBJECT
public:
    explicit ScreenShot(FireShot *lpFireShot);
    ~ScreenShot() override;

    void init(QWidget* parent);

    void cleanup();

    void rasie();

private:
    //QList<Widget*>* m_widgets;
    //QList<Widget*>* m_unused_widgets;

signals:
    void ShotDone(ScreenShot*);
    void ShotResult(std::shared_ptr<QPixmap> pixmap);

private slots:
    void finishShot(int code);
    void finishConfirmArea();

private:
    FireShot *m_lpFireShot;
};


#endif //FIRESHOT_SCREEN_SHOT_H
