// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "globalshortcutfilter.h"
#include "src/core/flameshot.h"
#include <qt_windows.h>

GlobalShortcutFilter::GlobalShortcutFilter(QObject* parent)
  : QObject(parent)
{
    // Forced Print Screen
    if (RegisterHotKey(NULL, 1, 0, VK_SNAPSHOT)) {
        // ok - capture screen
    }

    if (RegisterHotKey(NULL, 2, MOD_SHIFT, VK_SNAPSHOT)) {
        // ok - show screenshots history
    }
}

bool GlobalShortcutFilter::nativeEventFilter(const QByteArray& eventType,
                                             void* message,
                                             long* result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    MSG* msg = static_cast<MSG*>(message);
    if (msg->message == WM_HOTKEY) {
        // TODO: this is just a temporal workwrround, proper global
        // support would need custom shortcuts defined by the user.
        const quint32 keycode = HIWORD(msg->lParam);
        const quint32 modifiers = LOWORD(msg->lParam);

        // Show screenshots history
        // 按下截屏键和shit键时，触发
        if (VK_SNAPSHOT == keycode && MOD_SHIFT == modifiers) {
            Flameshot::instance()->history();
        }

        // Capture screen
        // 按下截屏键时触发并且同时没有触发Ctrl sshift等键盘的时候触发
        if (VK_SNAPSHOT == keycode && 0 == modifiers) {
            Flameshot::instance()->requestCapture(
              CaptureRequest(CaptureRequest::GRAPHICAL_MODE));
        }

        return true;
    }
    return false;
}
