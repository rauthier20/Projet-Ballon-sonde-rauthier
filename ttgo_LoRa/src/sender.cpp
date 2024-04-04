/* 
 * File:   gateway.cpp
 * Author: rauthier
 *
 * Created on 8 février 2024, 09:51
 */

#include <Arduino.h>

#include <BallonLora.h>
#include <Afficheur.h>

BallonLora bl;
char receivedString[50];
int id = 0;

void setup() {

    Serial.begin(9600);
    
    while (!Serial);

    
    bl.init();
    afficheur.init();
    
    afficheur.afficher("Sender\nDone");
    
    Serial.println("Setup done");
    Serial.println("LoRa Sender");
}

void loop() {



    while (Serial.available() > 0) {

        // Lit le caractère suivant
        char incomingCharacter = Serial.read();

        // Vérifie si le caractère reçu est un retour à la ligne ou une nouvelle ligne
        if (incomingCharacter == '\n' || incomingCharacter == '\r') {
            // Si c'est le cas, ajoute un caractère de fin de chaîne
            receivedString[id] = '\0';

            // Affiche la chaîne reçue sur le port série
            Serial.print("Chaîne reçue : ");
            Serial.println(receivedString);

            Serial.print("index : ");
            Serial.println(id);

            afficheur.afficher(String(receivedString));


            // send message
            bl.send(receivedString);

            // réponse
            Serial.println("OK");

            // Réinitialise l'index pour la prochaine lecture
            id = 0;
        } else {
            // Si ce n'est pas un caractère de fin de ligne, ajoute le caractère à la chaîne
            receivedString[id] = incomingCharacter;
            // Passe au caractère suivant dans la chaîne
            id++;

            // Vérifie si la longueur maximale de la chaîne est atteinte
            if (id >= 49) {
                // Ajoute un caractère de fin de chaîne
                receivedString[id] = '\0';
                // Affiche la chaîne reçue sur le port série
                Serial.println("Chaîne reçue : " + String(receivedString));
                bl.send(receivedString);
                // Réinitialise l'index pour la prochaine lecture
                id = 0;
            }

        }


    }

}

