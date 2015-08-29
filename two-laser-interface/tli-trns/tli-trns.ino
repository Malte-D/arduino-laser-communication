int clkPin  = 11;	// Nummer des Pins, an dem der Takt-Laser angeschlossen ist
int dataPin = 12;	// Nummer des Pins, an dem der Daten-Laser angeschlossen ist
int baud = 200;		// Intervall für die Datenübertragung - je kleiner, desto schneller, aber instabiler

void setup() {
  Serial.begin(115200);			// Serielle Schnittstelle initialisieren
  pinMode(clkPin, OUTPUT);	// Takt-Pin initialisieren
  pinMode(dataPin, OUTPUT);	// Daten-Pin initialisieren
}

/* Sendet eine 1 oder 0 über die Laser ab. Der Integer byteEnd entscheidet dabei,
	 ob das gerade gesendete Bit das letzte Bit des Bytes war (byteEnd=1), sodass
	 ein Pausensignal gesendet werden soll, oder ob sich das Bit am Anfang oder 
	 in der Mitte des Bytes befindet (byteEnd=0). */
void sendData(int data, int byteEnd) {
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

// Sendet einen Char über den Laser ab, der als Parameter übergeben wurde.
void sendChar(char input) {
  for(int i = 0; i < 9; i++) {
    int b = input & 1;
    sendData(b,i==7);
    input = input >> 1;
  }
}

void loop() {
  while(!Serial.available()) {	// Warten, bis serielle Daten annehmbar sind
  }
  sendChar(Serial.read());			// Sende Char für Char die Daten ab
}
