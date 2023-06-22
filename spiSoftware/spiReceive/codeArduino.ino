int ss = 7;
int sck = 9;
int miso = 10;

void setup() {

  pinMode(ss, INPUT);
  pinMode(sck, INPUT);
  pinMode(miso, INPUT);
  Serial.begin(9600);

}

void loop() {
  
  while (digitalRead(ss) == 1);

  uint8_t i = 0;
  uint8_t data = 0;
  for ( ; i < 8; i++) {
    while (digitalRead(sck) == 0);
    while (digitalRead(sck) == 1);
    if (digitalRead(miso) == 1) data = data | (0x80 >> i);
  }

  Serial.print("data: ");
  Serial.print(data);
  Serial.print("\n");
  while (digitalRead(ss) == 0);

}
