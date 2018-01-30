#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H


#include <sstream>

#include <unistd.h>

#include <memory>
#include <string>
#include "Server.h"
#include "Protocol.h"
#include "ConnectionContainer.h"

namespace connection {

struct gameAndUserInterface {
	std::string text;
	networking::Connection conn;
};

/*functor used in searches*/
struct findGameAndUserInterface {
	findGameAndUserInterface(networking::Connection conn): conn(conn) {}
	bool operator()(const std::unique_ptr<gameAndUserInterface>& ptr) {return ptr->conn.id == conn.id;}
private:
	networking::Connection conn;
};

struct findContainer {
	findContainer(networking::Connection conn): conn(conn) {}
	bool operator()(const std::unique_ptr<ConnectionContainer>& ptr) {return ptr->getConnection().id == conn.id;}

private:
	networking::Connection conn;
};



typedef std::vector<std::unique_ptr<ConnectionContainer>> ConnectionList;

typedef std::vector<std::unique_ptr<ConnectionContainer>>::iterator it;

typedef std::vector<std::unique_ptr<gameAndUserInterface>> gameAndUserMsgs;


/*Connection Manager manages ConnectionContainers.
 Adds new connections and removes connections.
 Passes on or broadcasts incoming and outgoing messages*/
class ConnectionManager {

	// auto onConnect = [this](Connection c) {
	// 	printf("New connection found: %lu\n", c.id);
	// 	this->addConnection(c);
	// };

	// auto onDisconnect = [this](Connection c) {
	// 	printf("Connection lost: %lu\n", c.id);
	// };

	ConnectionList mList;

	bool done; //set to True to stop run()

	networking::Server server;

public:
	ConnectionManager();
//pass signals to server to drop connections
	void dropConnections();

	void addConnection(const networking::Connection c);

//pass incoming Messages from server to connection containers
	void rxFromServer(std::deque<networking::Message> &incoming);

//send Messages to server
	std::deque<networking::Message> sendToServer();

//collect and pass msgs from protocols to the GameManager
	std::unique_ptr<gameAndUserMsgs> sendToGameManager();

//collect and pass msgs from GameManager to ConnectionManager
	void receiveFromGameManager(std::unique_ptr<gameAndUserMsgs>fromGame);

    bool update();
};

} //end of namespace connection

#endif
