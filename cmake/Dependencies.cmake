# All external dependencies live here, included once so every other target can link against them]

include(FetchContent)

# Catch2 - test framework
FetchContent_Declare(catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.16.1
        GIT_SHALLOW TRUE)

# glm - math library
FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
        GIT_SHALLOW TRUE)

# raylib - platform api
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build examples for raylib
FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.2
        GIT_SHALLOW TRUE)

# ImGui - gui
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.7
        GIT_SHALLOW TRUE)

# rlImGui - ImGui integration into raylib
FetchContent_Declare(rlimgui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG Raylib_6_0
        GIT_SHALLOW TRUE)

# raygizmo - gizmo support for raylib
FetchContent_Declare(raygizmo
        GIT_REPOSITORY https://github.com/cloudofoz/raylib-gizmo.git
        GIT_TAG main)

FetchContent_MakeAvailable(catch2 glm raylib imgui rlimgui raygizmo)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
target_include_directories(rlimgui PUBLIC ${rlimgui_SOURCE_DIR})
target_link_libraries(rlimgui PUBLIC imgui raylib)

add_library(raygizmo STATIC ${raygizmo_SOURCE_DIR}/src/raygizmo.c)
target_include_directories(raygizmo PUBLIC ${raygizmo_SOURCE_DIR}/src)
target_link_libraries(raygizmo PUBLIC raylib)
