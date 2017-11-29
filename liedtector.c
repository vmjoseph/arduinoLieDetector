int maxthreshold = 54;
int mediumthreshold = 25;
int lowthreshold = 15;
int offset = 10;

int arrayCounter = 0;
const int readAmount = 10; //If each LED reaction is delayed by half a second, lets wait 5 seconds to set our averages

int readings[readAmount];      // the readings from the analog inputs
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

  Serial.println(analogRead(A0));
  //delay(20); 
  arrayCounter =arrayCounter + 1; //add to array counter
  readings[arrayCounter] = A0; //assign analog reading to array
  if(arrayCounter == 10){
    setMax(readings);
  }
}

void setMax(int valueArray[])
{
 

  if(arrayCounter == readAmount){ 
    int max_v = 0;
    int min_v = 70;
    int total = 0;
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
    maxthreshold = max_v;
    lowthreshold = min_v;
    mediumthreshold = total/readAmount;
    arrayCounter =0;
  }
} 
  