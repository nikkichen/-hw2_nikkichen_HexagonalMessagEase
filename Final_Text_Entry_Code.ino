#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

//Declaring inputs
int pin6 = D6;
int pin5 = D5;
int pin4 = D4;
int pin3 = D3;
int pin2 = D2;
int pin1 = D1;
int pin0 = D0;

int pinMatrix[] = {pin0,pin1,pin2,pin3,pin4,pin5,pin6};
int pinState[7] = {0,0,0,0,0,0,0};//Initialise array of Zeros

//Declaring variables
int firstbutton = 10;
int secondbutton = 10;
int timercount = 0;

//Declaring dictonary
const char* keyMatrix[6][7] = {
  {"a", "b", "d", "", "", "c", ""},
  {"f", "e", "", "h", "", "g", ""},
  {"j", "", "i", "", "l", "k", ""},
  {"", "q", "", "o", "", "r", "v"},
  {"", "", "x", "", "u", "y", "z"},
  {"n", "m", "p", "s", "w", "", "t"},
};

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(pin6, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin0, INPUT_PULLUP);
}

void loop() {
  for(int i = 0; i<7; i++){ //Scan all buttons
    if (digitalRead(pinMatrix[i])==LOW) {
      //Debouncing -- Check if pin is HIGH for entire preset amount of time
      while (digitalRead(pinMatrix[i])==LOW && timercount<10) {
        delay(1);
        timercount = timercount+1;
      }
      //Enter loop only if a HIGH pin is verified to be a button press
      if (timercount >= 10) {
        timercount = 0; //reset timer
        if (pinState[i]==0) { //Enter loop only when there is falling edge
          pinState[i] = 1; //Set specific pinState to 1
          //Serial.print("I received HIGH for pin ");
          //Serial.print(i);
          //Serial.print("\n");
          delay(115); 
            //Storing variables to access dictionary
            //Input SPACE
            if (pinState[6]==1 && (firstbutton==10 || firstbutton<3)) {
              Serial.print(" ");
              firstbutton = 10;
              secondbutton = 10;
            }
            else if (firstbutton == 10){
              firstbutton = i;
              //Serial.print("First Button is ");
              //Serial.print(i);
              //Serial.print("\n");
            } 
            else if (secondbutton == 10){
              secondbutton = i;
              //Serial.print("Second Button is ");
              //Serial.print(i);
              //Serial.print("\n");
              //Access Dictionary when two button inputs are available
              if (firstbutton != 10 && secondbutton != 10) {
                Serial.print(keyMatrix[firstbutton][secondbutton]);
                //Reset button inputs after character is displayed
                firstbutton = 10;
                secondbutton = 10;
              }
            }
  
        }
      }
    }
    else{
      pinState[i] = 0; //Return specific pinState to 0 if button is released
      timercount = 0; //reset timer
    }
  }
}
