#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <sstream>
#include <unistd.h>
#include <memory>
#include <string>

#include "Server.h"
#include "Protocol.h"
#include "ConnectionContainer.h"
// #include "Handler.h"

using namespace networking;

/*functor used in searches*/
struct find_container {
	find_container(Connection conn): conn(conn) {}
	bool operator()(const std::unique_ptr<ConnectionContainer>& ptr) {return ptr->getConnection().id == conn.id;}
private:
	Connection conn;
};

struct gameAndUserInterface {
	std::string text;
	Connection conn;
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

	ConnectionList* m_list;

	std::unique_ptr<Protocol> m_protocol;

	gameAndUserMsgs msgsToGameManager;

	bool done; //set to True to stop run()

	Server server{4000, 
		[this](Connection c) {
			printf("New connection found: %lu\n", c.id);
			this->addConnection(c);
		}, 

		[this](Connection c) {
			printf("Connection lost: %lu\n", c.id);
		}
	};

public:
	ConnectionManager();
//pass signals to server to drop connections
	void dropConnections();

	void addConnection(const Connection c);

//pass incoming Messages from server to connection containers
	void rxFromServer(std::deque<Message> &incoming);

//send Messages to server
	void sendToServer();

//collect and pass msgs from protocols to the GameManager
	gameAndUserMsgs& send2GameManager();

//receive msgs to send from GameManager
// void rxFromGameManager(MsgsPtr);

//run connection manager
	void run();

	void quit();
};


#endif