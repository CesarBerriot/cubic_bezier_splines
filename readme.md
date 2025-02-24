```cmake
    include(FetchContent)

    FetchContent_Declare(
        cubic_bezier_splines
        GIT_REPOSITORY https://github.com/CesarBerriot/cubic_bezier_splines.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(cubic_bezier_splines)

    target_link_libraries(PROJECT_NAME PRIVATE cubic_bezier_splines)
```