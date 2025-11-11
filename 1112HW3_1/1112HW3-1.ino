/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/
const int buttonPin = 2;
const int RLedPin = 9;
const int GLedPin = 10;
const int BLedPin = 11;

int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000;

int lightNum = 0;

int RLightColor = 255;
int GLightColor = 255;
int BLightColor = 255;
int RCurrentColor = 255;
int GCurrentColor = 255;
int BCurrentColor = 255;

int currentMode = 0;
unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn = true;

const int fadeAmount = 2;
int fadeDirection = 1;
// the setup routine runs once when you press reset:
void setup() 
{
  pinMode(buttonPin, INPUT);
  pinMode(RLedPin, OUTPUT);
  pinMode(GLedPin, OUTPUT);
  pinMode(BLedPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{ 
  checkButton();
  updateLEDColor();
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor);
}
void checkButton(){
  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH && !buttonPressed){
    pressingTime = millis();
    buttonPressed = true;
  }
  if(buttonState == LOW && buttonPressed){
    unsigned long currentTime = millis();
    if(currentTime - pressingTime < longPressInterval){
      changeLEDColor();
    }
    else{
      changeMode();
    }
    buttonPressed = false;
  }
}

void changeMode(){
  currentMode = currentMode + 1;
  if(currentMode >= 3){
    currentMode = 0;
  }
  if(currentMode == 1){
    blinkTimer = 0;
    blinkOn = true;
  }
  if(currentMode == 2){
    fadeDirection = 1;
  }
}

void updateLEDColor(){
  if(currentMode == 0){
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }
  else if(currentMode == 1){
    unsigned long currentTime = millis();
    if(currentTime - blinkTimer > blinkInterval){
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }
    if(blinkOn){
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    }
    else{
      RCurrentColor = 255;
      GCurrentColor = 255;
      BCurrentColor = 255;
    }
  }
  else if(currentMode == 2){
    bool negativeDir = false;
    if(RLightColor == 0){
      RCurrentColor = RCurrentColor + fadeDirection * fadeAmount;
      if(RCurrentColor > (255 - RLightColor) || (RCurrentColor < 0)){
        negativeDir = true;
      }
      if(RCurrentColor < 0) RCurrentColor = 0;
      if(RCurrentColor > 255) RCurrentColor = 255;
    }
    if(GLightColor == 0){
      GCurrentColor = GCurrentColor + fadeDirection * fadeAmount;
      if(GCurrentColor > (255 - GLightColor) || (GCurrentColor < 0)){
        negativeDir = true;
      }
      if(GCurrentColor < 0) GCurrentColor = 0;
      if(GCurrentColor > 255) GCurrentColor = 255;
    }
    if(BLightColor == 0){
      BCurrentColor = BCurrentColor + fadeDirection * fadeAmount;
      if(BCurrentColor > (255 - BLightColor) || (BCurrentColor < 0)){
        negativeDir = true;
      }
      if(BCurrentColor < 0) BCurrentColor = 0;
      if(BCurrentColor > 255) BCurrentColor = 255;
    }
    if(negativeDir)
      fadeDirection = -fadeDirection;

    delay(10);
  }
}

void changeLEDColor(){
  lightNum = lightNum + 1;
  if(lightNum >= 5)
    lightNum = 0;

  if(lightNum == 0){
    //WHITE
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 0;
  }
  if(lightNum == 1){
    //RED
    RLightColor = 0;
    GLightColor = 255;
    BLightColor = 255;
  }
  if(lightNum == 2){
    //GREEN
    RLightColor = 255;
    GLightColor = 0;
    BLightColor = 255;
  }
  if(lightNum == 3){
    //BLUE
    RLightColor = 255;
    GLightColor = 255;
    BLightColor = 0;
  }
  if(lightNum == 4){
    //YELLOW
    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 255;
  }
  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;
}

void setRGBLEDColor(int r, int g, int b){
  analogWrite(RLedPin, r);
  analogWrite(GLedPin, g);
  analogWrite(BLedPin, b);
}