int clk = A3;
int data = A2;

int low = 700;

void setup() {
  Serial.begin(115200);
  pinMode(clk, INPUT);
  pinMode(data, INPUT);
}

int fuzzyInput(int pin) {
  if (analogRead(pin) >= low) {
    return 0;
  } else {
    return 1;
  }
}

int fuzzyMed() {
  int sum = 0;
  int n = 0;
  while (fuzzyInput(clk) == 1) {
    n += 1;
    sum += fuzzyInput(data);
    delay(1);
  }
  if (sum >= (n / 2)) {
    return 1;
  } else {
    return 0;
  }
}

int readBit(int *e) {
  int sum = 0;
  int n = 0;
  while (fuzzyInput(clk) == 0) {
    n += 1;
    sum += fuzzyInput(data);
    delay(1);
  }
  if (sum >= n/2 ){
    *e = 1;
  }else{
    *e = 0;
  }
  return fuzzyMed();
}


char readChar(){
  char c = 0;
  int e = 0;
  byte b = readBit(&e);
  while (e==0){
    c = ((c>>1)&127)|(b<<7);
    b = readBit(&e);
  }
  return c;
}

int e = 0;

void loop() {
  /*int b = readBit(&e);
  if (e){
    Serial.println();
  }
  Serial.print(b);*/
  Serial.print(readChar());
}
