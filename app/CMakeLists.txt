add_library(app_lib OBJECT
        src/experiment_vec2d.cpp
        src/experiment_vec3d.cpp
        src/tiny_app.cpp
        src/tiny_experiment.cpp)
target_include_directories(app_lib PUBLIC include)
target_link_libraries(app_lib PUBLIC
        math
        raylib
        rlimgui
        raygizmo
)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE app_lib)

add_custom_target(app_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:app>/resources
        COMMENT "Copying app resources")
add_dependencies(app app_resources)