add_library(app src/main.cpp)
target_include_directories(app PUBLIC include)
target_link_libraries(app PUBLIC math raylib rlimgui raygizmo)