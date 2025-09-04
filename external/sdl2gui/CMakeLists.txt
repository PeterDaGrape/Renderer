add_library(
    imgui STATIC
    imgui.cpp
    imgui_draw.cpp
    imgui_impl_sdl2.cpp
    imgui_impl_sdlrenderer2.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

find_package(SDL2 REQUIRED)


target_include_directories(
    imgui
    PUBLIC
    "${SDL2_INCLUDE_DIRS}"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

