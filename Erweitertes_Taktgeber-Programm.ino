// Arduino: drei Taktsignale (Eingänge: B,C,D) und Ausgang Z plotten

const int clk1Pin = 2;   // 1 Hz → D2
const int clk2Pin = 3;   // 0,5 Hz → D3
const int clk3Pin = 4;   // 0,25 Hz → D4
const int zPin     = 5;   // D5 zum Einlesen von Z

bool clk1State = false;
bool clk2State = false;
bool clk3State = false;
unsigned long lastToggle1 = 0;
unsigned long lastToggle2 = 0;
unsigned long lastToggle3 = 0;
const unsigned long interval1 = 500;   // 500 ms high/low → 1 Hz
const unsigned long interval2 = 1000;  // 1000 ms high/low → 0,5 Hz
const unsigned long interval3 = 2000;  // 2000 ms high/low → 0,25 Hz


void setup() {
  pinMode(clk1Pin, OUTPUT);
  pinMode(clk2Pin, OUTPUT);
  pinMode(clk3Pin, OUTPUT);
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

  // 0,5 Hz-Taktsignal (D3)
  if (now - lastToggle2 >= interval2) {
    clk2State = !clk2State;
    digitalWrite(clk2Pin, clk2State);
    lastToggle2 = now;
  }

    // 0,25 Hz-Taktsignal (D4)
  if (now - lastToggle3 >= interval3) {
    clk3State = !clk3State;
    digitalWrite(clk3Pin, clk3State);
    lastToggle3 = now;
  }

  // Ausgang Z einlesen
  int z = digitalRead(zPin);

  // Sende Daten an serial Plotter
  Serial.print(clk1State);
  Serial.print(' ');
  Serial.print(clk2State);
  Serial.print(' ');
  Serial.print(clk3State);
  Serial.print(' ');
  Serial.println(z);

    delay(100);  // Verzögerung für Darstellung einer ganzen Periode
}
