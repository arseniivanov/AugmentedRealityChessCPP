#ifndef CHESSPIECE_H_INCLUDED
#define CHESSPIECE_H_INCLUDED

#include <glm/glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "chesstype.h"
#include <iostream>

class ChessPiece
{
public:
    ChessPiece(ChessType* chessType, cv::Point2f position, bool player, glm::vec3 color);
    ChessPiece();
    ~ChessPiece(){};
    void render();
    void kill();
    void move(cv::Point2f newpos);
    cv::Point2f getPosition();
    void setSelected();
    bool operator==(const ChessPiece& input)
    {
        return this->position == input.position;
    }
    bool operator!=(const ChessPiece& input)
    {
        return this->position != input.position;
    }
private:
    ChessType* chesstype;
    cv::Point2f position;
    cv::Point2f grave;
    bool player;
    glm::vec3 color;
    bool alive;
    bool selected;
};


#endif // CHESSOBJECT_H_INCLUDED

