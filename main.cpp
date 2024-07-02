#include <wiringPi.h>
#include <iostream>
#include <atomic>
#include <csignal>

#include <Modelec/CLParser.h>

#include "MyClient.h"

// Numéro du GPIO connecté à la tirette
#define TIRETTE_GPIO 17

std::atomic<bool> shouldStop = false;

void signalHandler(int signum) {
    shouldStop = true;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    // Initialisation de WiringPi
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Erreur lors de l'initialisation de WiringPi." << std::endl;
        return 1;
    }

    // Configuration du GPIO de la tirette en mode entrée
    pinMode(TIRETTE_GPIO, INPUT);

    pullUpDnControl(TIRETTE_GPIO, PUD_UP);

    CLParser clParser(argc, argv);

    int port = clParser.getOption<int>("port", 8080);

    auto host = clParser.getOption("host", "127.0.0.1");

    MyClient client(host, port);

    client.setTiretteState(true);

    try{
        client.start();

        client.sendMessage("tirette;strat;ready;1");

        int lastEtat = digitalRead(TIRETTE_GPIO);
        // Boucle principale
        while (!client.shouldStop() && !shouldStop) {
            int etat = digitalRead(TIRETTE_GPIO);

            if (etat == LOW) {
                client.setTiretteState(true);
            } else {
                client.setTiretteState(false);
                if (lastEtat != etat) {
                    // std::cout << "LETSGO" << std::endl;
                    client.sendMessage("tirette;strat;set state;0");
                }
            }

            // Attendre un court délai avant de vérifier à nouveau
            lastEtat = etat;
            delay(50);
        }
    }
    catch (std::exception& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
