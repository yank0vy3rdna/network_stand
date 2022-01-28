#include <Arduino.h>
#include "UART.h"


UART leftUART(11, 12);



void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(57600);
}

void loop() {
    leftUART.tick();
}
