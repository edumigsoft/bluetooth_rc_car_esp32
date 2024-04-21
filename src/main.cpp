#include "BluetoothSerial.h"

#define motorRight_P1 4
#define motorRight_P2 12
#define motorLeft_P1 32
#define motorLeft_P2 25

BluetoothSerial SerialBT;
char comando;
char comandoOld = ' ';

void rightStop()
{
  digitalWrite(motorRight_P1, LOW);
  digitalWrite(motorRight_P2, LOW);
}

void leftStop()
{
  digitalWrite(motorLeft_P1, LOW);
  digitalWrite(motorLeft_P2, LOW);
}

void rightForward()
{
  digitalWrite(motorRight_P1, HIGH);
  digitalWrite(motorRight_P2, LOW);
}

void leftForward()
{
  digitalWrite(motorLeft_P1, HIGH);
  digitalWrite(motorLeft_P2, LOW);
}

void rightBack()
{
  digitalWrite(motorRight_P1, LOW);
  digitalWrite(motorRight_P2, HIGH);
}

void leftBack()
{
  digitalWrite(motorLeft_P1, LOW);
  digitalWrite(motorLeft_P2, HIGH);
}

void setup()
{
  Serial.begin(9600);
  // btSerial.begin(9600);
  SerialBT.begin("Carrinho");

  pinMode(motorRight_P1, OUTPUT);
  pinMode(motorRight_P2, OUTPUT);
  pinMode(motorLeft_P1, OUTPUT);
  pinMode(motorLeft_P2, OUTPUT);

  Serial.println();
  Serial.println();

  Serial.println("Conecte em: Carrinho");

  delay(2000);
}

void loop()
{
  if (SerialBT.available())
  {
    comando = SerialBT.read();

    // Serial.print("comando: ");
    // Serial.println(comando);
  }

  if (comando != comandoOld)
  {
    comandoOld = comando;

    switch (comando)
    {
    case 'F':
    { // Forward / Frente
      rightForward();
      leftForward();

      Serial.println("F - Forward / Frente");
      break;
    }
    case 'B':
    { // Back / Ré
      rightBack();
      leftBack();

      Serial.println("B - Back / Ré");
      break;
    }
    case 'R':
    { // Right / Direita
      rightStop();
      leftForward();

      Serial.println("R - Right / Direita");
      break;
    }
    case 'L':
    { // Left / Esquerda
      rightForward();
      leftStop();

      Serial.println("L - Left / Esquerda");
      break;
    }

    case 'I':
    { // Forward Right / Frente Direita
      rightBack();
      leftForward();

      Serial.println("I - Forward Right / Frente Direita");
      break;
    }
    case 'G':
    { // Forward Left / Frente Esquerda

      rightForward();
      leftBack();

      Serial.println("G - Forward Left / Frente Esquerda");
      break;
    }

    case 'H':
    { // Back Left / Ré Esquerda
      rightStop();
      leftBack();

      Serial.println("H - Back Left / Ré Esquerda");
      break;
    }
    case 'J':
    { // Back Right / Ré Direita
      rightBack();
      leftStop();

      Serial.println("J - Back Right / Ré Direita");
      break;
    }
    case 'S':
      // default:
      { // Stop / Parado
        rightStop();
        leftStop();

        Serial.println("S - Stop / Parado");
        break;
      }
    }
  }
};