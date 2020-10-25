#ifndef CONFIGURACION_HPP
#define CONFIGURACION_HPP

#define SERIAL_DEBUG_BAUD    115200
// Delay en cada ejecucion de la aplicacion
int quant = 300;

//Datos de la red wifi a la que se conectara el ESP32
#define WIFI_AP_NAME        "Jl"
#define WIFI_PASSWORD       "esp322020"

//datos del servidor de thingsboard y el token del sistema en thingsboard
#define TOKEN               "OBGJnz1nIXw25j0EEXwK"
#define THINGSBOARD_SERVER  "138.4.92.46"

//pines motor
int motorPin1 = 4;    
int motorPin2 = 13;    
int motorPin3 = 15;   
int motorPin4 = 16;   
//secuencia media fase
const int numSteps = 8;
const int stepsLookup[8] = { B1000, B1001, B0001, B0101, B0100, B0110, B0010, B1010 };
int aux=64;
int motorSpeed = 1200;   //variable para fijar la velocidad (1200)
int stepCounter = 0;     // contador para los pasos

//pines botones 
int botonSubir=35;
int botonBajar=34;

//pines led bar
int pin_0=12;
int pin_1=14;
int pin_2=27;
int pin_3=26;
int pin_4=25;
int pin_5=5;
int pin_6=32;
int pin_7=17;

const int luces[8] = { B0000000, 
                       B1000000, 
                       B1100000, 
                       B1110000, 
                       B1111000, 
                       B1111100, 
                       B1111110, 
                       B1111111};
//pines TPIC
//int srck = 16;
//int datos = 5;
//int rck = 17;

//codigos para enviar al TPIC para necender las luces correspondientes
/*uint8_t patterns[] = 
{ 
  0x00,0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff,
};*/

#endif
