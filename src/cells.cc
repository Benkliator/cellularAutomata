#include "cells.h"
#include "utility.h"

Cells::Cells() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers     (1, &VBO);
    glGenBuffers     (1, &EBO);

    shaderInit();
    projection = glm::perspective(glm::radians(60.0f), 1.8f, 0.1f, 1000.0f);
    cells[51][1][51] = true;
    cells[51][1][52] = true;
    cells[51][1][53] = true;
    cells[52][1][53] = true;
    cells[53][1][52] = true;
}

void Cells::shaderInit() {
    unsigned vertexShader =
        loadShader(GL_VERTEX_SHADER, "./res/shaders/cells.vert");
    unsigned fragmentShader =
        loadShader(GL_FRAGMENT_SHADER, "./res/shaders/cells.frag");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Cells::generateMesh() {
    vertexMesh.clear();
    indexMesh.clear();
    for (int x{0}; x < cells.size(); ++x) {
        for (int y{0}; y < cells[x].size(); ++y) {
            for (int z{0}; z < cells[x][y].size(); ++z) {
                if (!cells[x][y][z]) {
                    continue;
                }

                bool top    {true};
                bool bottom {true};
                bool front  {true};
                bool back   {true};
                bool left   {true};
                bool right  {true};
                if (y < (boardWidth - 1)) {
                    front = !cells[x][y+1][z];
                }
                if (y >= 1) {
                    back = !cells[x][y-1][z];
                }
                if (z < (boardWidth - 1)) {
                    right = !cells[x][y][z+1];
                }
                if (z > 0) {
                    left = !cells[x][y][z-1];
                }
                if (x < (boardWidth - 1)) {
                    top = !cells[x+1][y][z];
                }
                if (x > 0) {
                    bottom = !cells[x-1][y][z];
                }

                if (top) {
                    loadFace(&topMeshData, x, y, z);
                }

                if (bottom) {
                    loadFace(&bottomMeshData, x, y, z);
                }

                if (back) {
                    loadFace(&backMeshData, x, y, z);
                }

                if (front) {
                    loadFace(&frontMeshData, x, y, z);
                }

                if (left) {
                    loadFace(&leftMeshData, x, y, z);
                }

                if (right) {
                    loadFace(&rightMeshData, x, y, z);
                }
            }
        }
    }
    renderInit();
}

void Cells::renderInit() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexMesh.size() * sizeof(GLuint),
                 vertexMesh.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexMesh.size() * sizeof(GLuint),
                 indexMesh.data(),
                 GL_STATIC_DRAW);

    glVertexAttribIPointer(
        0, 4, GL_UNSIGNED_INT, 0 * sizeof(GLuint), (void*)(0));
    glEnableVertexAttribArray(0);
}

void Cells::loadFace(const MeshData* data,
                     unsigned x,
                     unsigned y,
                     unsigned z) {
    indexMesh.push_back((vertexMesh.size() / 4) + 0);
    indexMesh.push_back((vertexMesh.size() / 4) + 3);
    indexMesh.push_back((vertexMesh.size() / 4) + 1);
    indexMesh.push_back((vertexMesh.size() / 4) + 2);
    indexMesh.push_back((vertexMesh.size() / 4) + 1);
    indexMesh.push_back((vertexMesh.size() / 4) + 3);
    std::array<ushort, 4> occlusionArray =
        getOcclusion(x, y, z, data->face);
    size_t j = 0;
    for (size_t i = 0; i < 4; i++) {
        GLuint zi = z + data->faceCoords[j++];
        GLuint xi = x + data->faceCoords[j++];
        GLuint yi = y + data->faceCoords[j++];
        vertexMesh.push_back(xi);
        vertexMesh.push_back(yi);
        vertexMesh.push_back(zi);
        vertexMesh.push_back(occlusionArray[i]);
    }
}

std::array<ushort, 4> Cells::getOcclusion(unsigned x, unsigned y, unsigned z, unsigned short face) {
    // This is really ugly lol, will probably rework at some point.
    std::array<ushort, 4> vertexOcclusion{ 0, 0, 0, 0 };
    switch (face) {
        case MeshData::Top: {
            vertexOcclusion[0] = 0;
            vertexOcclusion[1] = 0;
            vertexOcclusion[2] = 0;
            vertexOcclusion[3] = 0;
        } break;
        case MeshData::Bottom: {
            vertexOcclusion[0] = 4;
            vertexOcclusion[1] = 4;
            vertexOcclusion[2] = 4;
            vertexOcclusion[3] = 4;
        } break;
        case MeshData::Back: {
            vertexOcclusion[0] = 2;
            vertexOcclusion[1] = 2;
            vertexOcclusion[2] = 2;
            vertexOcclusion[3] = 2;
        } break;
        case MeshData::Front: {
            vertexOcclusion[0] = 2;
            vertexOcclusion[1] = 2;
            vertexOcclusion[2] = 2;
            vertexOcclusion[3] = 2;
        } break;
        case MeshData::Right: {
            vertexOcclusion[0] = 3;
            vertexOcclusion[1] = 3;
            vertexOcclusion[2] = 3;
            vertexOcclusion[3] = 3;
        } break;
        case MeshData::Left: {
            vertexOcclusion[0] = 3;
            vertexOcclusion[1] = 3;
            vertexOcclusion[2] = 3;
            vertexOcclusion[3] = 3;
        } break;
    }
    return vertexOcclusion;
}

void Cells::draw(glm::mat4& view) {
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"),
                       1,
                       GL_FALSE,
                       glm::value_ptr(projection));

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"),
                       1,
                       GL_FALSE,
                       glm::value_ptr(view));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexMesh.size(), GL_UNSIGNED_INT, 0);
}


void Cells::progress() {
    countNeighbours();
    generateMesh();
}

// Iterate over all cells and check for neighbours
void Cells::countNeighbours() {
    std::array<std::array<std::array<bool, 100>, 100>, 100> nextCells;
    for (int x{0}; x < cells.size(); ++x) {
        for (int y{0}; y < cells[x].size(); ++y) {
            for (int z{0}; z < cells[x][y].size(); ++z) {
                countNeighbours(x, y, z, nextCells);
            }
        }
    }
    cells.swap(nextCells);
}

// Iterate over all neighbours of a cell and check if they are alive
void Cells::countNeighbours(int ix, int iy, int iz, std::array<std::array<std::array<bool, 100>, 100>, 100>& nextCells) {
    int count{0};
    for (int x{ix - 1}; x <= (ix + 1); ++x) {
        for (int y{iy - 1}; y <= (iy + 1); ++y) {
            for (int z{iz - 1}; z <= (iz + 1); ++z) {
                if ((x == ix && y == iy && z == iz) ||
                    (x < 0 || y < 0 || z < 0) || 
                    (x >= boardWidth || y >= boardWidth || z >= boardWidth)) {
                    continue;
                }
                if (cells[x][y][z]) {
                    ++count;
                }
            }
        }
    }

    if (count == 2) {
        nextCells[ix][iy][iz] = cells[ix][iy][iz];
    } else if (count == 3) {
        nextCells[ix][iy][iz] = true;
    } else if (count >= 4) {
        nextCells[ix][iy][iz] = false;
    } else if (count <= 1){
        nextCells[ix][iy][iz] = false;
    } 
}
