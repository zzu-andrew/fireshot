target_sources(fireshot PRIVATE
    flameshot.h
    flameshotdaemon.h
    qguiappcurrentscreen.h
)

target_sources(fireshot PRIVATE
    capturerequest.cpp
    flameshot.cpp
    flameshotdaemon.cpp
    qguiappcurrentscreen.cpp
)

IF (WIN32)
    target_sources(fireshot PRIVATE globalshortcutfilter.h globalshortcutfilter.cpp)
ENDIF ()
