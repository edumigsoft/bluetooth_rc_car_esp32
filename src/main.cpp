#include "BluetoothSerial.h"

#define pin1 13
#define pin2 27
#define pin3 26
#define pin4 25

BluetoothSerial SerialBT;
char comando;
char comandoOld = ' ';

void setup()
{
  Serial.begin(9600);
  // btSerial.begin(9600);
  SerialBT.begin("Carrinho");

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  Serial.println();
  Serial.println();

  Serial.println("Conecte em: Carrinho");

  Serial.println("Fim Setup");

  delay(2000);
}

void loop()
{
  if (SerialBT.available())
  {
    comando = SerialBT.read();
  }

  if (comando != comandoOld) {
    comandoOld = comando;


    switch (comando)
    {
      case 'F':
        { // Forward / Frente
          digitalWrite(pin1, HIGH);
          digitalWrite(pin2, LOW);
          digitalWrite(pin3, HIGH);
          digitalWrite(pin4, LOW);

          Serial.println("Forward / Frente");
          break;
        }
      case 'I':
        { // Forward Right / Frente Direita
          digitalWrite(pin1, HIGH);
          digitalWrite(pin2, LOW);
          digitalWrite(pin3, LOW);
          digitalWrite(pin4, HIGH);

          Serial.println("Forward Right / Frente Direita");
          break;
        }
      case 'G':
        { // Forward Left / Frente Esquerda
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, HIGH);
          digitalWrite(pin3, HIGH);
          digitalWrite(pin4, LOW);

          Serial.println("Forward Left / Frente Esquerda");
          break;
        }
      case 'R':
        { // Right / Direita
          digitalWrite(pin1, HIGH);
          digitalWrite(pin2, LOW);
          digitalWrite(pin3, LOW);
          digitalWrite(pin4, LOW);

          Serial.println("Right / Direita");
          break;
        }
      case 'L':
        { // Left / Esquerda
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, LOW);
          digitalWrite(pin3, HIGH);
          digitalWrite(pin4, LOW);

          Serial.println("Left / Esquerda");
          break;
        }
      case 'B':
        { // Back / Ré
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, HIGH);
          digitalWrite(pin3, LOW);
          digitalWrite(pin4, HIGH);

          Serial.println("Back / Ré");
          break;
        }
      case 'H':
        { // Back Left / Ré Esquerda
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, LOW);
          digitalWrite(pin3, LOW);
          digitalWrite(pin4, HIGH);

          Serial.println("Back Left / Ré Esquerda");
          break;
        }
      case 'J':
        { // Back Right / Ré Direita
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, HIGH);
          digitalWrite(pin3, LOW);
          digitalWrite(pin4, LOW);

          Serial.println("Back Right / Ré Direita");
          break;
        }
      default:
        { // Stop / Parado
          digitalWrite(pin1, LOW);
          digitalWrite(pin2, LOW);
          digitalWrite(pin3, LOW);
          digitalWrite(pin4, LOW);

          Serial.println("Stop / Parado");
          break;
        }
    }
  }
};