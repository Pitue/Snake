cmake_minimum_required(VERSION 3.21)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

add_executable(Snake)

target_sources(
        ${PROJECT_NAME}
        PRIVATE

        header/Snake.h
        header/Texture.h
        header/misc.h
        header/Game.h

        src/main.cpp
        src/Snake.cpp
        src/Texture.cpp
        src/misc.cpp
        src/Game.cpp
        )

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE

        ./header/
        )

target_precompile_headers(
        ${PROJECT_NAME}
        PRIVATE

        ./header/pch.h
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_definitions(_DEBUG)
endif()

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE

        SDL2::SDL2 SDL2::SDL2main
        SDL2::SDL2_ttf
        SDL2::SDL2_image
        SDL2::SDL2_mixer
        fmt::fmt
)