#include "host.h"

Host::Host()
{
}

string Host::readString(const shared_ptr<Connection>& conn)
{	
	string str;
	unsigned char c;
	while((c = conn->read()) != '$'){
	    str += c;
        }
	return str;
}

/*
 * Send a string to a client.
 */
void Host::writeString(const shared_ptr<Connection>& conn, const string& s)
{
        for (char c : s) {
                conn->write(c);
        }
        conn->write('$');
}

Server Host::init()
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

void Host::makeMove(string& str){
    cout << "Write message to send" << endl;
    cin >> str;
}

int Host::app(std::shared_ptr<Connection> conn, Server& server)
{
        conn = make_shared<Connection>();
        server.registerConnection(conn);
        cout << "New client connects" << endl;
        string str{};
        if (conn != nullptr) {
                try {
                    makeMove(str);
                    writeString(conn, str);
                    sleep(1);
                    string str = readString(conn);
                    cout << "Received message: " << str << endl;
                } catch (ConnectionClosedException&) {
                    server.deregisterConnection(conn);
                    cout << "Client closed connection" << endl;
                    return 0;
                }
        }
        return 0;
}
