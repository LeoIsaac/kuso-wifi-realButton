#include <SakuraIO.h>
SakuraIO_I2C sakuraio;

const int BUTTON = 2;
boolean buttonState = 0;
boolean buttonStatePre = 1;

uint32_t count = 0;

void setup() {
  pinMode(BUTTON, INPUT);
  //IoT
  Serial.begin(9600);
  Serial.print("Waiting to come online");
  for(;;) {
    if( (sakuraio.getConnectionStatus() & 0x80) == 0x80 ) break;
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
}

void loop() {
  buttonState = digitalRead(BUTTON);
  if(buttonState != buttonStatePre) {
    if(!buttonState) {
      Serial.println(++count);
      sakuraio.enqueueTx(0, count);
      sakuraio.send();
    }
    buttonStatePre = buttonState;
  }
  delay(10);
}
