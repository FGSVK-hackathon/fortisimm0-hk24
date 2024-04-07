#include <Arduino.h>

void playTone(uint32_t note);
void readBuffer(uint32_t *buffer);
void playChunk();
void playAudioStream();

const unsigned int scale[12] = {262, 277, 293, 311, 330, 349, 370, 392, 415, 440, 466, 494};


void setup()
{
    // PINOUT
    pinMode(PB3, OUTPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);

    // SERIAL INIT
    Serial.begin(9600);
    while (!Serial);
    Serial.flush();
}

void loop()
{
    int b1, b2, b3;
    b1 = digitalRead(A1) == LOW;
    b2 = digitalRead(A2) == LOW;
    b3 = digitalRead(A3) == LOW;

    if (b1)
    {
        for (int i = 0; i < 12; i++)
        {
            tone(PB3, scale[i], 250);
            delay(250);
        }
    }

    if (b3)
    {
        tone(PB3, 440, 2000);
        delay(2000);
    }

    int bytecount;
    if ((bytecount = Serial.available()) >= 16)
    {
        Serial.println(bytecount);
        playChunk();
    }

    if (!Serial)
    {
        Serial.end();
        Serial.begin(9600);
        while (!Serial);
    }
}


void playChunk()
{
    unsigned long buffer[4], dt;
    unsigned int f;

    readBuffer(buffer);

    for (int i = 0; i < 4; i++) {
        playTone(buffer[i]);
    }
}

void readBuffer(uint32_t *buffer)
{
    uint8_t bytes[16];
    Serial.readBytes(bytes, 16);

    int i = 0;
    buffer[i] = 0;
    for (int j = 0; j < 16; j++)
    {
        buffer[i] = buffer[i] << 8;
        buffer[i] = buffer[i] | bytes[j];

        if ((j + 1) % 4 == 0)
        {
            i++;
            buffer[i] = 0;
        }
    }
}

void playTone(uint32_t note)
{
    unsigned long dt = (unsigned long) (note & 0x0000ffff);
    tone(PB3, (unsigned int) (note >> 16), dt);
    delay(dt);
}