cmake_minimum_required(VERSION 3.19)
project(Top LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(Top
    WIN32 MACOSX_BUNDLE
    main.cpp
    geral.cpp
    geral.h
    geral.ui
    interface/arquivo.h interface/arquivo.cpp interface/arquivo.ui

    ED/gno.h
    ED/gpilha.h
    ED/gfila.h
    ED/glista.h
    Tipos/ponto.h Tipos/ponto.cpp
    ED/quadro.h ED/quadro.cpp
    Tipos/aresta.h Tipos/aresta.cpp



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
