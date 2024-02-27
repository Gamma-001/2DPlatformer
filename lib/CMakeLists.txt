add_library(
    engine 
    "gen/transform.cpp" "gen/color.cpp" "gen/path.cpp" "gen/strutils.cpp"
    "engine/mesh.cpp" "engine/shader.cpp" "engine/camera.cpp" "engine/texture.cpp" "engine/sprite.cpp" "engine/buffer.cpp"
    "gui/window.cpp"
)