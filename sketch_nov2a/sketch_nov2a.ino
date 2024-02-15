#include <Servo.h>

#define WATERSENSOR A0
#define WETTHRESH 300

#define BUTTONDELAY 100000

#define FORWARD 0
#define LEFT 1
#define RIGHT 2

#define ACTIONCOUNT 4

#define WHEELSSTRAIGHT 80
#define WHEELSLEFT 108
#define WHEELSRIGHT 60

#define SETFORWARD(t) FORWARD, t
#define SETLEFT(t) LEFT, t
#define SETRIGHT(t) RIGHT, t

#define LEDPIN 12
#define IPIN 2

#define LOWSPEED 70
#define MEDSPEED 87
#define HIGHSPEED 94

volatile int flag = 0;

Servo myservo;
Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin
int i = 0;
int x = 0;
int buttonPress = 0;
int actionSelect = 0;

unsigned long previousMillis = 0;

int actions1[][4] ={{SETFORWARD(1000)},{SETLEFT(1000)},{SETRIGHT(1000)},{SETLEFT(1000)}};

int actions2[][3] = {{LOWSPEED, SETFORWARD(5000)},{MEDSPEED, SETFORWARD(5000)},{HIGHSPEED, SETFORWARD(5000)}};

void* actionList = {actions, actions2};
int** actions = actions1;

#define DACT(delay) {\
    if (currentMillis - previousMillis >= delay) {\
      previousMillis = currentMillis;\
      x=(x+1)%4;\
    }\
}\

void setup() {
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000);

  //Attach steering servo on pin 10
  myservo.attach(10, 500, 2500);

  //set 
  pinMode(LEDPIN, OUTPUT);

  //set up IPIN for (active low) interrupt
  pinMode(IPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IPIN), myisr, CHANGE);
   // (pin, min pulse width, max pulse width in microseconds) 
 
  //myservo.write(90);
  delay(1000);
  //myservo.write(120);
}

void loop() {
  //ESC.write(i);    // Send the signal to the ESC
  //myservo.write(i);
  //delay(20);
  unsigned long currentMillis = millis();
  
  //set speed
  ESC.write(actions[x][0]);

  //select action
  switch(actions[x][1]){
    case FORWARD:
      myservo.write(WHEELSSTRAIGHT);
      break;
    
    case LEFT:
      myservo.write(WHEELSLEFT);
      break;

    case RIGHT:
      myservo.write(WHEELSRIGHT);
      break;

    default:
      myservo.write(WHEELSSTRAIGHT);
      break;
  }

  //check if it is time to move to the next action
  DACT(actions[x][1]);
  
  
  if(analogRead(WATERSENSOR)>WETTHRESH){
    while(!buttonPress){
      signalHit();
    }
  }

  if(buttonPress){
    handleButtonPress()
  }

  /*
  while(flag){
    i = !i;
    digitalWrite(LEDPIN, 1);
    delay(500);
  }
  */
  
  //i = (i+1)%180;

}

void handleButtonPress(){

  //select next action list and reset index to 0th position
  actions = (int**)(actionList[(++actionSelect)%ACTIONCOUNT])
  x = 0;

  //ensure no button bounce or long-press issues
  for(int i = 0; i < BUTTONDELAY; i++);

  //clear flag and reset timer
  buttonPress = 0;
  previousMillis = currentMillis;

  /*Led indicator to indicate what mode is currently selected?*/
}

void myisr(){
  /*while(1){
    flag = !flag;
    digitalWrite(LEDPIN, flag);
    delay(500);
  }*/
  buttonPress = 1;
}