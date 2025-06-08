// Arduino: zwei Taktsignale (1 Hz und 0,5 Hz) und Ausgang Z plotten

const int clk1Pin = 2;   // 1 Hz → D2
const int clk2Pin = 4;   // 0,5 Hz → D4 (doppelte Periodendauer)
const int zPin     = 3;   // D3 zum Einlesen von Z

bool clk1State = false;
bool clk2State = false;
unsigned long lastToggle1 = 0;
unsigned long lastToggle2 = 0;
const unsigned long interval1 = 500;   // 500 ms high/low → 1 Hz
const unsigned long interval2 = 1000;  // 1000 ms high/low → 0,5 Hz

void setup() {
  pinMode(clk1Pin, OUTPUT);
  pinMode(clk2Pin, OUTPUT);
  pinMode(zPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  // 1 Hz-Taktsignal (D2)
  if (now - lastToggle1 >= interval1) {
    clk1State = !clk1State;
    digitalWrite(clk1Pin, clk1State);
    lastToggle1 = now;
  }

  // 0,5 Hz-Taktsignal (D4)
  if (now - lastToggle2 >= interval2) {
    clk2State = !clk2State;
    digitalWrite(clk2Pin, clk2State);
    lastToggle2 = now;
  }

  // Ausgang Z einlesen
  int z = digitalRead(zPin);

  // Sende Daten an serial Plotter
  Serial.print(clk1State);
  Serial.print(' ');
  Serial.print(clk2State);
  Serial.print(' ');
  Serial.println(z);

    delay(50);  // Kleine Verzögerung für saubere Darstellung
}
