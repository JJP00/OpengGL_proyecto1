// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <iostream>

// float vertices[] = {
//     // primer triangulo
//     -0.5f, 0.5f, 0.0f,   // top
//     -0.95f, -0.5f, 0.0f, // left
//     0.0f, -0.5f, 0.0f,   // center
//     // segundo
//     0.0f, -0.5f, 0.0f, // center
//     0.5f, 0.5f, 0.0f,  // top
//     0.95f, -0.5f, 0.0f // right
// };

// unsigned int indices[] = {
//     // note that we start from 0!
//     3, 2, 1, // first triangle
//     3, 0, 1  // second triangle
// };

// const char *vertexShaderSource = "#version 330 core\n"
//                                  "layout (location = 0) in vec3 aPos;\n"
//                                  "void main()\n"
//                                  "{\n"
//                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                  "}\0";

// const char *fragmentShaderSource = "#version 330 core\n"
//                                    "out vec4 FragColor;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                    "}\0";

// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// int main(void)
// {
//     /* Initialize the library */
//     if (!glfwInit())
//         return -1;

//     // Inicializar la version de opengl
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // Definicion de la ventana GLFW -> libreria que maneja ventanas
//     GLFWwindow *ventana = glfwCreateWindow(800, 600, "Primerita ventanita jiji uwu", NULL, NULL);

//     if (ventana == NULL)
//     {
//         std::cout << "No se ha creado la ventana correctamente" << std::endl;
//         glfwTerminate;
//         return -1;
//     }
//     glfwMakeContextCurrent(ventana);

//     // un callback por si se redimensiona la ventana
//     glfwSetFramebufferSizeCallback(ventana, framebuffer_size_callback);

//     // iniciar glad
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Fallo al iniciar GLAD" << std::endl;
//         return -1;
//     }

//     // Shaders GLSL, compilando un shader
//     unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);

//     // test del shader
//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

//     if (!success)
//     {
//         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
//                   << infoLog << std::endl;
//     }

//     // fragment shader y su compilación
//     unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);

//     // Shader program

//     unsigned int shaderProgram = glCreateProgram();

//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);

//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success)
//     {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
//                   << infoLog << std::endl;
//     }

//     // Borrado de shaders, una vez enlazado no es necesario tenerlo en memoria.

//     glDeleteShader(fragmentShader);
//     glDeleteShader(vertexShader);

//     // VAO y VBO

//     unsigned int VBO; // vertex buffer objects, almacena los datos del vertice en la GPU...
//     unsigned int VAO; // vertex array  objects, almacena el VBO y los atributos, explica lo que significa cada parte del vertice, posición, normal, coord de las texturas...
//     // unsigned int EBO; // Element buffer objects, indica el orden de dibujado de cada vertice

//     // glGenBuffers(1, &EBO);
//     glGenBuffers(1, &VBO); // genera uno o mas ids para cada VBO
//     glGenVertexArrays(1, &VAO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        // asociar y definir que VBO es de tipo GL_ARRAY_BUFFER
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // carga los datos del vetice al buffer

//     // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); no desenlazar el EBO cuando esta activo el VAO, ya que los elementos enlazados estan almacenados en el VAO

//     glBindVertexArray(0);

//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // para que se vea las lineas...

//     // Loop de renderizado, hasta que no cerremos la ventana, no va a parar.
//     while (!glfwWindowShouldClose(ventana))
//     {
//         // Al inicio del ciclo, ejecuta la función que comprueba si se ha pulsado un botón
//         processInput(ventana);

//         // VVV Renderizado... VVV

//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // configura el color al limpiar el buffer
//         glClear(GL_COLOR_BUFFER_BIT);         // limpia el buffer, por lo tanto, se mostrará el color configurado previamente.

//         glUseProgram(shaderProgram);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_TRIANGLES, 0, 6);
//         glBindVertexArray(0);
//         // Una ventana normalmente tiene 2 buffers:
//         // front donde se muestra el resultado y
//         // back al que se calcula como va a ser el resultado
//         glfwSwapBuffers(ventana);
//         glfwPollEvents();
//     }

//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteProgram(shaderProgram);

//     glfwTerminate();
//     return 0;
// }