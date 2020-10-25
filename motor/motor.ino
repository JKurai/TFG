//definicion de pins
int motorPin1 = 4;    
int motorPin2 = 13;    
int motorPin3 = 15;   
int motorPin4 = 16;  
                   
//definicion variables
int motorSpeed = 1200;   //variable para fijar la velocidad
int stepCounter = 0;     // contador para los pasos
int stepsPerRev = 512;  // pasos para una vuelta completa
 
//tablas con la secuencia de encendido (descomentar la que necesiteis)
//secuencia 1-fase
//const int numSteps = 4;
//const int stepsLookup[4] = { B1000, B0100, B0010, B0001 };
 
//secuencia 2-fases
//const int numSteps = 4;
//const int stepsLookup[4] = { B1100, B0110, B0011, B1001 };
 
//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1001, B0001, B0101, B0100, B0110, B0010, B1010 };
 
 
void setup()
{
  //declarar pines como salida
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}
 
void loop()
{
  for (int i = 0; i < stepsPerRev ; i++)
  {
    clockwise();
    delayMicroseconds(motorSpeed);
  }
  for (int i = 0; i < stepsPerRev ; i++)
  {
    anticlockwise();
    delayMicroseconds(motorSpeed);
  }
  delay(1000);
}
 
void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}
 
void anticlockwise()
{
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}
 
void setOutput(int step)
{
  digitalWrite(motorPin1, bitRead(stepsLookup[step], 0));
  digitalWrite(motorPin2, bitRead(stepsLookup[step], 1));
  digitalWrite(motorPin3, bitRead(stepsLookup[step], 2));
  digitalWrite(motorPin4, bitRead(stepsLookup[step], 3));
}
