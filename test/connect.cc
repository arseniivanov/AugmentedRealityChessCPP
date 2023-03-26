#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/opengl.hpp>
#include <opencv2/aruco.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../helpers/objloader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../helpers/stb_image.h"
#include "../helpers/Shader.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <pthread.h>
#include <X11/Xlib.h>
#include <atomic>
#include "../connection.h"
#include "../server.h"

#include "../helpers/chesstype.h"
#include "../helpers/chesspiece.h"

using namespace cv;
using namespace std;

cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

double xpos, ypos;
bool hasinput{0};
bool player;
unsigned int piece;
Point2f readpos;
pthread_cond_t cond;
bool hasmove;
pthread_mutex_t mutexx;
atomic_bool turn;
bool hasreceived;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);

//Transforms symmetric cv::Mat to glm::matN* where N = dimensions.
template <class T>
bool fromCV2GLM(const cv::Mat& cvmat, T& glmmat) {
    auto num = cvmat.rows;
    if (cvmat.cols != num) {
        cout << "Invalid matrix proportions, rows must be equal to cols!" << endl;
        return false;
    }
    memcpy(glm::value_ptr(glmmat), cvmat.data, num*num*sizeof(float));
    glmmat = glm::transpose(glmmat);
    return true;
}

Point2f closestPoint(Point2f& pos, vector<vector<Point2f>>& chessPositions){
    Point2f closest{};
    float val = 100;
    for (auto chessrows : chessPositions) {
        for (auto chesspos : chessrows) {
            float p = 0;
            if ((p = norm(pos-chesspos)) < val) {
                val = p;
                closest = chesspos;
            }
        }
    }
    return closest;
}

Point2f closestPoint(Point2f& pos, float scale, float offset){
    Point2f closest{};
    float diff = 1/scale;
    Point2f newpos = pos * diff + Point2f(offset,offset);
    int floorx = floor(newpos.x);
    int floory = floor(newpos.y);
    int ceilx = ceil(newpos.x);
    int ceily = ceil(newpos.y);
    Point2f ptvec[] = {Point2i(floorx,floory),Point2i(ceilx,floory),Point2i(floorx,ceily),Point2i(ceilx,ceily)};
    float val = 100;
    for (int i = 0; i < 4; ++i) {
        float p = 0;
        if ((p = norm(ptvec[i]-newpos)) < val) {
            val = p;
            closest = ptvec[i];
        }
    }
    return (closest-Point2f(offset,offset))*scale;
}

Point2f shootRay(glm::mat4 &view, glm::mat4& inverseP,glm::vec3& planeNormal,vector<vector<Point2f>>& chessPositions,float w,float h){
    auto inverseV = glm::inverse(view);
    xpos = xpos/w*2-1;
    ypos = ypos/h*2-1;
    auto ray = inverseP*glm::vec4(xpos,-ypos,-1,1); //Y-POS turned!
    ray = inverseV*glm::vec4(ray.x,ray.y,-1,0);
    auto rayDir = glm::normalize(glm::vec3(ray.x,ray.y,ray.z));
    auto camOrigin = glm::vec3(inverseV[3][0],inverseV[3][1],inverseV[3][2]);
    auto t = -(glm::dot(camOrigin,planeNormal)/glm::dot(rayDir,planeNormal));
    auto worldspacepos = glm::vec3(camOrigin + rayDir*t)*19.88f;
    Point2f compPoint = Point2f(worldspacepos[0],worldspacepos[1]);
    return closestPoint(compPoint, chessPositions);
}

int findChessPieceIndex(vector<ChessPiece>& chesspieces, Point2f& pos) {
    auto p = find_if(chesspieces.begin(), chesspieces.end(), [&pos](ChessPiece& arg) { return arg.getPosition() == pos;});
    if (p != chesspieces.cend()){
        return p-chesspieces.cbegin();
    }
    return -1;
}

string readString(Connection& conn)
{	
	string str;
	unsigned char c;
	while((c = conn.read()) != '$'){
        cout << "We read with function: " << c << endl;
	    str += c;
    }
	return str;
}

void sendString(Connection& conn, Point2f& pos, unsigned int selected){
    string s = to_string(pos.x) + " " + to_string(pos.y) + " " + to_string(selected);
    cout << "Sending string to peer: " << s << endl;
    for (unsigned char c : s) {
        conn.write(c);
    }
    conn.write('$');
}

void initializePieces(vector<ChessPiece>& chesspieces, Shader& chessShader, vector<vector<Point2f>>& chessPositions) {
    glm::vec3 p1color = glm::vec3(0.8f,0.0f,0.4f);
    glm::vec3 p2color = glm::vec3(1.0f,1.0f,0.0f);

    ChessType knight = ChessType("models/knight.obj",chessShader); 
    ChessType tower = ChessType("models/tower.obj",chessShader);
    ChessType pawn = ChessType("models/pawn.obj",chessShader); 
    ChessType bishop = ChessType("models/bishop.obj",chessShader); 
    ChessType queen = ChessType("models/queen.obj",chessShader);
    ChessType king = ChessType("models/king.obj",chessShader);
    int tot = 0;
    for (int i = 0; i < 8 ; ++i) {
        chesspieces[tot++] = ChessPiece(&pawn, chessPositions[1][i], 0, p1color);
    }
    chesspieces[tot++] = ChessPiece(&tower, chessPositions[0][0], 0, p1color);
    chesspieces[tot++] = ChessPiece(&knight, chessPositions[0][1], 0, p1color);
    chesspieces[tot++] = ChessPiece(&bishop, chessPositions[0][2], 0, p1color);
    chesspieces[tot++] = ChessPiece(&king, chessPositions[0][3], 0, p1color);
    chesspieces[tot++] = ChessPiece(&queen, chessPositions[0][4], 0, p1color);
    chesspieces[tot++] = ChessPiece(&bishop, chessPositions[0][5], 0, p1color);
    chesspieces[tot++] = ChessPiece(&knight, chessPositions[0][6], 0, p1color);
    chesspieces[tot++] = ChessPiece(&tower, chessPositions[0][7], 0, p1color);
    
    for (int i = 0; i < 8 ; ++i) {
        chesspieces[tot++] = ChessPiece(&pawn, chessPositions[6][i], 1, p2color);
    }
    chesspieces[tot++] = ChessPiece(&tower, chessPositions[7][0], 1, p2color);
    chesspieces[tot++] = ChessPiece(&knight, chessPositions[7][1], 1, p2color);
    chesspieces[tot++] = ChessPiece(&bishop, chessPositions[7][2], 1, p2color);
    chesspieces[tot++] = ChessPiece(&king, chessPositions[7][3], 1, p2color);
    chesspieces[tot++] = ChessPiece(&queen, chessPositions[7][4], 1, p2color);
    chesspieces[tot++] = ChessPiece(&bishop, chessPositions[7][5], 1, p2color);
    chesspieces[tot++] = ChessPiece(&knight, chessPositions[7][6], 1, p2color);
    chesspieces[tot++] = ChessPiece(&tower, chessPositions[7][7], 1, p2color);
}

void readCamera(VideoCapture& cap, Mat& cameraMatrix, vector<float>& distCoeffs,string name) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Mat img;
    cap.read(img);
    const char* cstring = name.c_str();
    float w{static_cast<float>(img.cols)},h{static_cast<float>(img.rows)};
    float near{0.1}, far{100};
    Mat opengl_mtx = (Mat_<float>(4,4)<<2*cameraMatrix.at<float>(0,0)/w,0.0,(w-2*cameraMatrix.at<float>(0,2))/w,0.0,
                            0.0,2*cameraMatrix.at<float>(1,1)/h,-(h-2*cameraMatrix.at<float>(1,2))/h,0.0,
                            0.0,0.0,(-far-near)/(far-near),-2*far*near/(far-near),
                            0.0,0.0,-1.0,0.0);
    GLFWwindow* window = glfwCreateWindow(w, h, cstring, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    Shader textureShader("shaders/textureShader.vs", "shaders/textureShader.fs");
    Shader gridShader("shaders/gridShader.vs", "shaders/gridShader.fs"); 
    Shader chessShader("shaders/chessShader.vs","shaders/chessShader.fs");
    
          
      //Vertices for background
      float vertices[] = {
        // positions          // colors           // texture coords
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // top right
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // top left 
      };
      unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
      };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
        
    unsigned int texture = 0;
    glGenTextures(1, &texture); //Generate the background texture space.
    
    //Chess-grid
    
    std::vector<glm::vec3> verts;
    std::vector<glm::uvec4> inds;
    int slices = 8;
    int length = 0;

    for(int j=0; j<=slices; ++j) { //change to -4 -> 4 etc
        for(int i=0; i<=slices; ++i) {
        float x = (float)i/(float)slices;
        float y = (float)j/(float)slices;;
        float z = 0;
        verts.push_back(glm::vec3(x, y, z));
        }
    }

    for(int j=0; j<slices; ++j) {
        for(int i=0; i<slices; ++i) {

        int row1 =  j    * (slices+1);
        int row2 = (j+1) * (slices+1);

        inds.push_back(glm::uvec4(row1+i, row1+i+1, row1+i+1, row2+i+1));
        inds.push_back(glm::uvec4(row2+i+1, row2+i, row2+i, row1+i));

        }
    }
    int framebuffer_width, framebuffer_height;
	glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    unsigned int gridFBO;
    glGenFramebuffers(1, &gridFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, gridFBO);
    unsigned int gridTex;
    glActiveTexture(GL_TEXTURE3);
    glGenTextures(1, &gridTex);
    glBindTexture(GL_TEXTURE_2D, gridTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, framebuffer_width, framebuffer_height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gridTex, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    unsigned int gridVAO;
    glGenVertexArrays( 1, &gridVAO );
    glBindVertexArray( gridVAO );

    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, verts.size()*sizeof(glm::vec3), glm::value_ptr(verts[0]), GL_STATIC_DRAW );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint ibo;
    glGenBuffers( 1, &ibo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, inds.size()*sizeof(glm::uvec4), glm::value_ptr(inds[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    length = (GLuint)inds.size()*4;
    
    //Initialize variables used in every loop but not dependent on loop
    cv::Mat image;
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<cv::Vec3d> rvecs, tvecs;
    cv::Mat R;
    
    //TODO Change to relative world space positions so that all pieces can translate properly
    vector<vector<Point2f>> chessPositions(8,vector<Point2f>(8));
    float xscalar = 1.25;
    float yscalar = 1.25;
    float x = -xscalar*3.5;
    float y = -yscalar*3.5;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            chessPositions[i][j] = Point2f(x,y);
             cout << "(" << chessPositions[i][j].x << "," << chessPositions[i][j].y << ") ";
            y += yscalar;
        }
         cout << endl;
        x += xscalar;
        y = -yscalar*3.5;
    }
    //Initialize geometry transformations.
                
    glm::mat4 projection    = glm::mat4(1.0f);
    fromCV2GLM(opengl_mtx,projection);
    
    glm::mat4 gridModel = glm::mat4(1.0f);
    gridModel = glm::scale(gridModel,glm::vec3(0.5f, 0.5f, 0.5f)); //Scale down to half it's size
    gridModel = glm::translate(gridModel, glm::vec3(-0.5f,-0.5f,0)); //Translate to middle
    
    gridShader.use();
    gridShader.setVec3("color",glm::vec3(0,1,1));
    gridShader.setMat4("projection", projection); 
    gridShader.setMat4("model", gridModel);
    
    chessShader.use();
    chessShader.setMat4("projection", projection); // note: move out and send reference
    
    vector<ChessPiece> chesspieces = vector<ChessPiece>(32,ChessPiece());
    chesspieces.reserve(32);
    initializePieces(chesspieces, chessShader, chessPositions);
    
    int selected{0};
    bool startedplacing{0};
    auto inverseP = glm::inverse(projection);
    auto planeNormal = glm::vec3(0.0f,0.0f,1.0f);
    
    while (cap.grab()) {
        glm::mat4 view = glm::mat4(1.0f); //Putting view matrix outside leads to objects locking onto position when aruco not detected as view keeps old value.
        cap.retrieve(image);
        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        if (ids.size() > 0) {
            cv::aruco::estimatePoseSingleMarkers(corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
            cv::Rodrigues(rvecs[0], R); // make sure to initialize matrix to identity matrix first
            R = R.t();
            for (int i = 0; i < 3; ++i){
                view[i][0] = R.at<double>(i,0);
                view[i][1] = -R.at<double>(i,1);
                view[i][2] = -R.at<double>(i,2);
            }
            view[3][0] = tvecs[0][0];
            view[3][1] = -tvecs[0][1];
            view[3][2] = -tvecs[0][2];
            glfwPollEvents();
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, (image.step & 3) ? 1 : 4); //Remove openCV padding
            cv::flip(image, image, 0); //Flip image as openCV read up-side-down.
            glBindTexture(GL_TEXTURE_2D, texture);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Set texture clamping method
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                            0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                            GL_RGBA,            // Internal colour format to convert to
                            image.cols,          // Image width  i.e. 640 for Kinect in standard mode
                            image.rows,          // Image height i.e. 480 for Kinect in standard mode
                            0,                 // Border width in pixels (can either be 1 or 0)
                            GL_BGR, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                            GL_UNSIGNED_BYTE,  // Image data type
                            image.ptr());        // The actual image data itself
            //Draw frame
            textureShader.use();
            textureShader.setInt("ourTexture", 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // render scene
            
            //render grid
            glEnable(GL_DEPTH_TEST);
            gridShader.use();
            gridShader.setMat4("view", view);
            gridShader.setVec3("color",glm::vec3(0,1,1));
            
            glBindVertexArray(gridVAO);
            glLineWidth(5);
            glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, NULL);
            
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            
            //Draw pawns
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            glLineWidth(1);
            chessShader.use();
            chessShader.setMat4("view", view);
            for (auto& p : chesspieces){
                p.render();
            }
            glDisable(GL_DEPTH_TEST);
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glBindTexture(GL_TEXTURE_2D,0);
            if (turn) {
                if(hasinput && startedplacing) {
                    auto pos = shootRay(view,inverseP,planeNormal,chessPositions,w,h);
                    int targetidx = findChessPieceIndex(chesspieces, pos);
                    if (selected == targetidx) {
                        //Checks if player clicked onto themselves(illegal move)
                        //Add statement to check if it's your own piece (player field)
                    } else {
                        if (targetidx >= 0) {
                            chesspieces[targetidx].kill();
                        }
                        chesspieces[selected].move(pos);
                        chesspieces[selected].setSelected();
                        
                        piece = selected;
                        readpos = pos;
                        hasmove = 1;
                        pthread_cond_signal(&cond);
                        startedplacing = 0;
                    }
                    hasinput = 0;
                }
                
                if (hasinput) {
                    hasinput = 0;
                    auto pos = shootRay(view,inverseP,planeNormal,chessPositions,w,h);
                    //Highlight piece
                    selected = findChessPieceIndex(chesspieces, pos);
                    if (selected >= 0) {
                        chesspieces[selected].setSelected();
                        startedplacing = 1;
                    }
                }
            } else {
                if (hasreceived) {
                    int targetidx = findChessPieceIndex(chesspieces, readpos);
                    if (targetidx >= 0) {
                        chesspieces[targetidx].kill();
                    }
                    chesspieces[piece].move(readpos);
                    hasmove = 0;
                    hasreceived = 0;
                    turn = !turn;
                    pthread_cond_signal(&cond);
                }
            }
        glfwSwapBuffers(window);
        waitKey(1);
        }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action,int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
       glfwGetCursorPos(window, &xpos, &ypos);
       hasinput = 1;
    }
}


Connection initConnection()
{
        string hostname = "localhost";
        int portnum = 5555;

        int port = -1;
        try {
                port = portnum;
        } catch (exception& e) {
                cerr << "Wrong port number. " << e.what() << endl;
                exit(2);
        }

        Connection conn(hostname.c_str(), port);
        if (!conn.isConnected()) {
                cerr << "Connection attempt failed" << endl;
                exit(3);
        }

        return conn;
}

Server initserver()
{
    string servername = "server";
    int portnum = 5555;
    int port = -1;
    try {
            port = portnum;
    } catch (exception& e) {
            cerr << "Wrong format for port number. " << e.what() << endl;
            exit(2);
    }

    Server server(port);
    if (!server.isReady()) {
            cerr << "Server initialization error." << endl;
            exit(3);
    }
    return server;
}


void connect(Connection& conn){
    while (true) {
        if (turn) {
            pthread_mutex_lock(&mutexx);
            while(!hasmove){
                pthread_cond_wait(&cond, &mutexx); 
            }
            hasmove = 0;
            sendString(conn, readpos, piece);
            turn = !turn;
            pthread_mutex_unlock(&mutexx);
        } else {
            if (!hasreceived) {
                float tox{0}, toy{0};
                string s = readString(conn);
                stringstream ss(s);
                ss >> tox >> toy >> piece;
                readpos = Point2f(tox,toy);
                hasreceived = 1;
            } else {
                pthread_mutex_lock(&mutexx);
                while(hasreceived){
                    pthread_cond_wait(&cond, &mutexx);
                }
                pthread_mutex_unlock(&mutexx);
            }
        }
    }
}

int main() {
    cout << "Do you want to connect as a client(C) or server(S)" << endl;
    string ans;
    cin >> ans;
    pthread_t connThread;
    int rc;
    void* status;
    hasreceived = 0;
    if (pthread_cond_init(&cond, NULL) != 0) {                                    
        perror("pthread_cond_init() error");                                        
        exit(1);                                                                    
    }   
    if (ans == "S") {
        turn = 1;
        cv::Mat externalK = (Mat_<float>(3,3)<<1547.038722311687,0,659.4744524143695,
                        0,1583.854520845913,295.1216850506685,
                        0,0,1);
        auto distCoeffs = vector<float>({0.219034539356992, -0.6346636823652466, -0.04585683802963259, 0.01250174835874109, 1.94289676473369});
        VideoCapture extCam(0);
        auto server = initserver();
        auto conn = server.waitForActivity();
        conn = make_shared<Connection>();
        server.registerConnection(conn);
        rc = pthread_create(&connThread,NULL,(void*(*)(void*))&connect,&*conn);
        readCamera(extCam,externalK,distCoeffs,"External camera");
        rc = pthread_join(connThread, &status);
    } else {
        turn = 0;
        cv::Mat integratedK = (Mat_<float>(3,3)<<710.8178033515675, 0, 327.7446564862798,
                                    0, 714.9098093492465, 235.0741793299097,
                                    0, 0, 1);
        auto integratedDistCoeff = vector<float>({0.321775410633268, -1.857658222446384, 0.00680723620842942, 0.005285311234614084, 3.099809152134044});
        VideoCapture compCam(2);
        Connection conn = initConnection();
        rc = pthread_create(&connThread,NULL,(void*(*)(void*))&connect,&conn);
        readCamera(compCam,integratedK,integratedDistCoeff,"Internal camera");
        rc = pthread_join(connThread, &status);
    }
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);
    return 0;
}
