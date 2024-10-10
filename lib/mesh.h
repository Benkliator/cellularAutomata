#pragma once


struct MeshData {
    const unsigned faceCoords[12];
    const unsigned texCoords[8];
    enum Face : unsigned short {
        Top = 0,
        Bottom,
        Left,
        Right,
        Front,
        Back,
        FullBlock,
    };
    unsigned short face;
};


const MeshData topMeshData = {
    // Vertex Coordinates
    {
        1, 1, 0,
        1, 1, 1,
        0, 1, 1,
        0, 1, 0,
    },
    // Texture Coordinates
    {
        1, 0,
        1, 1,
        0, 1,
        0, 0,
    },
    // What type is block face
    MeshData::Top
};

const MeshData bottomMeshData = {
    // Vertex Coordinates
    {
        0, 0, 0,
        0, 0, 1,
        1, 0, 1,
        1, 0, 0,
    },
    // Texture Coordinates
    {
        0, 0,
        0, 1,
        1, 1,
        1, 0,
    },
    // What type is block face
    MeshData::Bottom
};

const MeshData backMeshData = {
    // Vertex Coordinates
    {
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,
        0, 0, 0,
    },
    // Texture Coordinates
    {
        0, 1,
        0, 0,
        1, 0,
        1, 1,
    },
    // What type is block face
    MeshData::Back
};

const MeshData frontMeshData = {
    // Vertex Coordinates
    {
        1, 1, 1,
        1, 0, 1,
        0, 0, 1,
        0, 1, 1,
    },
    // Texture Coordinates
    {
        0, 0,
        0, 1,
        1, 1,
        1, 0,
    },
    // What type is block face
    MeshData::Front
};

const MeshData leftMeshData = {
    // Vertex Coordinates
    {
        0, 1, 1,
        0, 0, 1,
        0, 0, 0,
        0, 1, 0,
    },
    // Texture Coordinates
    {
        1, 0,
        1, 1,
        0, 1,
        0, 0,
    },
    // What type is block face
    MeshData::Left
};

const MeshData rightMeshData = {
    // Vertex Coordinates
    {
        1, 1, 0,
        1, 0, 0,
        1, 0, 1,
        1, 1, 1,
    },
    // Texture Coordinates
    {
        0, 0,
        0, 1,
        1, 1,
        1, 0,
    },
    // What type is block face
    MeshData::Right
};
