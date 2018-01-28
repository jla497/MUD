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
<<<<<<< HEAD
private:
	networking::Connection conn;
};

typedef std::vector<std::unique_ptr<ConnectionContainer>> ConnectionList;

typedef std::vector<std::unique_ptr<ConnectionContainer>>::iterator it;

/*functor used in searches*/
struct find_container {
	find_container(Connection& conn): conn(conn) {}
	bool operator()(std::unique_ptr<ConnectionContainer>& ptr) {return ptr->getConnection() == conn;}
=======
>>>>>>> daadc40f63c104d98d68f948b73681792c9742b3
private:
	networking::Connection conn;
};

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

	networking::Server server{4000,
	[this](networking::Connection c) {
		printf("New connection found: %lu\n", c.id);
		this->addConnection(c);
	},

	[this](networking::Connection c) {
		printf("Connection lost: %lu\n", c.id);
	}
	                         };

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
<<<<<<< HEAD
	void receiveFromGameManager(std::unique_ptr<gameAndUserMsgs>fromGame);
	
	void passMessages(const std::deque<Message> &incoming);
=======
void receiveFromGameManager(std::unique_ptr<gameAndUserMsgs>fromGame);	

  void passMessages(const std::deque<Message> &incoming);
>>>>>>> daadc40f63c104d98d68f948b73681792c9742b3

	void sendMessages(Server& server);

	void broadCast(Server& server, std::string& broadcast);
};

} //end of namespace connection

#endif