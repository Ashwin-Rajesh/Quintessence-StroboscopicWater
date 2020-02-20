// Output pins
const int valveNum      = 4;                        // Number of valves
const int valvePins[]   = {3,4,5,6};                // Pins connected to valves
const int ledPin        = 13;                       // Pin connected to LED

// Control variables for valves
int valveOn[]           = {15,15,25,30};            // Time for which valve is ON - determines size of drop
bool valveState[]       = {0,0,0,0};                // Current state of valve - ON / OFF
int valvePeriod[]       = {70,72,68,70};            // Time period for switching valves

// Valve pattern variables
int patternNum          = 10;                       // Number of patterns
int currentPattern      = 0;                        // Index of current pattern being displayed
                                                    // Patterns, iterating and cycling from first to last
int valvePattern[][4]   = {{70,70,70,70},           
                           {68,70,70,68},
                           {72,70,70,72},
                           {70,72,72,70},
                           {70,68,68,70},
                           {68,68,68,68},
                           {72,68,68,72},
                           {72,72,72,72},
                           {70,72,68,70},
                           {72,70,70,68}};
long patternDelay       = 15000;                    // Delay after which pattern changes
long transitionDelay    = 200;                      // Delay for transition period between different patterns

// Control variables for LEDs
int ledPeriod           = 35;                       // Time period for switching of LED
int ledOn               = 2;                        // Time for which led remains ON
bool ledState           = 0;                        // Current state of LED - ON / OFF

// Variable temorarily stores current time
long now                = 0;                        // Temporary variable to store time

// Callibration and debug constant variables 
bool debugValve         = false;
bool debugLed           = false;
bool debugPattern       = false;
bool debugTime          = false;                   

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
  
  if(now % patternDelay == 0)
  {
    patternSwitch();
    if(debugPattern)    Serial.println("Pattern switch");
    digitalWrite(ledPin,HIGH);
    for(int i = 0; i < valveNum; i++)
      valveState[i] = 1;
    writeValve();
    delay(transitionDelay);
  }
  else
  {
    setLed();
    writeLed();
    setValve();
    writeValve();
  }
  
  if(debugTime)         Serial.print(millis() - now);
}

void patternSwitch()
{
  if(currentPattern == patternNum - 1)
    currentPattern = 0;
  else
    currentPattern++;
  for(int i = 0; i < valveNum; i++)
    valvePeriod[i] = valvePattern[currentPattern][i];
}

void setValve()
{
  for(int i = 0; i < valveNum; i++)
  {
    if(now % valvePeriod[i] <= valveOn[i])
    {
      valveState[i] = true;
      if(debugValve)  Serial.print("valve no " + String(i) + " ON");
    }
    else
    {
      valveState[i] = false;
      if(debugValve)  Serial.print("valve no " + String(i) + " OFF");
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
    if(debugLed)    Serial.println("led ON");
  }
  else
  {
    ledState = false;
    if(debugLed)    Serial.println("led OFF");  
  }
}

void writeLed()     
{
  digitalWrite(ledPin,ledState);
}
