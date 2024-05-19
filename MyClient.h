#pragma once

#include <Modelec/TCPClient.h>
#include <Modelec/Utils.h>

class MyClient : public TCPClient {

public:
    MyClient(const char* host, int port);

    void handleMessage(const std::string& message) override;

    void setTiretteState(bool tiretteState);
private:
    bool tiretteState;
};
