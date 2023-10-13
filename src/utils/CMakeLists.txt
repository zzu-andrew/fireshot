# Required to generate MOC
target_sources(
        fireshot
  PRIVATE abstractlogger.h
          filenamehandler.h
          screengrabber.h
          systemnotification.h
          valuehandler.h
          request.h
          strfparse.h
)

target_sources(
        fireshot
  PRIVATE abstractlogger.cpp
          filenamehandler.cpp
          screengrabber.cpp
          confighandler.cpp
          systemnotification.cpp
          valuehandler.cpp
          screenshotsaver.cpp
          globalvalues.cpp
          desktopfileparse.cpp
          desktopinfo.cpp
          pathinfo.cpp
          colorutils.cpp
          history.cpp
          strfparse.cpp
          request.cpp
)

IF (WIN32)
  target_sources(
          fireshot
    PRIVATE winlnkfileparse.cpp
  )
ENDIF()
