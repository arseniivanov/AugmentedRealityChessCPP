#include "chesspiece.h"

ChessPiece::ChessPiece(ChessType* chesstype, cv::Point2f position, bool player, glm::vec3 color)
{
    this->chesstype = chesstype;
    this->position = position;
    this->color = color;
    this->player = player;
    alive = 1;
    selected = 0;
    grave = cv::Point2f(50,50);
}

ChessPiece::ChessPiece()
{
    //placeholder
}



void ChessPiece::render()
{
    if (alive) {
        glBindVertexArray(chesstype->VAO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model,glm::vec3(0.05f, 0.05f, 0.05f));
        model = glm::translate(model, glm::vec3(position.x,position.y,0)); //can move out
        if (player) {
            model = glm::rotate(model, 3.14159f,glm::vec3(0.0f,0.0f,1.0f));
        }
        chesstype->shader.setMat4("model", model); //only needs to be set once for each set of pieces
        chesstype->shader.setVec3("color",color);
        if(selected) {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        glDrawArrays(GL_TRIANGLES, 0, chesstype->verts.size());
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
}

void ChessPiece::move(cv::Point2f newpoint){
    if (chesstype->checkLegality(this->position,newpoint)){
        this->position = newpoint;
    }
}

cv::Point2f ChessPiece::getPosition(){
    return this->position;
}

void ChessPiece::setSelected()
{
    selected = !selected;
}

void ChessPiece::kill()
{
    alive = 0;
    move(grave);
}

