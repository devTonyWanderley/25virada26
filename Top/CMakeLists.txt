cmake_minimum_required(VERSION 3.19)
project(Top LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(Top
    WIN32 MACOSX_BUNDLE
    main.cpp
    topografia.cpp
    topografia.h
    topografia.ui
    ed/glista.h
    tipos/ponto.cpp tipos/ponto.h
    tipos/aresta.cpp tipos/aresta.h
)

qt_add_translations(
    TARGETS Top
    TS_FILES Top_pt_BR.ts
)

target_link_libraries(Top
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Top
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Top
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
