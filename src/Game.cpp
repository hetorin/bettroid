//
// Created by Martin Cristobal on 22/04/2020.
//

#include "Game.h"

int Game::run() {
    initWindow();
    loadAssets();
    gameLoop();
}

std::shared_ptr<GameObject>
Game::createGameObject(const GLfloat *vertices,
                       const char *vertex_shader_source,
                       const char *fragment_shader_source)
{
    auto triangleRenderer = std::make_shared<Renderer>();
    triangleRenderer->init(vertices);
    triangleRenderer->setShaders(vertex_shader_source, fragment_shader_source);
    auto triangleGameObject = std::make_shared<GameObject>();
    auto emptyGameObject = std::make_shared<GameObject>();
    triangleGameObject->addChildren(emptyGameObject);
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
    static const GLfloat vertices1[] = {
          -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.0f,  0.5f, 0.0f
    };
    static const GLfloat vertices2[] = {
          -0.3f, -0.3f, 0.0f,
          0.3f, -0.4f, 0.0f,
          0.0f,  0.3f, 0.0f
    };
    static const GLfloat vertices3[] = {
          -0.1f, -0.1f, 0.0f,
          0.1f, -0.2f, 0.0f,
          0.0f,  0.1f, 0.0f
    };
    
    const char* vertex_shader_source = R"glsl(
    #version 330 core
    layout(location = 0) in vec3 vertexPosition_modelspace;
    void main()
    {
        gl_Position.xyz = vertexPosition_modelspace;
        gl_Position.w = 1.0;
    }
)glsl";
    const char* fragment_shader_source1 = R"glsl(
		#version 330 core
        out vec3 color;
        void main(){
            color = vec3(1,0,0);
        }
)glsl";
    const char* fragment_shader_source2 = R"glsl(
		#version 330 core
        out vec3 color;
        void main(){
            color = vec3(0,1,0);
        }
)glsl";
    const char* fragment_shader_source3 = R"glsl(
		#version 330 core
        out vec3 color;
        void main(){
            color = vec3(0,0,1);
        }
)glsl";

    Scene bossFight = Scene();
    bossFight.addGameObject(
       createGameObject(vertices1,
                        vertex_shader_source,
                        fragment_shader_source1));
    bossFight.addGameObject(
       createGameObject(vertices2,
                        vertex_shader_source,
                        fragment_shader_source2));
    bossFight.addGameObject(
       createGameObject(vertices3,
                        vertex_shader_source,
                        fragment_shader_source3));
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
