#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.6f, 0.2f, 0.6f, 1.0f);\n"  
"}\n\0";

const char* vertexShaderSourceWithColor =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"

"out vec3 ourColor;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;"
"}\0";


const char* fragmentShaderSourceWithColor = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceWithColor, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceWithColor, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
   /* float vertices[] = {
         0.4f,   0.5f,  0.0f,  // 0
         0.4f,  -0.5f,  0.0f,  // 1
         0.0f,  -0.5f,  0.0f,  // 2
         0.0f,   0.5f,  0.0f,  // 3 
        -0.4f,  -0.5f,  0.0f,  // 4
        -0.4f,   0.5f,  0.0f,  // 5
         0.8f,  -0.5f,  0.0f,  // 6
        -0.8f,  -0.5f,  0.0f,  // 7
    };
    unsigned int indices[] = {  // note that we start from 0!

        0, 6, 1, //TRIANGULO 1 (EL DE LA PUNTA DERECHA)

        //RECTANGULO 1 (COMPUESTO DE TRIANGULO 2 Y 3)
        0, 1, 3,
        3, 2, 1,

        ////RECTANGULO 2 (COMPUESTO DE TRIANGULO 4 Y 5)
        3, 2, 5,
        5, 4, 2,

        5, 4, 7, //TRIANGULO 6 (EL DE LA PUNTA IZQUIERDA)
       
    };*/

    float verticesTriangulosColores[] = {
        0.25f, -0.35f, 0.0f,    0.878, 0.639, 0.827,  // 1
        0.45f, -0.35f, 0.0f,    0.878, 0.639, 0.827,  // 0
        0.25f, -0.55f, 0.0f,    0.878, 0.639, 0.827,  // 2 

        0.25f, -0.35f, 0.0f,   0.878, 0.639, 0.827,   // 1
        0.25f, -0.55f, 0.0f,   0.878, 0.639, 0.827,   // 2
        0.05f, -0.55f, 0.0f,   0.878, 0.639, 0.827,   // 4

        0.05f, -0.15f, 0.0f,   0.529, 0.066, 0.815,   // 3
        0.05f, -0.55f, 0.0f,   0.529, 0.066, 0.815,   // 4
       -0.35f, -0.55f, 0.0f,   0.529, 0.066, 0.815,   // 5

       -0.25f,  0.10f, 0.0f,   0.956, 0.462, 0.788,   // 6
        0.05f, -0.15f, 0.0f,   0.956, 0.462, 0.788,   // 3
       -0.25f, -0.45f, 0.0f,   0.956, 0.462, 0.788,   // 8 

       -0.25f,  0.10f, 0.0f,   0.576, 0.494, 0.925,   // 6
       -0.25f, -0.30f, 0.0f,   0.576, 0.494, 0.925,   // 7
       -0.45f, -0.10f, 0.0f,   0.576, 0.494, 0.925,   // 9 

       -0.25f, 0.40f, 0.0f,    0.831, 0.768, 0.870,   // 12
       -0.10f, 0.25f, 0.0f,    0.831, 0.768, 0.870,   // 11
       -0.25f, 0.10f, 0.0f,    0.831, 0.768, 0.870,   // 6 

       -0.25f, 0.40f, 0.0f,    0.831, 0.768, 0.870,   // 12
       -0.25f, 0.10f, 0.0f,    0.831, 0.768, 0.870,   // 6 
       -0.40f, 0.25f, 0.0f,    0.831, 0.768, 0.870,   // 14

       -0.10f, 0.55f, 0.0f,    0.780, 0.262, 0.643,   // 10
       -0.10f, 0.25f, 0.0f,    0.780, 0.262, 0.643,   // 11 
       -0.25f, 0.40f, 0.0f,    0.780, 0.262, 0.643,   // 12

       -0.40f, 0.55f, 0.0f,    0.564, 0.329, 0.870,   // 13
       -0.25f, 0.40f, 0.0f,    0.564, 0.329, 0.870,   // 12 
       -0.40f, 0.25f, 0.0f,    0.564, 0.329, 0.870,   // 14
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangulosColores), verticesTriangulosColores, GL_STATIC_DRAW);

    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Column Major
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glLineWidth(20.0);

        glPointSize(20.0);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 27);
        //glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        //ESTE ES MUY IMPORTANTE, ESE "18" ES EL NUMERO DE VERTICES DEL OBJETO. SI NO PONES LA CANTIDAD CORRECTA,
        //NO TE APARECERAN TUS TRIANGULOS. SOLO SUMA LA CANTIDAD DE VERTICES EN LA MATRIZ DE INDICES
        
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}