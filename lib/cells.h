#pragma once

#include "glad/glad.h"
#include "mesh.h"

#include <GL/gl.h>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>

#include <array>
#include <vector>
#include <cstdint>
#include <iostream>

const unsigned boardWidth = 50;

class Cells {
public:
    Cells(std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>, unsigned short);

    void generateMesh();
    void draw(glm::mat4&);

    void progress();
    enum Neighboorhood : unsigned short {
        MOORE,
        NEUMANN,
    };
private:
    void countNeighbours();
    void countNeighbours(int, int, int, std::array<std::array<std::array<bool, boardWidth>, boardWidth>, boardWidth>&);

    void loadFace(const MeshData*, unsigned, unsigned, unsigned);
    std::array<ushort, 4> getOcclusion(unsigned x, unsigned y, unsigned z, unsigned short face);
    void shaderInit();
    void renderInit();
    std::array<std::array<std::array<bool, boardWidth>, boardWidth>, boardWidth> cells{false};

    std::vector<GLuint> indexMesh;
    std::vector<GLuint> vertexMesh;

    unsigned shaderProgram;

    unsigned VAO;
    unsigned VBO;
    unsigned EBO;
    
    unsigned gameMode;

    std::pair<unsigned, unsigned> survivalRange;
    std::pair<unsigned, unsigned> birthRange;
    unsigned short neighbourhood;

    glm::mat4 projection;
};
