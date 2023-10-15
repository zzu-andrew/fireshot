// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#pragma once

#include "src/core/capturerequest.h"
#include <QObject>
#include <QPointer>
#include <QVersionNumber>

class CaptureWidget;
class ConfigWindow;
class InfoWindow;
class CaptureLauncher;
class UploadHistory;

class Flameshot : public QObject
{
    Q_OBJECT

public:
    enum Origin
    {
        CLI,
        DAEMON
    };

    static Flameshot* instance();

public slots:
    // 截图接口
    CaptureWidget* gui(const CaptureRequest& req = CaptureRequest::GRAPHICAL_MODE);

    void screen(CaptureRequest req, int const screenNumber = -1);
    void full(const CaptureRequest& req);
    void launcher();
    void config();

    void info();
    void history();

    QVersionNumber getVersion();

public:
    void setExternalWidget(bool b);
    bool haveExternalWidget();

signals:
    void captureTaken(QPixmap p);
    void captureFailed();

public slots:
    void requestCapture(const CaptureRequest& request);
    void exportCapture(const QPixmap& p,
                       QRect& selection,
                       const CaptureRequest& req);

private:
    Flameshot();
    bool resolveAnyConfigErrors();

    bool m_haveExternalWidget;

    // 用来操作激凸的主界面
    QPointer<CaptureWidget> m_captureWindow;
    QPointer<InfoWindow> m_infoWindow;
    QPointer<CaptureLauncher> m_launcherWindow;
    QPointer<ConfigWindow> m_configWindow;

};
