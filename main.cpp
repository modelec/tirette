#include <wiringPi.h>
#include <iostream>

#include "MyClient.h"

// Numéro du GPIO connecté à la tirette
#define TIRETTE_GPIO 17

int main() {
    // Initialisation de WiringPi
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Erreur lors de l'initialisation de WiringPi." << std::endl;
        return 1;
    }

    // Configuration du GPIO de la tirette en mode entrée
    pinMode(TIRETTE_GPIO, INPUT);

    pullUpDnControl(TIRETTE_GPIO, PUD_UP);
    bool* tiretteState = new bool(true);

    MyClient client(tiretteState, "127.0.0.1", 8080);

    client.start();

    // Boucle principale
    while (true) {
        int etat = digitalRead(TIRETTE_GPIO);

        if (etat == LOW) {
            std::cout << "Les aimants sont en contact." << std::endl;
            client.sendMessage("tirette;start;set tirette_state;1");
        } else
        {
            std::cout << "Les aimants ne sont pas en contact." << std::endl;
        }

        // Attendre un court délai avant de vérifier à nouveau
        delay(100);
    }

    return 0;
}
