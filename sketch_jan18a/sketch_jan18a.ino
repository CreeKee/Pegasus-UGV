#include <Servo.h>

Servo ESC; 
uint32_t i = 90;

void setup() {
  // put your setup code here, to run once:
  ESC.attach(10,1000, 2000);
  //ESC.write(90);
  delay(1000);
  //i = 40;

}

void loop () {
  // put your main code here, to run repeatedly:

  
  ESC.write(80);

  delay(5000);

  ESC.write(85);

  delay(5000);

  ESC.write(90);

  delay(5000);

  //while(1);
}
