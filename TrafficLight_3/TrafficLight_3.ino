// pin number setup
int const redNSpin    = 4;
int const yelNSpin    = 2;
int const greNSpin    = 3;
int const redEWpin    = 7;
int const yelEWpin    = 6;
int const greEWpin    = 5;
int const redSpin     = 8;
int const yelSpin     = 9;
int const greSpin     = 10;
int const redPEDpin   = 11;
int const grePEDpin   = 12;
int const butPEDpin   = 13;
int const photoSensor = A0;

// Traffic light constants
int const NS_BOUND = 1;
int const S_BOUND  = 2;
int const EW_BOUND = 3;
int const PED      = 4;

// Traffic signal colour constants
int const GREEN  = 1;
int const YELLOW = 2;
int const RED    = 3;

// Traffic On/Off constants
bool const ON  = 1;
bool const OFF = 0;

// Counter variables
int current;
int previous = 0;

// Starting counter numbers for each traffic lights
int yelNS = 0;
int greNS = 0;
int redNS = 11;

int yelEW = 0;
int greEW = 0;
int redEW = 1;

// Init left car to false
bool leftCar = false;

bool butPED = false;

void setup() {
  Serial.begin(9600);

  //NS EW LED pinMode Setup
  for (int i = 2; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  
  // Photoresistor Sensor and PED button Setup
  pinMode(photoSensor, INPUT);
  pinMode(butPEDpin, INPUT);

}


void loop() {
  // Refresh counter variable to contain the current millisecond
  current = millis();
  // Refresh traffic light (colour/ON OFF)
  trafficLight();
  // Refresh left car status (photoresistor sensor)
  leftTurn();
  // Refresh PED button status
  trafficLight_Ped();
}


// Traffic Light Cycle status boolean (if 1 cycle is finished or not)
bool NorthCycle = false;
bool SouthCycle = false;

// Blink Cycle Counter variable (counts how many cycles of blinks are executed)
int blinkCycle = 0;

// Blink boolean that determens ON and OFF for the blinking action
bool blink = true;


void trafficLight() {
  //counter setted to every 500 milliseconds (modified from https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay)
  if (current - previous == 500) {
    previous = current;
    
  //if sensor detects the car and the cycle of both traffic lights are finished (both red) execute blinking
    if (leftCar == true && NorthCycle == true && SouthCycle == true) {
      trafficLightControl(NS_BOUND, RED, OFF);

      if (blink) {
        trafficLightControl(NS_BOUND, GREEN, ON);
        blink = false;
      } else {
        trafficLightControl(NS_BOUND, GREEN, OFF);
        blink = true;
        blinkCycle++;
      }


      if (blinkCycle > 2) {
        NorthCycle = false;
        SouthCycle = false;
        blinkCycle = 0;
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
          butPED = false;
        }
      }


      if (yelNS > 0) {
        yelNS ++;
        NorthCycle = false;

        trafficLightControl(NS_BOUND, GREEN, OFF);
        trafficLightControl(NS_BOUND, YELLOW, ON);

        trafficLightControl(S_BOUND, GREEN, OFF);
        trafficLightControl(S_BOUND, YELLOW, ON);
        
        if (yelNS > 3) {
          yelNS = 0;
          redNS = 1;
        }
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

      }


      if (greEW > 0) {
        greEW++;
        SouthCycle = false;

        trafficLightControl(EW_BOUND, RED, OFF);
        trafficLightControl(EW_BOUND, GREEN, ON);
        
        if (greEW > 7) {
          greEW = 0;
          yelEW = 1;
        }
      }

      if (yelEW > 0) {
        yelEW ++;

        trafficLightControl(EW_BOUND, GREEN, OFF);
        trafficLightControl(EW_BOUND, YELLOW, ON);
        
        if (yelEW > 3) {
          yelEW = 0;
          redEW = 1;
          SouthCycle = true;
        }
      }

      if (redEW > 0) {
        redEW++;

        trafficLightControl(EW_BOUND, YELLOW, OFF);
        trafficLightControl(EW_BOUND, RED, ON);
        
        if (redEW > 13) {
          redEW = 0;
          greEW = 1;
        }
      }
    }
  }
}


// Detects if there is a car wating for a left turn
void leftTurn() {
  int value = analogRead(photoSensor);
  
  // if the slider go past half set boolean leftCar to TRUE
  if (value > 540) {
    leftCar = true;
  } else {
    leftCar = false;
  }
}


// Traffic Light Contorl function to control each NS, S, EW traffic lights
void trafficLightControl(int light, int colour, bool power) {
  if (light == 1) {
    if (colour == 1) {
      digitalWrite(greNSpin, power);
    } else if (colour == 2) {
      digitalWrite(yelNSpin, power);
    } else if (colour == 3) {
      digitalWrite(redNSpin, power);
    }
  }
  else if (light == 2) {
    if (colour == 1) {
      digitalWrite(greSpin, power);
    } else if (colour == 2) {
      digitalWrite(yelSpin, power);
    } else if (colour == 3) {
      digitalWrite(redSpin, power);
    }
  }
  else if (light == 3) {
    if (colour == 1) {
      digitalWrite(greEWpin, power);
    } else if (colour == 2) {
      digitalWrite(yelEWpin, power);
    } else if (colour == 3) {
      digitalWrite(redEWpin, power);
    }
  }
  else if (light == 4) {
    if (colour == 1) {
      digitalWrite(grePEDpin, power);
    } else if (colour == 3) {
      digitalWrite(redPEDpin, power);
    }
  }
}




//pulldown resistor reference https://makeabilitylab.github.io/physcomp/arduino/buttons.html
void trafficLight_Ped(){
  int butPEDStatus = digitalRead(butPEDpin);
    
  if (butPEDStatus){
    butPED = true;
  } 
  
  if (digitalRead(greSpin) == HIGH && butPED == true){
    trafficLightControl(PED, RED, OFF);
    trafficLightControl(PED, GREEN, ON);
    
  } else if (digitalRead(redSpin) == HIGH){
    trafficLightControl(PED, GREEN, OFF);
    trafficLightControl(PED, RED, ON);
    
  } else if (digitalRead(yelSpin) == HIGH){ 
    trafficLightControl(PED, RED, OFF);
    trafficLightControl(PED, GREEN, ON);
  }
  
}
