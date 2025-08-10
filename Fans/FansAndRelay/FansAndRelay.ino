
// constants won't change
const int RELAY_PIN = 26;  // the Arduino pin, which connects to the IN pin of relay

// the setup function runs once when you press reset or power the board
void setup() {
  // set the relay digital pin as an output.
  pinMode(RELAY_PIN, OUTPUT);
  // set relay to initial OFF state
  digitalWrite(RELAY_PIN, HIGH);  //for an active-LOW relay, HIGH means OFF
  

  //can use Serial to debug
  Serial.begin(115200);
  Serial.println("ESP32 Relay Controller Initialized");
}

// the loop function runs over and over again forever
void loop() {

//TURN THE FAN ON FOR 5 SECONDS
digitalWrite(RELAY_PIN, LOW); 
Serial.println("Fan ON");
delay(5000);

//TURN THE FAN OFF FOR 5 SECONDS
digitalWrite(RELAY_PIN, HIGH);  //for an active-LOW relay, HIGH means OFF
Serial.println("Fan OFF");
delay(5000);
  

}
