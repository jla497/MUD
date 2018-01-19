#include "LoginHandler.h"

LoginHandler::LoginHandler() {
    m_commands.push_back("new");
    m_commands.push_back("load");
    waitingForName = false;
}

void LoginHandler::handle(ConnectionContainer* container, std::string& str) {
    
    
    //here should search user db for valid user
    auto it = std::find_if(m_commands.begin(),m_commands.end(), find_command(str));
    
    if(it != m_commands.end()) {
        //pass command to game
        if (str == "new") {
            std::string getName = "Please enter your user name:\n";

            container->sendToProtocol(getName);

            waitingForName = true;
            
            return;
        }
    }else{
        if (waitingForName) {
            //here we create new user or load user

            container->username = str;
            //if name is valid go to playHandler
            PlayHandler* playHandler = new PlayHandler();

            container->pushToStack(*playHandler);
            //create and load PlayHandler() onto container Handler stack
            waitingForName = false;
        } else {
            userInput = str;
            //container->sendToProtocol(msg);
        }
    }

    return;
}

void LoginHandler::welcome(ConnectionContainer* container) {
    std::stringstream ss;
    std::string msg;
    ss<< "---------------Game Login Handler---------------\n";
    ss<<"Type 'new' to start a new game.";
    msg = ss.str();
    container->sendToProtocol(msg);
}

void LoginHandler::exit(ConnectionContainer* container) {
    std::stringstream ss;
    std::string msg;
    ss<< "Exiting the game...\n";
    msg = ss.str();
    container->sendToProtocol(msg);
}

std::string LoginHandler::getUserInput() {
    std::string res = userInput;
    userInput.clear();
    return res;
}

