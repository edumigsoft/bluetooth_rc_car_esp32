#include <Arduino.h>
#line 1 "/home/anderson/Projects/bluetooth_rc_car_esp32/bluetooth_rc_car_esp32.ino"
#include "BluetoothSerial.h"

#define pin1 13
#define pin2 27
#define pin3 26
#define pin4 25

BluetoothSerial SerialBT;
char comando;

#line 11 "/home/anderson/Projects/bluetooth_rc_car_esp32/bluetooth_rc_car_esp32.ino"
void setup();
#line 27 "/home/anderson/Projects/bluetooth_rc_car_esp32/bluetooth_rc_car_esp32.ino"
void loop();
#line 11 "/home/anderson/Projects/bluetooth_rc_car_esp32/bluetooth_rc_car_esp32.ino"
void setup()
{
    Serial.begin(9600);
    // btSerial.begin(9600);
    SerialBT.begin("Carrinho");

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    Serial.println("Fim Setup");

    delay(2000);
}

void loop()
{
    if (SerialBT.available())
    {
        comando = SerialBT.read();
    }

    switch (comando)
    {
    case 'F':
    { // move frente
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);

        Serial.println("Move Frente");
        break;
    }
    case 'I':
    { // frente direita
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);

        Serial.println("Frente Direita");
        break;
    }
    case 'G':
    { // frente esquerda
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);

        Serial.println("Frente Esquerda");
        break;
    }
    case 'R':
    { // direita
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);

        Serial.println("Direita");
        break;
    }
    case 'L':
    { // esquerda
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);

        Serial.println("Esquerda");
        break;
    }
    case 'B':
    { // ré
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);

        Serial.println("Ré");
        break;
    }
    case 'H':
    { // ré esquerda
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);

        Serial.println("Ré Esquerda");
        break;
    }
    case 'J':
    { // ré direita
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);

        Serial.println("Ré Direita");
        break;
    }
    default:
    {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);

        Serial.println("Parado");
        break;
    }
    }
}
