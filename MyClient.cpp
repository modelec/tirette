#include "MyClient.h"

MyClient::MyClient(const char* host, int port) : TCPClient(host, port), tiretteState(false)
{

}


void MyClient::handleMessage(const std::string& message)
{
    std::cout << "Message received : " << message << std::endl;
    std::vector<std::string> messageSplited = Modelec::split(message, ";");
    // if get tirette => send tiretteState
    if (messageSplited[1] == "tirette" || messageSplited[1] == "all")
    {
        if (messageSplited[2] == "get state") {
            const std::string toSend = "tirette;start;set state;" + std::to_string(tiretteState);
            this->sendMessage(toSend.c_str());
        } else if (messageSplited[2] == "ping") {
            this->sendMessage("tirette;ihm;pong;1");
        }
    }
}

void MyClient::setTiretteState(bool tiretteState)
{
    this->tiretteState = tiretteState;
}
