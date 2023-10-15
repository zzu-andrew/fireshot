// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "singleapplication.h"

#include "abstractlogger.h"
#include "src/config/styleoverride.h"
#include "src/core/capturerequest.h"
#include "src/core/flameshot.h"
#include "src/core/flameshotdaemon.h"
#include "src/utils/confighandler.h"
#include "src/utils/filenamehandler.h"
#include "src/utils/pathinfo.h"
#include "src/utils/valuehandler.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
#include <desktopinfo.h>
#endif

#ifdef Q_OS_LINUX
// source: https://github.com/ksnip/ksnip/issues/416
void wayland_hacks()
{
    // Workaround to https://github.com/ksnip/ksnip/issues/416
    DesktopInfo info;
    if (info.windowManager() == DesktopInfo::GNOME) {
        qputenv("QT_QPA_PLATFORM", "xcb");
    }
}
#endif

void requestCaptureAndWait(const CaptureRequest& req)
{
    Flameshot* flameshot = Flameshot::instance();
    flameshot->requestCapture(req);
    QObject::connect(flameshot, &Flameshot::captureTaken, [&](const QPixmap&) {
        // if this instance is not daemon, make sure it exit after caputre finish
        if (FireshotDaemon::instance() == nullptr && !Flameshot::instance()->haveExternalWidget()) {
            qApp->exit(0);
        }
    });
    QObject::connect(flameshot, &Flameshot::captureFailed, []() {
        AbstractLogger::info() << "Screenshot aborted.";
        qApp->exit(1);
    });
    qApp->exec();
}


int main(int argc, char* argv[])
{
#if defined(Q_OS_LINUX)
    wayland_hacks();
#endif

    // required for the button serialization
    // TODO: change to QVector in v1.0
    qRegisterMetaTypeStreamOperators<QList<int>>("QList<int>");
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setApplicationName(QStringLiteral("flameshot"));
    QCoreApplication::setOrganizationName(QStringLiteral("flameshot"));

    SingleApplication app(argc, argv);

    QApplication::setStyle(new StyleOverride);

    QTranslator translator, qtTranslator;
    QStringList trPaths = PathInfo::translationsPaths();

    for (const QString& path : trPaths) {
        bool match = translator.load(QLocale(),
                                     QStringLiteral("Internationalization"),
                                     QStringLiteral("_"),
                                     path);
        if (match) {
            break;
        }
    }
    // 添加翻译文件
    qtTranslator.load(
      QLocale::system(),
      "qt",
      "_",
      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&translator);
    qApp->installTranslator(&qtTranslator);

    qApp->setAttribute(Qt::AA_DontCreateNativeWidgetSiblings, true);

    Flameshot::instance();
    FireshotDaemon::start();

    return qApp->exec();
}
