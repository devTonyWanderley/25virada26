cmake_minimum_required(VERSION 3.19)
project(tp1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(tp1
    WIN32 MACOSX_BUNDLE
    main.cpp
    planialt.cpp
    planialt.h
    planialt.ui
    ed/glista.h
    tipos/ecivil.h tipos/ecivil.cpp
    tipos/ponto.h tipos/ponto.cpp
    tipos/aresta.h tipos/aresta.cpp
)

qt_add_translations(
    TARGETS tp1
    TS_FILES tp1_pt_BR.ts
)

target_link_libraries(tp1
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS tp1
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET tp1
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
