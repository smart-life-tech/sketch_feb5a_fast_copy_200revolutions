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

  // Check if the forward button is pressed and perform forward movement
  if (forwardRead == LOW && forwardMovementDone)
  {
    Serial.println("Forward button pressed");
    digitalWrite(directionPin, LOW);

    // Move in one direction
    for (int distance = 0; distance < NumSteps; distance++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(Speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(Speed);
    }

    Serial.println("Forward movement done");
    forwardMovementDone = false;
  }

  // Reset the forwardMovementDone flag if the forward button is released
  if (forwardRead == LOW)
  {
    forwardMovementDone = true;
  }

  // Check if the reverse button is pressed and perform reverse movement
  if (reverseRead == LOW && reverseMovementDone)
  {
    Serial.println("Reverse button pressed");
    digitalWrite(directionPin, HIGH);

    // Move in one direction
    for (int distance = 0; distance < NumSteps; distance++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(Speed);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(Speed);
    }

    Serial.println("Reverse movement done");
    reverseMovementDone = false;
  }

  // Reset the reverseMovementDone flag if the reverse button is released
  if (reverseRead == LOW)
  {
    reverseMovementDone = true;
  }

  // Add a small delay to avoid excessive loop iterations
  delay(10);
}
