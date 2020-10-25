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

int codSubirTemp=16754775;
int codBajarTemp=16769055;

IRrecv irrecv(pinRecep);

decode_results results;

IRsend irsend;

int codigo=0;

void setup() {
    //pinMode(LED_BUILTIN, OUTPUT);
    pinMode(srck, OUTPUT);
    pinMode(datos, OUTPUT);
    pinMode(rck, OUTPUT);
    Serial.begin(SERIAL_DEBUG_BAUD);
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    InitWiFi();
    client.setServer( THINGSBOARD_SERVER, 1883 );
    client.setCallback(on_message); 
    #if defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
        delay(2000); // To be able to connect Serial monitor after reset and before first printout
    #endif
    irrecv.enableIRIn();
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
    client.loop();
    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        Serial.println(results.value);
        Serial.println(results.decode_type);
        codigo=results.value;
        enviarCodigo(results.value);
        displayTemp(results.value);
        irrecv.resume(); // Receive the next value
    }
    delay(100);
      
    unsigned long dato = codigo;
    if(codigo!=0){
      for (int i = 0; i < 3; i++) {
          irsend.sendLG(dato, 28);
          delay(100);
      }
    }else{
      Serial.println("No hay codigo para enviar");
    }

    codigo=0;
    delay(100); //5 second delay between each signal burst
}

void on_message(const char* topic, byte* payload, unsigned int length) {
  Serial.println("On message");
  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';
  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(json);
  // Decode JSON request
  StaticJsonDocument<200> doc;
  deserializeJson(doc,json);
  // Check request method
  String methodName = String((const char*)doc["method"]);
  Serial.print("WIIII");
  Serial.print(methodName);
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

void displayTemp(int cod)
{
    if(cod==codSubirTemp)
      temperatura++;
    else
      if(cod==codBajarTemp)
        temperatura--;
      else
        Serial.println("No se reconoce el codigo");
    if(temperatura>8)
      temperatura=8;
    if(temperatura<0)
      temperatura=0;
    digitalWrite(rck, LOW);
    shiftOut(datos, srck, MSBFIRST, patterns[temperatura]);
    digitalWrite(rck, HIGH);
}

void enviarCodigo(int cod)
{
   Serial.println("Sending data...");
   tb.sendTelemetryInt("codigo", cod);
   tb.loop();
}
