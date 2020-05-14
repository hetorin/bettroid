cmake_minimum_required(VERSION 3.16)
project(Bettroid)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bettroid
   src/main.cpp
   src/Game.cpp
   src/Common/Renderer.cpp
   src/Common/Shader.cpp
   src/Common/Behaviour.cpp
   src/Common/Component.cpp
   src/Common/GameObject.cpp
   src/Common/Scene.cpp
   src/Common/Transform.cpp)

target_link_libraries(Bettroid PUBLIC glew32 glfw3 opengl32)
