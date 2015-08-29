int baud = 300;

void setup()
{
  pinMode (12, OUTPUT); // define the digital output interface 13 feet
}

void sendOne() {
  digitalWrite(12, HIGH);
  delay(baud / 4 - baud / 5);
  digitalWrite(12, LOW);
  delay(baud / 4 - baud / 5);
  digitalWrite(12, HIGH);
  delay(baud - (baud / 4));
  digitalWrite(12, LOW);
  delay(baud / 4);
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  delay(baud / 10);
}

void sendZero() {
  digitalWrite(12, HIGH);
  delay(baud / 4 - baud / 5);
  digitalWrite(12, LOW);
  delay(baud / 4 - baud / 5);
  digitalWrite(12, HIGH);
  delay(baud / 4);
  digitalWrite(12, LOW);
  delay(baud - (baud / 4));
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  delay(baud / 10);
}

void sendPause() {
  digitalWrite(12, HIGH);
  delay(baud / 4 - baud / 5);
  digitalWrite(12, LOW);
  delay(baud / 4 - baud / 5);
  digitalWrite(12, HIGH);
  delay(baud / 2);
  digitalWrite(12, LOW);
  delay(baud / 2);
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  delay(baud / 10);
}

void sendChar(char input) {
  for(int i = 0; i < 8; i++) {
    int b = input & 1;
    if(b) {
      sendOne();
      sendOne();
    } else {
      sendZero();
      sendZero();
    }
    input = input >> 1;
  }
  sendPause();
  sendPause();
}

void sendInt(int input) {
  for(int i = 0; i < 4; i++) {
    int b = input & 1;
    if(b) {
      sendOne();
    } else {
      sendZero();
    }
    input = input >> 1;
  }
  sendPause();
}

void loop() {
  // 00101100 => ,
  // 01000001 => A
  // 00100001 => !
  sendChar('x');
}
