cmake_minimum_required(VERSION 3.17)
project(e3-marcgr9)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)
set(CMAKE_PREFIX_PATH /Users/marc/Qt/6.1.0/clang_64/lib/cmake/
        )

add_executable(${PROJECT_NAME} main.cpp
        utils/observer.h utils/repository.h utils/utils.h
        controller/board.h controller/board.cpp
        entities/player.h
        ui/window.cpp ui/window.h
        ui/model/model.h
        )

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})