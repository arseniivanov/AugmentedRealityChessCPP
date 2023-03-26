#ifndef HOST_H_INCLUDED
#define HOST_H_INCLUDED

#include "../connection.h"
#include "../connectionclosedexception.h"
#include "../server.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <string>
#include <unistd.h>

using namespace std;

class Host {
public:
    Host();
    void writeString(const shared_ptr<Connection>& conn, const string& s);
    string readString(const shared_ptr<Connection>& conn);
    void makeMove(string& str);
    Server init();
    int app(std::shared_ptr<Connection> conn, Server& server);
private:
    
};
#endif // HOST_H_INCLUDED
