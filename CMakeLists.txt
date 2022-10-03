cmake_minimum_required(VERSION 3.21)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    if (CMAKE_BUILD_TYPE MATCHES Release)
       add_executable(Snake WIN32)
    else()
        add_executable(Snake)
    endif()
else()
       add_executable(Snake)
endif()


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

        resource/snake.rc
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


find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE

        SDL2::SDL2 SDL2::SDL2main
		$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
        SDL2::SDL2_image
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        fmt::fmt
)
