int laser = 12;	// Nummer des Pins, an dem der Laser angeschlossen ist
int baud = 300;	// Intervall für die Datenübertragung - je kleiner, desto schneller, aber instabiler

void setup() {
  Serial.begin(115200);			// Serielle Schnittstelle initialisieren
  pinMode (laser, OUTPUT);	// Laser-Pin initialisieren 
}

// Sendet eine 1 über den Laser ab.
void sendOne() {
  digitalWrite(laser, HIGH);
  delay(baud / 4 - baud / 5);
  digitalWrite(laser, LOW);
  delay(baud / 4 - baud / 5);
  digitalWrite(laser, HIGH);
  delay(baud - (baud / 4));
  digitalWrite(laser, LOW);
  delay(baud / 4);
  digitalWrite(laser, HIGH);
  delay(10);
  digitalWrite(laser, LOW);
  delay(baud / 10);
}

// Sendet eine 0 über den Laser ab.
void sendZero() {
  digitalWrite(laser, HIGH);
  delay(baud / 4 - baud / 5);
  digitalWrite(laser, LOW);
  delay(baud / 4 - baud / 5);
  digitalWrite(laser, HIGH);
  delay(baud / 4);
  digitalWrite(laser, LOW);
  delay(baud - (baud / 4));
  digitalWrite(laser, HIGH);
  delay(10);
  digitalWrite(laser, LOW);
  delay(baud / 10);
}

// Sendet eine Pause (Byte-Ende) über den Laser ab.
void sendPause() {
  digitalWrite(laser, HIGH);
  delay(baud / 4 - baud / 5);
  digitalWrite(laser, LOW);
  delay(baud / 4 - baud / 5);
  digitalWrite(laser, HIGH);
  delay(baud / 2);
  digitalWrite(laser, LOW);
  delay(baud / 2);
  digitalWrite(laser, HIGH);
  delay(10);
  digitalWrite(laser, LOW);
  delay(baud / 10);
}

// Sendet einen Char über den Laser ab, der als Parameter übergeben wurde.
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

void loop() {
  while(!Serial.available()) {	// Warten, bis serielle Daten annehmbar sind
  }
  sendChar(Serial.read());			// Sende Char für Char die Daten ab
}
