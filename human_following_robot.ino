// Human Following Luggage Carrying Robot
// Arduino + Ultrasonic Sensor + Relay Module
// (Simple relay-based control as used in mini project reports)

#define trigPin 9
#define echoPin 8

// Relay pins (Motor ON/OFF control)
#define relayLeft 2
#define relayRight 3

long duration;
int distance;

// Threshold values (keep same as your report)
int upper_threshold = 80;   // Move forward if person is far
int lower_threshold = 40;   // Stop if person is close

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(relayLeft, OUTPUT);
  pinMode(relayRight, OUTPUT);

  // Keep motors OFF initially
  digitalWrite(relayLeft, HIGH);   // Relay OFF
  digitalWrite(relayRight, HIGH);  // Relay OFF

  Serial.begin(9600);
}

void loop() {
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // --- Control Logic Based On Report ---
  
  if (distance > upper_threshold) {
    moveForward();
    Serial.println("Action: FORWARD");
  } 
  else if (distance < lower_threshold) {
    stopMoving();
    Serial.println("Action: STOP");
  } 
  else {
    stopMoving();
    Serial.println("Action: HOLD");
  }

  delay(200);  // Small delay for stability
}

// ------------------- FUNCTIONS -------------------

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int dist = duration * 0.034 / 2;   // Convert to cm

  return dist;
}

void moveForward() {
  // Relay LOW = ON (depends on module, matches most reports)
  digitalWrite(relayLeft, LOW);
  digitalWrite(relayRight, LOW);
}

void stopMoving() {
  digitalWrite(relayLeft, HIGH);
  digitalWrite(relayRight, HIGH);
}
