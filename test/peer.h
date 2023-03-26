/* myclient.cc: sample client program */
#ifndef PEER_H_INCLUDED
#define PEER_H_INCLUDED

#include "../connection.h"
#include "../connectionclosedexception.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

using namespace std;

class Peer {
public:
    Peer();
    void writeString(const Connection& conn, string s);
    string readString(const Connection& conn);
    void makeMove(string& str);
    int app(const Connection& conn);
private:
};
#endif // PEER_H_INCLUDED
