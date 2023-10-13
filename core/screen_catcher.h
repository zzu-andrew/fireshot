//
// Created by wangyz38535 on 2023/10/13.
//

#ifndef FIRESHOT_SCREEN_CATCHER_H
#define FIRESHOT_SCREEN_CATCHER_H
#include <QList>
#include "screen_list.h"

/*
 * @brief 用来捕获所有的屏幕
 * */
class ScreenCatcher {
public:
    static QList<QList<ScreenInfo>> CatchScreen();
};


#endif //FIRESHOT_SCREEN_CATCHER_H
