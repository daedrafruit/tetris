#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <stdio.h>

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        // Do game logic, present a frame, etc.

        float vertices[] = {
          -0.5f, -0.5f, 0.0f,
          -0.5f, -0.5f, 0.0f,
          -0.5f, -0.5f, 0.0f
        };

        // vertex buffer object
        unsigned int VBO;
        // generate vbo
        glGenBuffers(1, &VBO);
        // bind vbo 
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // copy vertex data to vbo
        glBufferData(
          GL_ARRAY_BUFFER, //buffer
          sizeof(vertices), //size
          vertices, //vertices
          GL_STATIC_DRAW //method (static is for vertices that wont change often, something like dynamic would be good for often changing ones)
        );

        //create vertex shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        //attach source code (top of file)
        glShaderSource(
          vertexShader, //shader object
          1, //number of strings 
          &vertexShaderSource, //shader source code
          NULL 
        );
        //compile shader
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
          glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
          printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
          printf("%s", infoLog) ;
        }


    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
