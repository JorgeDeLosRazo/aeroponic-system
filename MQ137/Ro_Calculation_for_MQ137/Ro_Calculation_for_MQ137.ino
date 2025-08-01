/*
 * Program to measure the value of R0 for a know RL at fresh air condition
 * Program by: B.Aswinth Raj
 * Website: www.circuitdigest.com                                       
 * Dated: 28-12-2017
 */
//This program works best at a fresh air room with temperaure Temp: 20℃, Humidity: 65%, O2 concentration 21% and when the value of Rl is 47K
#define RL 47  //The value of resistor RL is 47K
void setup() //Runs only once
{
  Serial.begin(9600); //Initialise serial COM for displaying the value
}
void loop() {
  float analog_value;
  float VRL = 0;
  float Rs = 0;
  float Ro = 0;


  for(int test_cycle = 1 ; test_cycle <= 500 ; test_cycle++) //Read the analog output of the sensor for 500 times
  {
    analog_value = analog_value + analogRead(A0); //add the values for 500
  }
  analog_value = analog_value/500.0; //Take average
  VRL = analog_value*(3.22/4095.0); //Convert analog value to voltage
  //RS = ((Vc/VRL)-1)*RL is the formulae we obtained from datasheet
  Rs = ((3.22/VRL)-1) * RL;
  //RS/RO is 3.6 as we obtained from graph of datasheet
  Ro = Rs/3.6;
  Serial.print("Ro at fresh air = ");
  Serial.println(Ro); //Display calculated Ro
  delay(1000); //delay of 1sec

}