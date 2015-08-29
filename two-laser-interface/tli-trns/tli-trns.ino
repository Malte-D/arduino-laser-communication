int clk  = 11;	// Nummer des Pins, an dem der Takt-Laser angeschlossen ist
int data = 12;	// Nummer des Pins, an dem der Daten-Laser angeschlossen ist
int baud = 200; // Intervall für die Datenübertragung - je kleiner, desto schneller, aber instabiler

void setup() {
  Serial.begin(115200);		// Serielle Schnittstelle initialisieren
  pinMode(clk, OUTPUT);		// Takt-Pin initialisieren
  pinMode(data, OUTPUT);	// Daten-Pin initialisieren
}

/* Sendet eine 1 über die Laser ab. Der Integer e entscheidet dabei, ob
	 das gerade gesendete Bit das letzte Bit des Bytes war (e=1), sodass
	 ein Pausensignal gesendet werden soll, oder ob sich das Bit am Anfang
	 oder in der Mitte des Bytes befindet (e=0). */
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

/* Sendet eine 0 über die Laser ab. Der Integer e entscheidet dabei, ob
	 das gerade gesendete Bit das letzte Bit des Bytes war (e=1), sodass
	 ein Pausensignal gesendet werden soll, oder ob sich das Bit am Anfang
	 oder in der Mitte des Bytes befindet (e=0). */
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

// Sendet einen Char über den Laser ab, der als Parameter übergeben wurde.
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
  while(!Serial.available()) {	// Warten, bis serielle Daten annehmbar sind
  }
  sendChar(Serial.read());			// Sende Char für Char die Daten ab
}
