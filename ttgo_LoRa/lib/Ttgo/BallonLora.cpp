/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   BallonLora.cpp
 * Author: rauthier
 * 
 * Created on 4 avril 2024, 15:08
 */

#include "BallonLora.h"

BallonLora::BallonLora() {
}

BallonLora::~BallonLora() {
}

void BallonLora::init(long frequency) {

    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
    LoRa.begin(frequency);
    LoRa.setSpreadingFactor(12);
    LoRa.setCodingRate4(8);
    pinMode(LED, OUTPUT);
    
    // Initialize LoRa with the specified frequency 433,775 Mhz.
    if (!LoRa.begin(433775000)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

}

void BallonLora::send(String message) {

    digitalWrite(LED, 1); // turn the LED
    
    LoRa.beginPacket(); // Démarre la séquence d'envoi d'un paquet.
    LoRa.print(message); // Ecriture des données. Chaque paquet peut contenir jusqu'à 255 octets. 
    LoRa.endPacket(); // Termine la séquence d'envoi d'un paquet.
    
    digitalWrite(LED, 0); // turn the LED

}

String BallonLora::receive(){
    
    String data{""};
    int packetSize = 0;
    
    // Attend la réception d'un packet
    do {
        packetSize = LoRa.parsePacket();
    }while (!packetSize);
    
    digitalWrite(LED,1); // turn the green LED
    while (LoRa.available()) {
            data = LoRa.readString();
    }
    digitalWrite(LED,0); // turn the LED
    return data;
    
}
