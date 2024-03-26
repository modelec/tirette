#include <wiringPi.h>
#include <iostream>

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

    // Boucle principale
    while (true) {
        // Lecture de l'état du GPIO de la tirette
        int etat = digitalRead(TIRETTE_GPIO);

        // Si les aimants ne sont plus en contact, afficher un message
        if (etat == LOW) {
            std::cout << "Les aimants ne sont plus en contact." << std::endl;
            // Vous pouvez exécuter d'autres actions ici
        }

        // Attendre un court délai avant de vérifier à nouveau
        delay(100);
    }

    return 0;
}
