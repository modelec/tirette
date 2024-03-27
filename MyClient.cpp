#include "MyClient.h"

MyClient::MyClient(const char* host, int port) : TCPClient(host, port), tiretteState(false)
{

}


void MyClient::handleMessage(const std::string& message)
{
    // if get tirette => send tiretteState
    if (split(message, ";")[1] == "tirette") {
        if (split(message, ";")[2] == "get tirette_state") {
            const std::string toSend = "tirette;start;set tirette_state;" + std::to_string(*tiretteState);
            this->sendMessage(toSend.c_str());
        }
    }
}

void MyClient::setTiretteState(bool tiretteState)
{
    this->tiretteState = tiretteState;
}
