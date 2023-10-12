//
// Created by wangyz38535 on 2023/10/12.
//

#ifndef FIRESHOT_SCREEN_LIST_H
#define FIRESHOT_SCREEN_LIST_H



#include <QPainter>
#include <QRect>

#include <memory>
#include <QScreen>
#include <QPixmap>
#include <QRect>

struct ScreenInfo{
    QScreen *object;
    QRect boundary;
    QPixmap pixmap;
};

/**
 * @class : ScreenList
 * @brief : 屏幕列表集合
 * @note  : 屏幕列表集合基本功能
 */
class ScreenList
{
public:
    ScreenList(QList<ScreenInfo> list);

    QRect allBoundary(bool isGlobal=false) const;
    QPixmap allPixMap() const;

    QRect boundaryAt(int screenIndex,bool isGlobal=false);
    QScreen *screenAt(int screenIndex);
    QPixmap pixmapAt(int screenIndex);

    QRect toLocal(QRect rect);
    float scale();

    void draw(QPainter &painter);
    void draw(QPainter &painter,QPainterPath maskPath,QBrush maskBrush);

private:
    QRect m_allBoundary;
    std::shared_ptr<QPixmap> m_allPixMap;
    QList<ScreenInfo> m_List;

    void initParams();
};



#endif //FIRESHOT_SCREEN_LIST_H
