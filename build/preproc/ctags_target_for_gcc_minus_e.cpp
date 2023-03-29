# 1 "/home/anderson/Projects/bluetooth_rc_car_esp32/bluetooth_rc_car_esp32.ino"
# 2 "/home/anderson/Projects/bluetooth_rc_car_esp32/bluetooth_rc_car_esp32.ino" 2






BluetoothSerial SerialBT;
char comando;

void setup()
{
    Serial.begin(9600);
    // btSerial.begin(9600);
    SerialBT.begin("Carrinho");

    pinMode(13, 0x03);
    pinMode(27, 0x03);
    pinMode(26, 0x03);
    pinMode(25, 0x03);

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
        digitalWrite(13, 0x1);
        digitalWrite(27, 0x0);
        digitalWrite(26, 0x1);
        digitalWrite(25, 0x0);
        break;
    }
    case 'I':
    { // frente direita
        digitalWrite(13, 0x1);
        digitalWrite(27, 0x0);
        digitalWrite(26, 0x0);
        digitalWrite(25, 0x1);
        break;
    }
    case 'G':
    { // frente esquerda
        digitalWrite(13, 0x0);
        digitalWrite(27, 0x1);
        digitalWrite(26, 0x1);
        digitalWrite(25, 0x0);
        break;
    }
    case 'R':
    { // direita
        digitalWrite(13, 0x1);
        digitalWrite(27, 0x0);
        digitalWrite(26, 0x0);
        digitalWrite(25, 0x0);
        break;
    }
    case 'L':
    { // esquerda
        digitalWrite(13, 0x0);
        digitalWrite(27, 0x0);
        digitalWrite(26, 0x1);
        digitalWrite(25, 0x0);
        break;
    }
    case 'B':
    { // ré
        digitalWrite(13, 0x0);
        digitalWrite(27, 0x1);
        digitalWrite(26, 0x0);
        digitalWrite(25, 0x1);
        break;
    }
    case 'H':
    { // ré esquerda
        digitalWrite(13, 0x0);
        digitalWrite(27, 0x0);
        digitalWrite(26, 0x0);
        digitalWrite(25, 0x1);
        break;
    }
    case 'J':
    { // ré direita
        digitalWrite(13, 0x0);
        digitalWrite(27, 0x1);
        digitalWrite(26, 0x0);
        digitalWrite(25, 0x0);
        break;
    }
    default:
    {
        digitalWrite(13, 0x0);
        digitalWrite(27, 0x0);
        digitalWrite(26, 0x0);
        digitalWrite(25, 0x0);
        break;
    }
    }
}
