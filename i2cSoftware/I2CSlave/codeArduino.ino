#define ADDRESS 0x56 // 86

int scl = 9;
int sda = 10;

uint8_t addReceive = 0;
uint8_t data1 = 0;
uint8_t data2 = 0;

void setup() {

  pinMode(9, INPUT);
  pinMode(10, INPUT);

}

void receiveData(uint8_t *data);
void receiveAddress();
void endCondition();
void ACKTransmit();

void loop() {

    // điều kiện ban đầu  
    while ((digitalRead(scl) == 1) && (digitalRead(scl) == 1)) {

      if (digitalRead(scl) == 0) {

        while(digitalRead(scl) == 1)

        // Nhận đia chỉ
        receiveAddress();

        // nhận bít R/W
        while (digitalRead(scl) == 0);
        while (digitalRead(scl) == 1);

        // bit 1 ~ write
        if (digitalRead(sda) == 1) {

          // Truyền ACK/NACK
          ACKTransmit();

          // Nhận data1
          receiveData(&data1);

          // Truyền ACK/NACK 
          ACKTransmit();

          // Nhận data2
          receiveData(&data2);

          // Truyền ACK/NACK
          ACKTransmit();

          // Điều kiện kết thúc
          endCondition();
  
        } else {
            // to be continued
        }
      }
    }
}
    
void receiveAddress () {

  int i = 0;
  addReceive = 0;

  for ( ; i < 7; i++) {
    while (digitalRead(scl) == 0);
    while (digitalRead(scl) == 1);
    if (digitalRead(sda) == 1) addReceive = addReceive | (1 << (6 - i));
    
  }
}

void receiveData (uint8_t *data) {

  int j = 0;
  *data = 0;

  for ( ; j < 8; j++) {
    while (digitalRead(scl) == 0);
    while (digitalRead(scl) == 1);
    if (digitalRead(sda) == 1) (*data) = (*data) | (1 << (7 - j));

  }
}

void endCondition () {

  while (digitalRead(scl) == 0);
  while ((digitalRead(scl) == 1) && (digitalRead(sda) == 1));

}

void ACKTransmit () {

  pinMode(10, OUTPUT);
  if (data1 != 0) digitalWrite(10, LOW);
  else return;
  while(digitalRead(scl) == 0);
  while (digitalRead(scl) == 1);
  pinMode(10, INPUT);

}



