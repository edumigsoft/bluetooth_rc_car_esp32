#include "BluetoothSerial.h"

#define motorRight_P1 4
#define motorRight_P2 12
#define motorLeft_P1 32
#define motorLeft_P2 25
#define statusLed 2
// #define buzzer 33
#define pinEcho 23
#define pinTrigger 5

/*
https://forum.arduino.cc/t/distance-sensor-without-delay/307802/11
*/
// unsigned long duration;           // the time ECHO is HIGH
// int distance;                     // the distance in cms
// unsigned long previousMicros = 0; // will sotre last time TRIGGER was updated
// long OnTime = 10;                 // microseconds of on-time
// long OffTime = 2;                 // microseconds of off-time
// unsigned long viewTime = 200;
// unsigned long previousMillis = 0; // will store last time viewTime was updated
// int triggerState = LOW;           // triggerState used to set it up
/*---------------------------------------------*/

/*
https://randomnerdtutorials.com/esp32-hc-sr04-ultrasonic-arduino/
*/
// define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm = 15;
float distanceInch;
/*----------------------------*/

unsigned long previousMillisLed = 0;
// unsigned long previousMillisBuzzerOn = 0;
// unsigned long previousMillisBuzzerOff = 0;
unsigned long previousMillisDistance = 0;

BluetoothSerial SerialBT;
char comando;
char comandoOld = ' ';

int dutyRight = 0;
int dutyLeft = 0;

// void view()
// { //  pc  data views
//   // Serial.print(distance);
//   // Serial.println("  cm");
//   // // chech to see if it´ time to change the state
//   // unsigned long currentMillis = millis();
//   // if (currentMillis - previousMillis >= viewTime)
//   // {
//   //   previousMillis = currentMillis; // remember the time
//   // }
// }

void readDistance()
{
  // // check to see if it's time to change the state of the TRIGGER
  // unsigned long currentMicros = micros();
  // if ((triggerState == LOW) && (currentMicros - previousMicros >= OffTime))
  // {
  //   triggerState = HIGH;                    // turn it on
  //   previousMicros = currentMicros;         // remember the time
  //   digitalWrite(pinTrigger, triggerState); // update the actual trigger
  // }
  // else if ((triggerState == HIGH) && (currentMicros - previousMicros >= OnTime))
  // {
  //   triggerState = LOW;                     // turn it off
  //   previousMicros = currentMicros;         // remember the time
  //   digitalWrite(pinTrigger, triggerState); // update the actual trigger
  // }
  // duration = pulseIn(pinEcho, HIGH, 1000);
  // distance = duration / 58;
  // view();

  unsigned long currentMillis = millis();
  int interval = 1000;
  if (currentMillis - previousMillisDistance >= interval)
  {
    previousMillisLed = currentMillis;

    // Clears the trigPin
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(pinEcho, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_SPEED / 2;

    // Convert to inches
    distanceInch = distanceCm * CM_TO_INCH;

    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.print("Distance (inch): ");
    Serial.println(distanceInch);
  }
}

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
  analogWrite(motorRight_P1, 0);
  analogWrite(motorRight_P2, 0);
}

void leftStop()
{
  analogWrite(motorLeft_P1, 0);
  analogWrite(motorLeft_P2, 0);
}

void rightForward(int duty)
{
  analogWrite(motorRight_P1, duty);
  analogWrite(motorRight_P2, 0);
}

void leftForward(int duty)
{
  analogWrite(motorLeft_P1, duty);
  analogWrite(motorLeft_P2, 0);
}

void rightBack(int duty)
{
  analogWrite(motorRight_P1, 0);
  analogWrite(motorRight_P2, duty);
}

void leftBack(int duty)
{
  analogWrite(motorLeft_P1, 0);
  analogWrite(motorLeft_P2, duty);
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
  pinMode(pinEcho, INPUT);
  pinMode(pinTrigger, OUTPUT);

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

  // readDistance();

  if (SerialBT.available())
  {
    comando = SerialBT.read();

    // Serial.print("comando: ");
    // Serial.println(comando);
  }

  if (distanceCm < 11)
  {
    rightStop();
    leftStop();

    Serial.println("distanceCm < 11");
  }
  else if (comando != comandoOld)
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
      rightForward(dutyRight);
      leftForward(dutyLeft);

      Serial.println("F - Forward / Frente");
      break;
    }
    case 'B':
    { // Back / Ré
      rightBack(dutyRight);
      leftBack(dutyLeft);

      Serial.println("B - Back / Ré");
      break;
    }
    case 'R':
    { // Right / Direita
      rightStop();
      leftForward(dutyLeft);

      Serial.println("R - Right / Direita");
      break;
    }
    case 'L':
    { // Left / Esquerda
      rightForward(dutyRight);
      leftStop();

      Serial.println("L - Left / Esquerda");
      break;
    }
    case 'I':
    { // Forward Right / Frente Direita
      rightForward(dutyRight / 2);
      leftForward(dutyLeft);

      Serial.println("I - Forward Right / Frente Direita");
      break;
    }
    case 'G':
    { // Forward Left / Frente Esquerda

      rightForward(dutyRight);
      leftForward(dutyLeft / 2);

      Serial.println("G - Forward Left / Frente Esquerda");
      break;
    }
    case 'H':
    { // Back Left / Ré Esquerda
      rightBack(dutyRight / 2);
      leftBack(dutyLeft);

      Serial.println("H - Back Left / Ré Esquerda");
      break;
    }
    case 'J':
    { // Back Right / Ré Direita
      rightBack(dutyRight);
      leftBack(dutyLeft / 2);

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
    case '0':
    { // Speed 0
      dutyRight = 0;
      dutyLeft = 0;

      Serial.println("0 - Speed 0 / Velocidade 0");
      break;
    }
    case '1':
    { // Speed 1
      dutyRight = 110;
      dutyLeft = 110;

      Serial.println("1 - Speed 1 / Velocidade 1");
      break;
    }
    case '2':
    { // Speed 2
      dutyRight = 140;
      dutyLeft = 140;

      Serial.println("2 - Speed 2 / Velocidade 2");
      break;
    }
    case '3':
    { // Speed 3
      dutyRight = 160;
      dutyLeft = 160;

      Serial.println("3 - Speed 3 / Velocidade 3");
      break;
    }
    case '4':
    { // Speed 4
      dutyRight = 180;
      dutyLeft = 180;

      Serial.println("4 - Speed 4 / Velocidade 4");
      break;
    }
    case '5':
    { // Speed 5
      dutyRight = 200;
      dutyLeft = 200;

      Serial.println("5 - Speed 5 / Velocidade 5");
      break;
    }
    case '6':
    { // Speed 6
      dutyRight = 210;
      dutyLeft = 210;

      Serial.println("6 - Speed 6 / Velocidade 6");
      break;
    }
    case '7':
    { // Speed 7
      dutyRight = 220;
      dutyLeft = 220;

      Serial.println("7 - Speed 7 / Velocidade 7");
      break;
    }
    case '8':
    { // Speed 8
      dutyRight = 230;
      dutyLeft = 230;

      Serial.println("8 - Speed 8 / Velocidade 8");
      break;
    }
    case '9':
    { // Speed 9
      dutyRight = 240;
      dutyLeft = 240;

      Serial.println("9 - Speed 9 / Velocidade 9");
      break;
    }
    case 'q':
    { // Speed 10
      dutyRight = 255;
      dutyLeft = 255;

      Serial.println("q - Speed 10 / Velocidade 10");
      break;
    }
    }
  }

  // readDistance();
};