#include "BluetoothSerial.h"

#define motorRight_P1 4
#define motorRight_P2 12
#define motorLeft_P1 32
#define motorLeft_P2 25
#define statusLed 2
// #define buzzer 33

unsigned long previousMillisLed = 0;
// unsigned long previousMillisBuzzerOn = 0;
// unsigned long previousMillisBuzzerOff = 0;

BluetoothSerial SerialBT;
char comando;
char comandoOld = ' ';

// void buzzerBlink(bool on)
// {
//   // unsigned long currentMillis = millis();
//   // int interval = 1000;

//   // static bool buzzer_on = false;
//   if (on)
//   {
//     tone(buzzer, 1000);
//     // if (currentMillis - previousMillisBuzzerOn >= interval && !buzzer_on)
//     // {
//     //   previousMillisBuzzerOn = currentMillis;

//     //   tone(buzzer, 1000); // Send 1KHz sound signal...
//     //   buzzer_on = true;
//     // }

//     // if (currentMillis - previousMillisBuzzerOff >= interval && buzzer_on)
//     // {
//     //   previousMillisBuzzerOff = currentMillis;

//     //   noTone(buzzer);
//     //   buzzer_on = false;
//     // }
//   }
//   else
//   {
//     noTone(buzzer);
//   }
// }

void statusBlink(bool connected)
{
  unsigned long currentMillis = millis();
  int interval = 100;

  if (connected)
  {
    digitalWrite(statusLed, HIGH);
  }
  else if (currentMillis - previousMillisLed >= interval)
  {
    previousMillisLed = currentMillis;

    digitalWrite(statusLed, !digitalRead(statusLed));
  }
}

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
  pinMode(statusLed, OUTPUT);
  // pinMode(buzzer, OUTPUT);

  Serial.println();
  Serial.println();

  Serial.println("Conecte em: Carrinho");

  delay(2000);
}

void loop()
{
  /*

  Forward------------------F

  Back---------------------B

  Left---------------------L

  Right--------------------R

  Forward Left-------------G

  Forward Right------------I

  Back Left----------------H

  Back Right---------------J

  Stop---------------------S

  Front Lights On----------W

  Front Lights Off---------w (lower case)

  Back Lights On-----------U

  Back Lights Off----------u (lower case)

  Horn On------------------V

  Horn Off-----------------v (lower case)

  Extra On-----------------X

  Extra Off----------------x (lower case)

  Speed 0------------------0

  Speed 10-----------------1

  Speed 20-----------------2

  Speed 30-----------------3

  Speed 40-----------------4

  Speed 50-----------------5

  Speed 60-----------------6

  Speed 70-----------------7

  Speed 80-----------------8

  Speed 90-----------------9

  Speed 100----------------q

  Everything OFF-----------D (Tudo desligado)

  */

  statusBlink(SerialBT.connected());

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
    case 'V':
    { // Horn On
      // buzzerBlink(true);

      Serial.println("V - Horn on / Buzina ligada");
      break;
    }
    case 'v':
    { // Horn Off
      // buzzerBlink(false);

      Serial.println("V - Horn off / Buzina desligada");
      break;
    }
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