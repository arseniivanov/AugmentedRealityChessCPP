#ifndef CHESSTYPE_H_INCLUDED
#define CHESSTYPE_H_INCLUDED

#include <vector>
#include <glm/glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include "./Shader.h"
#include "objloader.hpp"
#include <glm/glm/gtc/type_ptr.hpp>

class ChessType
{
public:
    ChessType(const char* p,Shader& s);
    ~ChessType(){};
    bool initialize();
    bool checkLegality(cv::Point2f a, cv::Point2f b);
    void initmoves(const char* p);
    std::vector<glm::vec3> verts;
	std::vector<glm::vec2> tex;
	std::vector<glm::vec3> norms;
    GLuint VAO;
    GLuint VBO;
    GLuint texbuf;
    Shader& shader;
    std::vector<cv::Point2f> legalmoves;
private:
    std::vector<std::string> choices;
    const char* path;
};

#endif // CHESSOBJECT_H_INCLUDED
