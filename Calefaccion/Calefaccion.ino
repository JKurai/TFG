#include <IRremote.h>
#include <WiFi.h>           // WiFi control for ESP32
#include <ThingsBoard.h>    // ThingsBoard SDK
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "configuracion.h"


// Helper macro to calculate array size
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

// Initialize ThingsBoard client
WiFiClient espClient;

PubSubClient client(espClient);

// Initialize ThingsBoard instance
ThingsBoard tb(espClient);
// the Wifi radio's status
int status = WL_IDLE_STATUS;

int temperatura = 0;

void setup() {
  Serial.begin(SERIAL_DEBUG_BAUD);
  inicializarPines();
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    InitWiFi();
    client.setServer( THINGSBOARD_SERVER, 1883 );
    //client.setCallback(on_message); 
    #if defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
        delay(2000); // To be able to connect Serial monitor after reset and before first printout
    #endif
}

void loop() {
    delay(quant);
    // Reconectar al wifi de ser necesario
    if (WiFi.status() != WL_CONNECTED) {
      reconnect();
      return;
    }
    // Reconectar a Thingsboard de ser necesario
    if (!tb.connected()) {
      if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
        Serial.println("Fallo al conectar");
        return;
      }else{
        //Serial.println("Conexion realizada con exito);
      }
    }
    int acto=actualizarTemperatura();
    enviarTemperatura();
    displayTemp();
    actualizarMotor(acto);
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}

void inicializarPines()
{
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorPin3,OUTPUT);
  pinMode(motorPin4,OUTPUT);
  pinMode(pin_0,OUTPUT);
  pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);
  pinMode(pin_3,OUTPUT);
  pinMode(pin_4,OUTPUT);
  pinMode(pin_5,OUTPUT);
  pinMode(pin_6,OUTPUT);
  pinMode(pin_7,OUTPUT);
  pinMode(botonSubir, INPUT);
  pinMode(botonBajar, INPUT);
   
}

int actualizarTemperatura()
{
  int acto=0; //0-->nada  1-->bajar  2-->subir
  int subirTemperatura = analogRead(botonSubir);
  int bajarTemperatura = analogRead(botonBajar);
  if(subirTemperatura > 3000)
  {
    temperatura++;
    acto=2;
  }
  if(bajarTemperatura > 3000)
  {
    temperatura--;
    acto=1;
  }  
  if(temperatura<0)
    temperatura=0;
  if(temperatura>7)
    temperatura=7;  
  return acto;
}

void displayTemp()
{
  digitalWrite(pin_0, bitRead(luces[temperatura], 7));
  digitalWrite(pin_1, bitRead(luces[temperatura], 6));
  digitalWrite(pin_2, bitRead(luces[temperatura], 5));
  digitalWrite(pin_3, bitRead(luces[temperatura], 4));
  digitalWrite(pin_4, bitRead(luces[temperatura], 3));
  digitalWrite(pin_5, bitRead(luces[temperatura], 2));
  digitalWrite(pin_6, bitRead(luces[temperatura], 1));
  digitalWrite(pin_7, bitRead(luces[temperatura], 0));
  //digitalWrite(rck, LOW);
  //shiftOut(datos, srck, MSBFIRST, patterns[temperatura]);
  //digitalWrite(rck, HIGH);
}

void actualizarMotor(int acto)
{ 
  
  if(acto == 2 && temperatura!=7){
    for (int i = 0; i < aux ; i++)
    {
      //clockwise();
      anticlockwise();
      delayMicroseconds(motorSpeed);
    }
  }
  if(acto == 1 && temperatura!=0){
    for (int i = 0; i < aux ; i++)
    {
      //anticlockwise();
      clockwise();
      delayMicroseconds(motorSpeed);
    }
  }

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

void enviarTemperatura()
{
   Serial.println("Sending data...");
   tb.sendTelemetryInt("Temperatura", temperatura);
   tb.loop();
}
