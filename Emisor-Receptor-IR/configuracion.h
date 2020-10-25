#ifndef CONFIGURACION_HPP
#define CONFIGURACION_HPP

#define SERIAL_DEBUG_BAUD    115200
// Delay en cada ejecucion de la aplicacion
int quant = 20;

//Datos de la red wifi a la que se conectara el ESP32
#define WIFI_AP_NAME        "Jl"
#define WIFI_PASSWORD       "lolwifigratis"

//datos del servidor de thingsboard y el token del sistema en thingsboard
#define TOKEN               "zlO0XVQmbj3JHTm21FO4"
#define THINGSBOARD_SERVER  "138.4.92.46"

//pines TPIC
int srck = 16;
int datos = 5;
int rck = 17;

//codigos para enviar al TPIC para necender las luces correspondientes
uint8_t patterns[] = 
{ 
  0x00,0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff,
};

//pines infrarrojos
int pinRecep = 13;
//pin de envio el 4


#endif
