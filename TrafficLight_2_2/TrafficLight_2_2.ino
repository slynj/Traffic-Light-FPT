
int const redNSpin = 4;
int const yelNSpin = 2;
int const greNSpin = 3;
int const redEWpin = 7;
int const yelEWpin = 6;
int const greEWpin = 5;
int const redSpin = 8;
int const yelSpin = 9;
int const greSpin = 10;
int const photoSensor = A0;

// Traffic light constants
int const NS_BOUND = 1;
int const S_BOUND  = 2;
int const EW_BOUND = 3;

// Traffic signal colour constants
int const GREEN  = 1;
int const YELLOW = 2;
int const RED    = 3;

// Traffic On/Off constants
bool const ON  = 1;
bool const OFF = 0;

int current;
int previous = 0;
int sec = 0;

int yelNS = 0;
int greNS = 0;
int redNS = 11;

int yelEW = 0;
int greEW = 0;
int redEW = 1;

bool leftCar = false;


void setup() {
  Serial.begin(9600);

  //NS EW LED pinMode Setup
  for (int i = 2; i < 11; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(photoSensor, INPUT);

}


void loop() {
  current = millis();
  trafficLight();
  leftTurn();
}


bool NorthCycle = false;
bool SouthCycle = false;
int blinkCycle = 0;
int blinkCount = 0;
bool blink = true;


void trafficLight() {
  //counter in seconds (modified from https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay)
  if (current - previous == 500) {
    previous = current;
    sec ++;

    if (leftCar == true && NorthCycle == true && SouthCycle == true) {
      //digitalWrite(redNSpin, LOW);
      trafficLightControl(NS_BOUND, RED, OFF);

      blinkCount++;
      
      if(blink) {
        //digitalWrite(greNSpin, HIGH);
        trafficLightControl(NS_BOUND, GREEN, ON);
        blink = false;
      } else {
        trafficLightControl(NS_BOUND, GREEN, OFF);
        //digitalWrite(greNSpin, LOW);
        blink = true;
        blinkCycle++;
      }
      

      if (blinkCycle > 2) {
        NorthCycle = false;
        SouthCycle = false;
        blinkCycle = 0;
        blinkCount = 0;
        
        greNS = 1;
        redNS = 0;
      }
      

    } else {


      if (greNS > 0) {
        greNS++;
        
        NorthCycle = false;
        trafficLightControl(NS_BOUND, RED, OFF);
        trafficLightControl(NS_BOUND, GREEN, ON);
        
        trafficLightControl(S_BOUND, RED, OFF);
        trafficLightControl(S_BOUND, GREEN, ON);
        
        if (greNS > 7) {
          greNS = 0;
          yelNS = 1;
        }
        
        //digitalWrite(redNSpin, LOW);
        //digitalWrite(greNSpin, HIGH);

        //digitalWrite(redSpin, LOW);
        //digitalWrite(greSpin, HIGH);

        
      }


      if (yelNS > 0) {
        yelNS ++;
        
        if (yelNS > 3) {
          yelNS = 0;
          redNS = 1;
        }
        
        NorthCycle = false;
        
        trafficLightControl(NS_BOUND, GREEN, OFF);
        trafficLightControl(NS_BOUND, YELLOW, ON);
        
        trafficLightControl(S_BOUND, GREEN, OFF);
        trafficLightControl(S_BOUND, YELLOW, ON);
        
        //digitalWrite(greNSpin, LOW);
        //digitalWrite(yelNSpin, HIGH);

        //digitalWrite(greSpin, LOW);
        //digitalWrite(yelSpin, HIGH);

        
      }

      if (redNS > 0) {
        redNS++;
        

        
        trafficLightControl(NS_BOUND, YELLOW, OFF);
        trafficLightControl(NS_BOUND, RED, ON);
        
        trafficLightControl(S_BOUND, YELLOW, OFF);
        trafficLightControl(S_BOUND, RED, ON);
        
        if (redNS > 13) {
          redNS = 0;
          greNS = 1;
          NorthCycle = true;
        }
        //digitalWrite(yelNSpin, LOW);
        //digitalWrite(redNSpin, HIGH);

        //digitalWrite(yelSpin, LOW);
        //digitalWrite(redSpin, HIGH);


      }


      if (greEW > 0) {
        greEW++;
        SouthCycle = false;

        if (greEW > 7) {
          greEW = 0;
          yelEW = 1;
        }
        
        trafficLightControl(EW_BOUND, RED, OFF);
        trafficLightControl(EW_BOUND, GREEN, ON);
        
        //digitalWrite(redEWpin, LOW);
        //digitalWrite(greEWpin, HIGH);

      }

      if (yelEW > 0) {
        yelEW ++;

        if (yelEW > 3) {
          yelEW = 0;
          redEW = 1;
          SouthCycle = true;
        }
        
        trafficLightControl(EW_BOUND, GREEN, OFF);
        trafficLightControl(EW_BOUND, YELLOW, ON);
        
        //digitalWrite(greEWpin, LOW);
        //digitalWrite(yelEWpin, HIGH);

      }

      if (redEW > 0) {
        redEW++;
        
        if (redEW > 13) {
          redEW = 0;
          greEW = 1;
          
        }
        
        trafficLightControl(EW_BOUND, YELLOW, OFF);
        trafficLightControl(EW_BOUND, RED, ON);
        
        //digitalWrite(yelEWpin, LOW);
        //digitalWrite(redEWpin, HIGH);
      }
    }
  }
}


void leftTurn() {
  int value = analogRead(photoSensor);
  if (value > 540) {
    leftCar = true;
  } else {
    leftCar = false;
  }
}


void trafficLightControl(int light, int colour, bool power){
  if(light == 1){
    if(colour == 1){
      digitalWrite(greNSpin, power);
    } else if(colour == 2){
      digitalWrite(yelNSpin, power);
    }else if(colour == 3){
      digitalWrite(redNSpin, power);
    }
  }
  else if(light == 2){
    if(colour == 1){
      digitalWrite(greSpin, power);
    } else if(colour == 2){
      digitalWrite(yelSpin, power);
    }else if(colour == 3){
      digitalWrite(redSpin, power);
    }
  }
  else if(light == 3){
    if(colour == 1){
      digitalWrite(greEWpin, power);
    } else if(colour == 2){
      digitalWrite(yelEWpin, power);
  }else if(colour == 3){
      digitalWrite(redEWpin, power);
    }
  }
}
