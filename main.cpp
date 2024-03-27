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

    MyClient client("127.0.0.1", 8080);

    client.setTiretteState(tiretteState);

    client.start();

    int lastEtat = digitalRead(TIRETTE_GPIO);
    // Boucle principale
    while (true) {
        int etat = digitalRead(TIRETTE_GPIO);

        if (etat == LOW) {
            client.setTiretteState(true);
        } else
        {
            client.setTiretteState(false);
            if (lastEtat != etat) {
                client.sendMessage("tirette;strat;set tirette_state;0");
            }
        }

        // Attendre un court délai avant de vérifier à nouveau
        lastEtat = etat;
        delay(100);
    }

    return 0;
}
