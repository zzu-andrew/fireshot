target_sources(fireshot PRIVATE arrow/arrowtool.h arrow/arrowtool.cpp)
target_sources(fireshot PRIVATE pixelate/pixelatetool.h pixelate/pixelatetool.cpp)
target_sources(fireshot PRIVATE circle/circletool.h circle/circletool.cpp)
target_sources(fireshot PRIVATE circlecount/circlecounttool.h circlecount/circlecounttool.cpp)
target_sources(fireshot PRIVATE copy/copytool.h copy/copytool.cpp)
target_sources(fireshot PRIVATE exit/exittool.h exit/exittool.cpp)
target_sources(fireshot PRIVATE sizeincrease/sizeincreasetool.h sizeincrease/sizeincreasetool.cpp)
target_sources(fireshot PRIVATE sizedecrease/sizedecreasetool.h sizedecrease/sizedecreasetool.cpp)
target_sources(
fireshot
        PRIVATE imgupload/storages/imgur/imguruploader.h
        imgupload/storages/imgur/imguruploader.cpp
        imgupload/storages/imguploaderbase.h
        imgupload/storages/imguploaderbase.cpp
        imgupload/imguploadertool.h
        imgupload/imguploadertool.cpp
        imgupload/imguploadermanager.h
        imgupload/imguploadermanager.cpp
)
target_sources(
        fireshot
  PRIVATE launcher/applaunchertool.h
          launcher/applauncherwidget.h
          launcher/launcheritemdelegate.h
          launcher/terminallauncher.h
          launcher/applaunchertool.cpp
          launcher/applauncherwidget.cpp
          launcher/launcheritemdelegate.cpp
          launcher/openwithprogram.cpp
          launcher/terminallauncher.cpp)
target_sources(fireshot PRIVATE line/linetool.h line/linetool.cpp)
target_sources(fireshot PRIVATE marker/markertool.h marker/markertool.cpp)
target_sources(fireshot PRIVATE move/movetool.h move/movetool.cpp)
target_sources(fireshot PRIVATE pencil/penciltool.h pencil/penciltool.cpp)
target_sources(
        fireshot
  PRIVATE pin/pintool.h
          pin/pinwidget.h
          pin/pintool.cpp
          pin/pinwidget.cpp)
target_sources(fireshot PRIVATE rectangle/rectangletool.h rectangle/rectangletool.cpp)
target_sources(fireshot PRIVATE redo/redotool.h redo/redotool.cpp)
target_sources(fireshot PRIVATE save/savetool.h save/savetool.cpp)
target_sources(fireshot PRIVATE accept/accepttool.h accept/accepttool.cpp)
target_sources(fireshot PRIVATE invert/inverttool.h invert/inverttool.cpp)
target_sources(fireshot PRIVATE selection/selectiontool.h selection/selectiontool.cpp)
target_sources(
        fireshot
  PRIVATE text/textconfig.h
          text/texttool.h
          text/textwidget.h
          text/textconfig.cpp
          text/texttool.cpp
          text/textwidget.cpp)
target_sources(fireshot PRIVATE undo/undotool.h undo/undotool.cpp)

target_sources(
        fireshot
  PRIVATE abstractactiontool.cpp
          abstractpathtool.cpp
          abstracttwopointtool.cpp
          capturecontext.cpp
          toolfactory.cpp
          abstractactiontool.h
          abstractpathtool.h
          abstracttwopointtool.h
          capturetool.h
          toolfactory.h)
