// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#pragma once

#include "capturerequest.h"
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QRect>

struct CaptureContext
{
    // 叠加效果之后的图片
    QPixmap screenshot;
    // 没有经过任何编辑的原始图片
    QPixmap origScreenshot;
    // 选择的区域
    QRect selection;
    // 选择的工具颜色
    QColor color;
    // Path where the content has to be saved
    QString savePath;
    // Offset of the capture widget based on the system's screen (top-left)
    QPoint widgetOffset;
    // Mouse position inside the widget
    QPoint mousePos;
    // Size of the active tool
    int toolSize;
    // Current circle count
    int circleCount;
    // Mode of the capture widget
    bool fullscreen;
    CaptureRequest request = CaptureRequest::GRAPHICAL_MODE;

    QPixmap selectedScreenshotArea() const;
};
