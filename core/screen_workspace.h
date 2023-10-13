//
// Created by wangyz38535 on 2023/10/13.
//

#ifndef FIRESHOT_SCREEN_WORKSPACE_H
#define FIRESHOT_SCREEN_WORKSPACE_H

#include <QWidget>
#include <QRect>
#include <QVector>
#include <QFont>
#include <QPushButton>

class Workspace : public QObject {
Q_OBJECT

public:
    explicit Workspace(QWidget *lpWidget);

    ~Workspace() override;

signals:
    void quitShot(int code);
    void finishConfirmArea();


}

#endif //FIRESHOT_SCREEN_WORKSPACE_H
