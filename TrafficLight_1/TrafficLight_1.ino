int const redNSpin = 4;
int const yelNSpin = 2;
int const greNSpin = 3;
int const redEWpin = 7;
int const yelEWpin = 6;
int const greEWpin = 5;
int const redSpin = 8;
int const yelSpin = 9;
int const greSpin = 10;

int current;
int previous = 0;
int sec = 0;

int yelNS = 0;
int greNS = 0;
int redNS = 6;

int yelEW = 0;
int greEW = 0;
int redEW = 1;

int yelS = 0;
int greS = 0;
int redS = 6;


void setup() {
  Serial.begin(9600);

  //NS EW LED pinMode Setup
  for (int i = 2; i < 11; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  current = millis();

  //counter in seconds (modified from https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay)
  if (current - previous == 1000) {
    previous = current;
    sec ++;
    Serial.println(sec);

    if (greNS > 0) {
      greNS++;
      digitalWrite(redNSpin, LOW);
      digitalWrite(greNSpin, HIGH);

      if (greNS > 4) {
        greNS = 0;
        yelNS = 1;
      }
    }

    if (yelNS > 0) {
      yelNS ++;
      digitalWrite(greNSpin, LOW);
      digitalWrite(yelNSpin, HIGH);

      if (yelNS > 2) {
        yelNS = 0;
        redNS = 1;
      }
    }

    if (redNS > 0) {
      redNS++;
      digitalWrite(yelNSpin, LOW);
      digitalWrite(redNSpin, HIGH);

      if (redNS > 7) {
        redNS = 0;
        greNS = 1;
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

    if (greS > 0) {
      greS++;
      digitalWrite(redSpin, LOW);
      digitalWrite(greSpin, HIGH);

      if (greS > 4) {
        greS = 0;
        yelS = 1;
      }
    }

    if (yelS > 0) {
      yelS ++;
      digitalWrite(greSpin, LOW);
      digitalWrite(yelSpin, HIGH);

      if (yelS > 2) {
        yelS = 0;
        redS = 1;
      }
    }

    if (redS > 0) {
      redS++;
      digitalWrite(yelSpin, LOW);
      digitalWrite(redSpin, HIGH);

      if (redS > 7) {
        redS = 0;
        greS = 1;
      }
    }

  }

}
