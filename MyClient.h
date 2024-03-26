#pragma once

#include <TCPSocket/TCPClient.hpp>
#include <TCPSocket/TCPUtils.hpp>

class MyClient : public TCPClient {

public:
    MyClient(bool* tiretteState, const char* host, int port);

    void handleMessage(const std::string& message) override;

    void setTiretteState(bool* tiretteState);
private:
    bool* tiretteState;
};
