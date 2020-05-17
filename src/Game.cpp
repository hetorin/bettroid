//
// Created by Martin Cristobal on 22/04/2020.
//

#include "Game.h"
#include "Common/Quad.h"

int Game::run() {
    initWindow();
    loadAssets();
    gameLoop();
}

std::shared_ptr<GameObject>
Game::createGameObject(const char *vertex_shader_source,
                       const char *fragment_shader_source)
{
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<Quad> quad = std::make_shared<Quad>();
    auto triangleRenderer = std::make_shared<Renderer>(quad);
    triangleRenderer->init();
    triangleRenderer->setShaders(vertex_shader_source, fragment_shader_source);
    auto triangleGameObject = std::make_shared<GameObject>();
    triangleGameObject->addComponent(triangleRenderer);

    return triangleGameObject;
}

int Game::initWindow() {
    int width = 1024;
    int height = 768;

    if( !glfwInit() )
    {
        fprintf( stderr, "Error al inicializar GLFW\n" );
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Queremos OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL

    window = glfwCreateWindow( width, height, "Bettroit", NULL, NULL);

    if( window == NULL ){
        fprintf( stderr, "Falla al abrir una ventana GLFW.\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Inicializar GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Falló al inicializar GLEW\n");
        return -1;
    }
    return 0;
}

int Game::gameLoop() {
    int width, height;

    const char* vertex_shader_source = R"glsl(
       #version 330 core
       layout(location = 0) in vec3 vertexPosition_modelspace;
       void main()
       {
           gl_Position.xyz = vertexPosition_modelspace;
           gl_Position.w = 1.0;
       }
    )glsl";

    const char* fragment_shader_source = R"glsl(
		 #version 330 core
       out vec3 color;
       void main(){
           color = vec3(1,0,0);
       }
    )glsl";

    Scene bossFight = Scene();
    bossFight.addGameObject(
       createGameObject(vertex_shader_source,
                        fragment_shader_source));
    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bossFight.update();
        glfwSwapBuffers(window);
        //Coger eventos de teclado / raton
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int Game::update() {

}
int Game::loadAssets() {

}
