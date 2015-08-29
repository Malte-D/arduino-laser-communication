int sensorPin = A5;
int sensVal = 0;

int baud = 300;
int fuzzy = (int)baud / 8;
int low = 200;

int debug = 0;

int fuzzyInput() {
  if (analogRead(sensorPin) >= low) {
    return 0;
  } else {
    return 1;
  }
}

char fuzzyRead(int x) {
  if (x >= (baud / 2) - fuzzy && x <= (baud / 2) + fuzzy) {
    return 'S';
  } else if (x >= (baud / 4) - fuzzy && x <= (baud / 4) + fuzzy) {
    return '-';
  } else if (x >= baud - (baud / 4) - fuzzy && x <= baud - (baud / 4) + fuzzy) {
    return '+';
  }
  return '#';
}

int readDuration(int* current) {
  long t = millis();
  while (fuzzyInput() == *current) {}
  *current = fuzzyInput();
  return (int)(millis() - t);
}

byte readBit(int *ct) {
  char last = fuzzyRead(readDuration(ct));
  char current = fuzzyRead(readDuration(ct));
  while (last != '#' || current != '#') {
    last = current;
    current = fuzzyRead(readDuration(ct));
  }

  char s1 = fuzzyRead(readDuration(ct));
  char s2 = fuzzyRead(readDuration(ct));
  char a = fuzzyRead(readDuration(ct));
  char b = fuzzyRead(readDuration(ct));
  if (debug) {
    Serial.print(last);
    Serial.print("_");
    Serial.print(current);
    Serial.print("_");
    Serial.print(s1);
    Serial.print(" ");
    Serial.print(s2);
    Serial.print(" ");
    Serial.print(a);
    Serial.print(" ");
    Serial.println(b);
  }
  if (a == '+' && b == '-') {
    return 1;
  } else if (a == '-' && b == '+') {
    return 0;
  } else if (a == 'S' && b == 'S') {
    return 2;
  } else {
    return 0;
  }
}

char readMaybeChar(int *current){
  char c = 0;
  byte b = readBit(current) | readBit(current);
  while (b<2){
    Serial.print(b);
    c = ((c>>1)&127)|(b<<7);
    b = readBit(current) | readBit(current);
  }
  return c;
}

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
}

int current = 0;

void loop() {
  Serial.print("bits: ");
  byte x  = (byte)readMaybeChar(&current);
  Serial.println();
  Serial.print("received: ");
  Serial.print(x);
  Serial.print(" => ");
  Serial.println((char)x);
}
