int clk  = 11;
int data = 12;
int baud = 200;

void setup() {
  Serial.begin(115200);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
}

void sendOne(int e) {
  digitalWrite(data, HIGH);
  digitalWrite(clk, HIGH);
  delay(baud);
  digitalWrite(clk, LOW);
  if(e) {
    digitalWrite(data, HIGH);
  } else {
    digitalWrite(data, LOW);
  }
  delay(baud);
}

void sendZero(int e) {
  digitalWrite(data, LOW);
  digitalWrite(clk, HIGH);
  delay(baud);
  digitalWrite(clk, LOW);
  if(e) {
    digitalWrite(data, HIGH);
  } else {
    digitalWrite(data, LOW);
  }
  delay(baud);
}

void sendChar(char input) {
  for(int i = 0; i < 9; i++) {
    int b = input & 1;
    if(b) {
      sendOne(i==7);
    } else {
      sendZero(i==7);
    }
    input = input >> 1;
  }
}

void loop() {
  while(!Serial.available()) {
  }
  sendChar(Serial.read());
}
