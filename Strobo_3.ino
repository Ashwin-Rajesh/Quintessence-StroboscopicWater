// Output pins
const int valveNum      = 4;                        // Number of valves
const int valvePins[]   = {3,4,5,6};                // Pins connected to valves
const int ledPin        = 13;                       // Pin connected to LED

// Control variables for valves
int valvePeriod[]       = {70,72,68,70};            // Time period for switching of valve
int valveOn[]           = {15,15,25,30};            // Time for which valve is ON - determines size of drop
bool valveState[]       = {0,0,0,0};                // Current state of valve - ON / OFF

// Control variables for LEDs
int ledPeriod           = 35;                       // Time period for switching of LED
int ledOn               = 1;                        // Time for which led remains ON
bool ledState           = 0;                        // Current state of LED - ON / OFF

// Variable temorarily stores current time
long now                = 0;                        // Temporary variable to store time

// Callibration and debug constant variables 
bool debug              = false;                    // Display debugging messages through Serial monitor?

void setup() 
{
  pinMode(ledPin,OUTPUT);
  for(int i = 0; i < valveNum; i++)  
    pinMode(valvePins[i],OUTPUT);
  
  Serial.begin(9600);
  Serial.println(" Serial commuication established.");
}

void loop() 
{
  now = millis();
  setLed();
  writeLed();
  setValve();
  writeValve();
}

void setValve()
{
  for(int i = 0; i < 4; i++)
  {
    if(now % valvePeriod[i] <= valveOn[i])
    {
      valveState[i] = true;
      if(debug) Serial.print("valve no " + String(i) + " ON");
    }
    else
    {
      valveState[i] = false;
      if(debug) Serial.print("valve no " + String(i) + " OFF");
    }
  }
}

void writeValve()
{
  for(int i = 0; i < valveNum; i++)
    digitalWrite(valvePins[i],valveState[i]);
}

void setLed()
{
  if(now % ledPeriod <= ledOn)
  {
    ledState = true;
    if(debug)   Serial.println("led ON");
  }
  else
  {
    ledState = false;
    if(debug)   Serial.println("led OFF");  
  }
}

void writeLed()     
{
  digitalWrite(ledPin,ledState);
}
