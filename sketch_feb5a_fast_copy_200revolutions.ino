// Pin numbers
const int directionPin = 9;
const int stepPin = 8;
const int reversePin = 4;
const int forwardPin = 5;

// Variables to track button states and movement
bool forwardButtonPressed = false;
bool reverseButtonPressed = false;
bool forwardMovementDone = true;
bool reverseMovementDone = true;
unsigned long lastForwardPressTime = 0;
unsigned long lastReversePressTime = 0;
const unsigned long longPressDuration = 1000; // Adjust as needed for long press duration
bool doubleForwardPress = false;
bool doubleReversePress = false;
unsigned int forwardPressCount = 0;
unsigned int reversePressCount = 0;

// Other constants
const int NumSteps = 800; // Number of steps to move the motor
const int Speed = 200;    // Speed at which the motor will "step" (shouldn't be less than 200)

void setup()
{
  Serial.begin(9600);
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(reversePin, INPUT_PULLUP);
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(directionPin, LOW);
  digitalWrite(stepPin, LOW);
}

void loop()
{
  // Read button states
  int forwardRead = digitalRead(forwardPin);
  int reverseRead = digitalRead(reversePin);

  // Check if the forward button is pressed
  if (forwardRead == LOW)
  {
    if (!forwardButtonPressed)
    {
      forwardButtonPressed = true;
      lastForwardPressTime = millis();
      forwardPressCount++;
    }
    else
    {
      if (millis() - lastForwardPressTime >= longPressDuration)
      {
        // Long press detected
        // Perform continuous movement
        forwardPressCount = 0;
        Serial.println("Long forward button press detected");
        digitalWrite(directionPin, LOW);

        // Move in one direction until the button is released
        while (digitalRead(forwardPin) == LOW)
        {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(Speed);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(Speed);
        }

        Serial.println("Forward movement done");
        forwardButtonPressed = false;
      }
      else
      {
        // Double press check
        if (forwardPressCount == 2)
        {
          // Double press detected
          doubleForwardPress = true;
          forwardPressCount = 0;
        }
      }
    }
  }
  else
  {
    forwardButtonPressed = false;
  }

  // Check if the reverse button is pressed
  if (reverseRead == LOW)
  {
    if (!reverseButtonPressed)
    {
      reverseButtonPressed = true;
      lastReversePressTime = millis();
      reversePressCount++;
    }
    else
    {
      if (millis() - lastReversePressTime >= longPressDuration)
      {
        // Long press detected
        // Perform continuous movement
        reversePressCount = 0;
        Serial.println("Long reverse button press detected");
        digitalWrite(directionPin, HIGH);

        // Move in the reverse direction until the button is released
        while (digitalRead(reversePin) == LOW)
        {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(Speed);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(Speed);
        }

        Serial.println("Reverse movement done");
        reverseButtonPressed = false;
      }
      else
      {
        // Double press check
        if (reversePressCount == 2)
        {
          // Double press detected
          doubleReversePress = true;
          reversePressCount = 0;
        }
      }
    }
  }
  else
  {
    reverseButtonPressed = false;
  }

  // Handle double press actions
  if (doubleForwardPress)
  {
    // Perform action for double press on forward button
    Serial.println("Double forward button press detected");
    // Move in one direction
    for (int distance = 0; distance < NumSteps; distance++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(Speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(Speed);
    }
    doubleForwardPress = false;
  }

  if (doubleReversePress)
  {
    // Perform action for double press on reverse button
    Serial.println("Double reverse button press detected");
    // Move in one direction
    for (int distance = 0; distance < NumSteps; distance++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(Speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(Speed);
    }
    doubleReversePress = false;
  }

  // Add a small delay to avoid excessive loop iterations
  delay(10);
}
