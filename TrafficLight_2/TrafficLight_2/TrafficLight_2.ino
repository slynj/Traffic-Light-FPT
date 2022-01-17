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

bool oneCycle = false;
int blinkCycle = 0;
int blinkCount = 0;
bool blink = true;

void trafficLight() {
  //counter in seconds (modified from https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay)
  if (current - previous == 1000) {
    previous = current;
    sec ++;
    // Serial.println(sec);

    if (leftCar == true && oneCycle == true) {
      digitalWrite(redNSpin, LOW);

      blinkCount++;


      if (blink) {
        digitalWrite(greNSpin, HIGH);
        if (blinkCount > 1) {
          blinkCount = 0;
          blink = false;
        }
      } else if (blink == false) {
        digitalWrite(greNSpin, LOW);
        if (blinkCount > 1) {
          blinkCount = 0;
          blink = true;
          blinkCycle++;
        }
      }
      if (blinkCycle > 2) {
        oneCycle = false;
        blinkCycle = 0;
        blinkCount = 0;
      }


    } else {

      if (greNS > 0) {
        greNS++;
        digitalWrite(redNSpin, LOW);
        digitalWrite(greNSpin, HIGH);

        digitalWrite(redSpin, LOW);
        digitalWrite(greSpin, HIGH);

        if (greNS > 4) {
          greNS = 0;
          yelNS = 1;
        }
      }


      if (yelNS > 0) {
        yelNS ++;
        digitalWrite(greNSpin, LOW);
        digitalWrite(yelNSpin, HIGH);

        digitalWrite(greSpin, LOW);
        digitalWrite(yelSpin, HIGH);

        if (yelNS > 2) {
          yelNS = 0;
          redNS = 1;
        }
      }

      if (redNS > 0) {
        redNS++;
        digitalWrite(yelNSpin, LOW);
        digitalWrite(redNSpin, HIGH);

        digitalWrite(yelSpin, LOW);
        digitalWrite(redSpin, HIGH);

        if (redNS > 7) {
          redNS = 0;
          greNS = 1;
          oneCycle = true;
        }
      }


      if (greEW > 0) {
        greEW++;
        digitalWrite(redEWpin, LOW);
        digitalWrite(greEWpin, HIGH);

        if (greEW > 4) {
          greEW = 0;
          yelEW = 1;
        }
      }

      if (yelEW > 0) {
        yelEW ++;
        digitalWrite(greEWpin, LOW);
        digitalWrite(yelEWpin, HIGH);

        if (yelEW > 2) {
          yelEW = 0;
          redEW = 1;
        }
      }

      if (redEW > 0) {
        redEW++;
        digitalWrite(yelEWpin, LOW);
        digitalWrite(redEWpin, HIGH);

        if (redEW > 7) {
          redEW = 0;
          greEW = 1;
        }
      }
    }
  }
}


void leftTurn() {
  int value = analogRead(photoSensor);
  //Serial.println(analogRead(photoSensor));
  if (value > 540) {
    leftCar = true;
  } else {
    leftCar = false;
  }
  //Serial.println(leftCar);
}
