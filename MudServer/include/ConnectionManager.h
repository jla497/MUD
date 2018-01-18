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

/*Connection Manager tracks all Connections from the server.
 Adds new connections and removes connections*/
struct find_container{
	find_container(Connection& conn): conn(conn) {}
	bool operator()(std::unique_ptr<ConnectionContainer>& ptr) {return ptr->getConnection() == conn;}
private:
	Connection conn;
};

class ConnectionManager {

typedef std::vector<std::unique_ptr<ConnectionContainer>> ConnectionList;

typedef std::vector<std::unique_ptr<ConnectionContainer>>::iterator it;

ConnectionList m_list;

public:

  void dropConnection(Server& server);

  void addConnection(Connection c);

  void passMessages(const std::deque<Message> &incoming);

  void sendMessages(Server& server);

  void broadCast(Server& server, std::string& broadcast);
};


#endif