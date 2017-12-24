// Creating base thresholds for the arduino to use before reading adjustments are performed
int maxthreshold = 54;
int mediumthreshold = 25;
int lowthreshold = 15;
int offset = 10;

int arrayCounter = 0; // Counter to use for every 10th reading
const int readAmount = 10; // If each LED reaction is delayed by half a second, lets wait 5 seconds to set our averages

int readings[readAmount];      // The readings from the analog inputs
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(4, HIGH);
  delay(500);
}
/**
* Called within the main() function to recieve and manipulate data.
* Recieves readings from the analog wires and outputs to the LED's connected to
* their appropriate pins.
*/
void loop()
{
  
  if (analogRead(A0) > maxthreshold - offset)
  {
    digitalWrite(4, HIGH);
  }
  else
  {
    digitalWrite(4, LOW);
  }
  if (analogRead(A0) > lowthreshold )
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
  }
  if (analogRead(A0) > mediumthreshold - offset)
  {
    digitalWrite(3, HIGH);
  }
  else
  {
    digitalWrite(3, LOW);
  }

  Serial.println(analogRead(A0)); // Print the analog readings to the serial plotter
  arrayCounter =arrayCounter + 1; // Add to array counter
  readings[arrayCounter] = A0; // Assign analog reading to array
  
  if(arrayCounter == 10){ // Reset the thresholds every 10th reading
    setMax(readings);
  }
}

/**
* On every 10th reading, grab all info from the reading array and
* use them to reset the lying/truth thresholds
* @param valueArray an integer array holding the previous 10 readings
*/
void setMax(int valueArray[])
{
  // Check to see if the array counter is at 10
  if(arrayCounter == readAmount){ 
    int max_v = 0;
    int min_v = 70;
    int total = 0;
    // Check each reading and sort it by max, min, and medium thresholds
    for(int i = 0; i < sizeof(readings); i++){
      if ( readings[i] > max_v )
      {
        max_v = readings[i];
      }
      if( readings[i] < min_v ){
        min_v =  readings[i];
      }
      total = total + readings[i];
    }
    // Assign the global threshold values to the new dynamically calculated ones
    maxthreshold = max_v;
    lowthreshold = min_v;
    mediumthreshold = total/readAmount;
    arrayCounter =0;
  }
} 
  
