HEADERS       = glwidget.h \
                plane.h \
                window.h \
                mainwindow.h
SOURCES       = glwidget.cpp \
                main.cpp \
                plane.cpp \
                window.cpp \
                mainwindow.cpp

QT           += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
INSTALLS += target
