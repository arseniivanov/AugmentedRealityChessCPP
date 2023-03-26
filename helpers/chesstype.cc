#include "chesstype.h"

ChessType::ChessType(const char* p, Shader& s) : shader(s) {
    path = p;
    choices = {"pawn","knight","bishop","king","queen","tower"};
    initialize();
    initmoves(p);
};

bool ChessType::initialize() {
    bool res = loadOBJ(path, verts, tex, norms);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData( GL_ARRAY_BUFFER, verts.size()*sizeof(glm::vec3), glm::value_ptr(verts[0]), GL_STATIC_DRAW );
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);
    
	glGenBuffers(1, &texbuf);
	glBindBuffer(GL_ARRAY_BUFFER, texbuf);
	glBufferData(GL_ARRAY_BUFFER, tex.size() * sizeof(glm::vec2), &tex[0], GL_STATIC_DRAW);
    glVertexAttribPointer(
        1,                                // attribute
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return res;
}

bool ChessType::checkLegality(cv::Point2f a, cv::Point2f b)
{
    return true;
}

void ChessType::initmoves(const char* p)
{
    std::string s = std::string(p);
    unsigned int i = 0;
    for (; i<6 ; ++i){
        if (s.compare(choices[i])) {
            break;
        }
    }
    switch(i) {
        case(0):
            //pawnmoves
        case(1):
            //knightmoves
        case(2):
            //bishop
        case(3):
            //king
        case(4):
            //queen
        case(5):
            //tower
        default: ;
    }
    
}
