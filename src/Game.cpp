//
// Created by Martin Cristobal on 22/04/2020.
//

#include "Game.h"

int Game::run() {
    initWindow();
    loadAssets();
    gameLoop();

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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS ; Aunque no debería ser necesaria
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL

    window = glfwCreateWindow( width, height, "Bettroit", NULL, NULL);


    if( window == NULL ){
        fprintf( stderr, "Falla al abrir una ventana GLFW.\n" );
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window); // Inicializar GLEW
    glewExperimental=true; // Se necesita en el perfil de base.
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Falló al inicializar GLEW\n");
        return -1;
    }
    return 0;
}

int Game::gameLoop() {
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
    Renderer renderer = Renderer();
    renderer.init();
    renderer.setShaders(vertex_shader_source, fragment_shader_source);

    while (!glfwWindowShouldClose(window))
    {
        //Coger eventos de teclado / ratón
        processLogic();
        render(&renderer);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int Game::loadAssets() {

}

int Game::processLogic() {
    return 0;
}

int Game::render(Renderer* renderer) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer->render();
    glfwSwapBuffers(window);
    return 1;
}
