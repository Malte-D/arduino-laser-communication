int clkPin  = 11;
int dataPin = 12;
int baud = 200;

void setup() {
  Serial.begin(115200);
  pinMode(clkPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void sendData(int data, int byteEnd){
  digitalWrite(dataPin, data);
  digitalWrite(clkPin, HIGH);
  delay(baud);
  digitalWrite(clkPin, LOW);
  if(byteEnd) {
    digitalWrite(dataPin, HIGH);
  } else {
    digitalWrite(dataPin, LOW);
  }
  delay(baud);
}

void sendChar(char input) {
  for(int i = 0; i < 9; i++) {
    int b = input & 1;
    sendData(b,i==7);
    input = input >> 1;
  }
}

void loop() {
  while(!Serial.available()) {
  }
  sendChar(Serial.read());
}
