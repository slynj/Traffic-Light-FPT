
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

int current;
int previous = 0;
int sec = 0;

int yelNS = 0;
int greNS = 0;
int redNS = 6;

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
  if (current - previous == 1000) {
    previous = current;
    sec ++;

    if (leftCar == true && NorthCycle == true && SouthCycle == true) {
      //digitalWrite(redNSpin, LOW);
      trafficLightControl("NS", "red", false);

      blinkCount++;
      
      if(blink) {
        //digitalWrite(greNSpin, HIGH);
        trafficLightControl("NS", "green", true);
        blink = false;
      } else {
        trafficLightControl("NS", "green", false);
        //digitalWrite(greNSpin, LOW);
        blink = true;
        blinkCycle++;
      }
      

      if (blinkCycle >= 2) {
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
        
        if (greNS > 4) {
          greNS = 0;
          yelNS = 1;
        }
        
        trafficLightControl("NS", "red", false);
        trafficLightControl("NS", "green", true);
        
        trafficLightControl("S", "red", false);
        trafficLightControl("S", "green", true);
        
        //digitalWrite(redNSpin, LOW);
        //digitalWrite(greNSpin, HIGH);

        //digitalWrite(redSpin, LOW);
        //digitalWrite(greSpin, HIGH);

        
      }


      if (yelNS > 0) {
        yelNS ++;
        
        if (yelNS > 2) {
          yelNS = 0;
          redNS = 1;
        }
        
        trafficLightControl("NS", "green", false);
        trafficLightControl("NS", "yellow", true);
        
        trafficLightControl("S", "green", false);
        trafficLightControl("S", "yellow", true);
        
        //digitalWrite(greNSpin, LOW);
        //digitalWrite(yelNSpin, HIGH);

        //digitalWrite(greSpin, LOW);
        //digitalWrite(yelSpin, HIGH);

        
      }

      if (redNS > 0) {
        redNS++;
        
        if (redNS > 7) {
          redNS = 0;
          greNS = 1;
          NorthCycle = true;
        }
        
        trafficLightControl("NS", "yellow", false);
        trafficLightControl("NS", "red", true);
        
        trafficLightControl("S", "yellow", false);
        trafficLightControl("S", "red", true);
        
        //digitalWrite(yelNSpin, LOW);
        //digitalWrite(redNSpin, HIGH);

        //digitalWrite(yelSpin, LOW);
        //digitalWrite(redSpin, HIGH);


      }


      if (greEW > 0) {
        greEW++;

        if (greEW > 4) {
          greEW = 0;
          yelEW = 1;
        }
        
        trafficLightControl("EW", "red", false);
        trafficLightControl("EW", "green", true);
        
        //digitalWrite(redEWpin, LOW);
        //digitalWrite(greEWpin, HIGH);

      }

      if (yelEW > 0) {
        yelEW ++;

        if (yelEW > 2) {
          yelEW = 0;
          redEW = 1;
          SouthCycle = true;
        }
        
        trafficLightControl("EW", "green", false);
        trafficLightControl("EW", "yellow", true);
        
        //digitalWrite(greEWpin, LOW);
        //digitalWrite(yelEWpin, HIGH);

      }

      if (redEW > 0) {
        redEW++;
        
        if (redEW > 7) {
          redEW = 0;
          greEW = 1;
          
        }
        
        trafficLightControl("EW", "yellow", false);
        trafficLightControl("EW", "red", true);
        
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


void trafficLightControl(String light, String colour, bool power){
  if(light == "NS"){
    if(colour == "green"){
      digitalWrite(greNSpin, power);
    } else if(colour == "yellow"){
      digitalWrite(yelNSpin, power);
    }else if(colour == "red"){
      digitalWrite(redNSpin, power);
    }
  }
  else if(light == "S"){
    if(colour == "green"){
      digitalWrite(greSpin, power);
    } else if(colour == "yellow"){
      digitalWrite(yelSpin, power);
    }else if(colour == "red"){
      digitalWrite(redSpin, power);
    }
  }
  else if(light == "EW"){
    if(colour == "green"){
      digitalWrite(greEWpin, power);
    } else if(colour == "yellow"){
      digitalWrite(yelEWpin, power);
    }else if(colour == "red"){
      digitalWrite(redEWpin, power);
    }
  }
}
