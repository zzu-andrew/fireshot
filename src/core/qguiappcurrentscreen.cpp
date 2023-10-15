// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2021 Yuriy Puchkov <yuriy.puchkov@namecheap.com>

#include "qguiappcurrentscreen.h"
#include <QCursor>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QPoint>
#include <QScreen>

QGuiAppCurrentScreen::QGuiAppCurrentScreen()
{
    m_currentScreen = nullptr;
}

QScreen* QGuiAppCurrentScreen::currentScreen()
{
    return currentScreen(QCursor::pos());
}

QScreen* QGuiAppCurrentScreen::currentScreen(const QPoint& pos)
{
    m_currentScreen = screenAt(pos);

    if (!m_currentScreen) {
        qCritical("Unable to get current screen, starting to use primary "
                  "screen. It may be a cause of logical error and working with "
                  "a wrong screen.");
        m_currentScreen = qGuiApp->primaryScreen();
    }
    return m_currentScreen;
}

QScreen* QGuiAppCurrentScreen::screenAt(const QPoint& pos)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
    m_currentScreen = qGuiApp->screenAt(pos);
#else
    for (QScreen* const screen : QGuiApplication::screens()) {
        m_currentScreen = screen;
        if (screen->geometry().contains(pos)) {
            break;
        }
    }
#endif
    return m_currentScreen;
}
