/*
 * Tile.cpp
 *
 *  Created on: 12 Nov 2014
 *      Author: George Vicarey
 */

#include "tile.h"

Tile::Tile() {
    // Initialise variables to zero
    shader = 0;
    shaderProgram = 0;
    fragmentShader = 0;
    vertexShader = 0;
    vao = 0;
    vbo = 0;
    ebo = 0;
    x = 0; y = 0;
    r = 0; g = 0; b = 0;
    uniTrans = 0;
}

/**
 * A simple setter for the Tiles positions.
 * X, Y & Z are the Tiles world positions.
 */
void Tile::setPos(GLfloat X, GLfloat Y) {
    x = X;
    y = Y;
}

/**
 * Setter to set type of Tile.
 * Type is an Enum.
 */
void Tile::setType(Type type) {
    switch (type) {
        case Type::Red:
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
            break;

        case Type::Green:
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
            break;

        case Type::Blue:
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
            break;

        default:
            r = 0.0f;
            g = 0.0f;
            b = 0.0f;
            break;
    }
}

Tile::~Tile() {
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
}

/**
 * Creates the actual Tile.
 */
void Tile::createTile() {
    // Create the shader program to be used to render the Tile
    createShader();

    // set the vertices for the Tile so it's centered around
    // the Tiles X,Y,Z position. This includes the colours.
    GLfloat vertices[] = {
            //X,    Y,     Z,             R, G, B
            x - 0.5f, y - 0.5f, r, g, b,      // 0
            x + 0.5f, y - 0.5f, r, g, b,      // 1
            x + 0.5f, y + 0.5f, r, g, b,      // 2
            x - 0.5f, y + 0.5f, r, g, b,      // 3
     };

    // An element array to save using 36 vertices.
    GLuint elements[] = {
            0, 1, 2,
            2, 3, 0
    };

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // pass teh vertices data to the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    glGenBuffers(1, &ebo);

    // create and then bind the Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Bind the EBO and then pass teh element data to it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
    GL_STATIC_DRAW);

    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    // First 2 vertices are Position
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    // vertices 4,5,6 are Colour
    GLint colAttrib = glGetAttribLocation(shaderProgram, "colour");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
            (void*) (2 * sizeof(GLfloat)));


    trans = glm::rotate(trans, 0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
}

void Tile::update() {
    // Use the shader program compiled earlier.
    glUseProgram(shaderProgram);

    uniTrans = glGetUniformLocation(shaderProgram, "model");

    // calculate the view matrix and pass it to the shader program
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 20.0f),   //camera pos
                                 glm::vec3(2.0f, 2.0f, 0.0f),   //center on screen
                                 glm::vec3(0.0f, 0.0f, 1.0f));  //up/down axis
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    // calculaet projection matrix and pass it to the shader program
    glm::mat4 proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 400.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

void Tile::draw() {
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


void Tile::createShader() {
    // load vertex shader source
    const GLchar* vertexSource = shader->fileRead("src/shaders/vertex.vs");
    if (vertexSource == NULL) std::cerr << "vertexSource not loaded" << std::endl;

    // load fragment shader source
    const GLchar* fragmentSource = shader->fileRead("src/shaders/fragment.fs");
    if (fragmentSource == NULL) std::cerr << "fragmentSource not loaded" << std::endl;

    // Create and compile the vertex shader
    vertexShader = shader->compileShader(vertexSource, GL_VERTEX_SHADER);

    // Create and compile the fragment shader
    fragmentShader =  shader->compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Link the vertex and fragment shader into a shader program
    shaderProgram = shader->compileProgram(vertexShader, fragmentShader);
}
