include(FetchContent) # make sure we include fetched content

#FetchContent_Declare(Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG v3.16.1
#        GIT_SHALLOW TRUE)
#
#FetchContent_Declare(glm
#        GIT_REPOSITORY https://github.com/g-truc/glm.git
#        GIT_TAG GLM 1.0.3
#        GIT_SHALLOW TRUE)

#FetchContent_MakeAvailable(Catch2 GLM)

add_executable(tests
        math/test_vec2.cpp
        math/test_vec3.cpp)
target_link_libraries(tests PRIVATE math glm Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(tests)
