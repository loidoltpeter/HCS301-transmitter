//simple keeloq transmitter without rollingCode encryprion (works with every pin)

#define HCS_TX_PIN  12
#define TE          400 //400us bit lenght

void setup()
{
  pinMode(HCS_TX_PIN, OUTPUT);
}

void loop()
{
  hcs301Transmitt(0, 2365235, 34); // transmit every second
  delay(1000);
}

void hcs301Transmitt(uint32_t rollingCode, uint32_t serialNr, uint8_t message) {
  
  //preamble
  for (int i=0; i<12; i++) {
    delayMicroseconds(TE);
    digitalWrite(HCS_TX_PIN, HIGH);
    delayMicroseconds(TE);
    digitalWrite(HCS_TX_PIN, LOW);
  }
  
  //header
  delayMicroseconds(TE*10);
  
  //rollingCode
  for (int i=0; i<32; i++) {
    digitalWrite(HCS_TX_PIN, HIGH);
    if (rollingCode & (1 << i)) {
      delayMicroseconds(TE);
      digitalWrite(HCS_TX_PIN, LOW);
      delayMicroseconds(TE*2);
    }
    else {
      delayMicroseconds(TE*2);
      digitalWrite(HCS_TX_PIN, LOW);
      delayMicroseconds(TE);
    }
  }

  //serialNr
  for (int i=0; i<28; i++) {
    digitalWrite(HCS_TX_PIN, HIGH);
    if (serialNr & (1 << i)) {
      delayMicroseconds(TE);
      digitalWrite(HCS_TX_PIN, LOW);
      delayMicroseconds(TE*2);
    }
    else {
      delayMicroseconds(TE*2);
      digitalWrite(HCS_TX_PIN, LOW);
      delayMicroseconds(TE);
    }
  }
  
  //message
  for (int i=0; i<6; i++) {
    digitalWrite(HCS_TX_PIN, HIGH);
    if (message & (1 << i)) {
      delayMicroseconds(TE);
      digitalWrite(HCS_TX_PIN, LOW);
      delayMicroseconds(TE*2);
    }
    else {
      delayMicroseconds(TE*2);
      digitalWrite(HCS_TX_PIN, LOW);
      delayMicroseconds(TE);
    }
  }
  
  //guard time
  delayMicroseconds(TE*30);
}
