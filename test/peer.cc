#include "peer.h"

Peer::Peer()
{
}


void Peer::writeString(const Connection& conn, string s)
{
	for (auto c : s){
	    conn.write(c);
	}
	conn.write('$');
}

/*
 * Read a string from the server.
 */
string Peer::readString(const Connection& conn)
{
        string s;
        char   ch;
        while ((ch = conn.read()) != '$') {
                s += ch;
        }
        return s;
}

void Peer::makeMove(string& str){
    str = "Peer is answering";
}

int Peer::app(const Connection& conn)
{
        cout << "You are player yellow, wait for your turn" << endl;
        string str;
        try {
            string pwmove = readString(conn);
            cout << "Recieved message: " << pwmove << endl;
            makeMove(str);
            writeString(conn,str);
            sleep(1);
            str = "";
        } catch (ConnectionClosedException&) {
            cout << " no reply from server. Exiting." << endl;
            return 1;
        }
        return 0;
}
