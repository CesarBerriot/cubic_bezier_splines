# Integration

Cubic Bezier Splines depends on CMake for automatic integration. Simply fetch the latest release and let CMake do the heavy-lifting.
```cmake
include(FetchContent)

FetchContent_Declare(
    cubic_bezier_splines
    GIT_REPOSITORY https://github.com/CesarBerriot/cubic_bezier_splines.git
    GIT_TAG 1.0.0
)
FetchContent_MakeAvailable(cubic_bezier_splines)

target_link_libraries(YOUR_TARGET_NAME PRIVATE cubic_bezier_splines)
```