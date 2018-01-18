#include "PlayHandler.h"

PlayHandler::PlayHandler() {
	m_commands.push_back("attack");
	m_commands.push_back("defend");
	m_commands.push_back("go up");
	m_commands.push_back("go down");
	m_commands.push_back("go left");
	m_commands.push_back("go right");
	m_commands.push_back("sleep");
	m_commands.push_back("quit");
	outBuffer = "---------------Game Play Handler---------------\n";
	
}

void PlayHandler::handle(ConnectionContainer* container, std::string& str) {
	// if (str=="quit") {
	// 	auto temp = container->m_handlers.pop();
	// 	return;
	// }
	//check if str is one of the commands
	auto it = std::find_if(m_commands.begin(),m_commands.end(), find_command(str));
	
	std::stringstream ss;
	
	std::string msg;
	
	if(it != m_commands.end()) {
		//pass command to game
		ss<<"command: "<<str<<" passed to game...\n";
		msg = ss.str();
		container->m_protocol->sendToBuffer(msg);
	}else{

		ss<<"player "<<container->username<<" says: "<<str<<"\n";
		msg = ss.str();
		container->m_protocol->sendToBuffer(msg);
	}

	return;
}

void PlayHandler::welcome(ConnectionContainer* container) {
	std::stringstream ss;
	std::string msg;
	ss<< "---------------Game Play Handler---------------\n";
	ss<<"Available commands:\n";
	ss<<" attack, defend, go left, go down, go up, go right, quit\n";
	ss<<"Any other strings will be treated as chat\n";
	msg = ss.str();
	container->m_protocol->sendToBuffer(msg);
}

void PlayHandler::exit(ConnectionContainer* container) {
	std::stringstream ss;
	std::string msg;
	ss<< "Exiting the game...\n";
	msg = ss.str();
	container->m_protocol->sendToBuffer(msg);
}

std::string PlayHandler::getOutBuffer() {
	std::string temp = outBuffer;
	outBuffer.clear();
	return temp;
}

