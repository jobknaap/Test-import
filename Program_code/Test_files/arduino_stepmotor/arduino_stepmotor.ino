#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  5

int bluePin = 2;    //IN1 on the ULN2003 Board, BLUE end of the Blue/Yellow motor coil
int pinkPin = 3;    //IN2 on the ULN2003 Board, PINK end of the Pink/Orange motor coil
int yellowPin = 4;  //IN3 on the ULN2003 Board, YELLOW end of the Blue/Yellow motor coil
int orangePin = 5;  //IN4 on the ULN2003 Board, ORANGE end of the Pink/Orange motor coil
//going up
//Keeps track of the current step.
//We'll use a zero based index. 
int currentStep = 0;


int paso [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  
  pinMode(bluePin, OUTPUT);
  pinMode(pinkPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(orangePin,OUTPUT);
  
  digitalWrite(bluePin, LOW);
  digitalWrite(pinkPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(orangePin, LOW);

  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  while((endtime - starttime) <=1500) // do this loop for up to 1000mS
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delayMicroseconds(2250);
    }
    endtime = millis();
}

  
}

void loop() {
    
}
