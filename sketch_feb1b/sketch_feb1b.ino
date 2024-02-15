const int read = A0;
const int led = 13;
int value;

void setup()
{
   Serial.begin(9600);
   pinMode(led, OUTPUT);
}

void loop()
{
   value = analogRead(read);

   if (value >= 300){
    digitalWrite(led, HIGH);
   } else {
    digitalWrite(led, LOW);
   }
   delay(100);
}