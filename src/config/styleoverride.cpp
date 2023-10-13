// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2020 Jeremy Borgman <borgman.jeremy@pm.me>
//
// Created by jeremy on 9/24/20.

#include "styleoverride.h"

int StyleOverride::styleHint(StyleHint hint,
                             const QStyleOption* option,
                             const QWidget* widget,
                             QStyleHintReturn* returnData) const
{

    // 当鼠标悬停在工具上时 延时600毫秒出现工具提示
    if (hint == SH_ToolTip_WakeUpDelay) {
        return 600;
    } else {
        return baseStyle()->styleHint(hint, option, widget, returnData);
    }
}
