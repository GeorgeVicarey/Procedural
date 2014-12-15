/*
 * tile.h
 *
 *  Created on: 15 Dec 2014
 *      Author: George Vicarey
 */

#ifndef SRC_TILE_H_
#define SRC_TILE_H_

#include "global.h"

class Tile {
    public:
        enum Type {
            Red, Green, Blue
        };

        Tile();
        ~Tile();
        void setPos(GLfloat X, GLfloat Y);
        void setType(Type);
        void createProgram();
        void createTile();
        void update();
        void draw();
    private:
        void createShader();
        Shader* shader;
        GLuint shaderProgram, fragmentShader, vertexShader;
        GLuint vao, vbo, ebo;
        GLfloat x, y;
        GLfloat r, g, b;
        GLint uniTrans;
        glm::mat4 trans;
};

#endif /* SRC_TILE_H_ */
