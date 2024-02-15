const int led = 13;
const int read = A0;
int value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(read);
  if (value <= 300) {
    digitalWrite(led, LOW);
    delay(1000);
  } else {
    digitalWrite(led, HIGH);
  }
  delay(100);
}