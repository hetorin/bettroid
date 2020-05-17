//
// Created by Martin Cristobal on 22/04/2020.
//

#include "Game.h"

int Game::run() {
    initWindow();
    loadAssets();
    gameLoop();
}

std::shared_ptr<GameObject> Game::createGameObject(const GLfloat *vertices, const char *vertex_shader_source, const char *fragment_shader_source)
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
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS ; Aunque no debería ser necesaria
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL

    window = glfwCreateWindow( width, height, "Bettroit", NULL, NULL);

    if( window == NULL ){
        fprintf( stderr, "Falla al abrir una ventana GLFW.\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Inicializar GLEW
    //glewExperimental=true; // Se necesita en el perfil de base.
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

    /*
    auto triangleRenderer1 = std::make_shared<Renderer>();
    triangleRenderer1->init(vertices1);
    triangleRenderer1->setShaders(vertex_shader_source, fragment_shader_source1);
    auto redTriangleOfDeath1 = std::make_shared<GameObject>();
    auto emptyGameObject1 = std::make_shared<GameObject>();
    redTriangleOfDeath1->addChildren(emptyGameObject1);
    redTriangleOfDeath1->addComponent(triangleRenderer1);

    auto triangleRenderer2 = std::make_shared<Renderer>();
    triangleRenderer2->init(vertices2);
    triangleRenderer2->setShaders(vertex_shader_source, fragment_shader_source2);
    auto redTriangleOfDeath2 = std::make_shared<GameObject>();
    auto emptyGameObject2 = std::make_shared<GameObject>();
    redTriangleOfDeath2->addChildren(emptyGameObject2);
    redTriangleOfDeath2->addComponent(triangleRenderer2);

    auto triangleRenderer3 = std::make_shared<Renderer>();
    triangleRenderer3->init(vertices3);
    triangleRenderer3->setShaders(vertex_shader_source, fragment_shader_source3);
    auto redTriangleOfDeath3 = std::make_shared<GameObject>();
    auto emptyGameObject3 = std::make_shared<GameObject>();
    redTriangleOfDeath3->addChildren(emptyGameObject3);
    redTriangleOfDeath3->addComponent(triangleRenderer3);
    */

    Scene bossFight = Scene();
    bossFight.addGameObject(createGameObject(vertices1, vertex_shader_source, fragment_shader_source1));
    bossFight.addGameObject(createGameObject(vertices2, vertex_shader_source, fragment_shader_source2));
    bossFight.addGameObject(createGameObject(vertices3, vertex_shader_source, fragment_shader_source3));

    while (!glfwWindowShouldClose(window))
    {
        //Coger eventos de teclado / ratón
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bossFight.update();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int Game::update() {

}
int Game::loadAssets() {

}
