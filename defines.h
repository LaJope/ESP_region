#pragma once



/*---------------  DEBUG  ---------------*/

#define VERBOSE true
// #define DEBUG

/*---------------------------------------*/

/*#######################################*/
#define REGION 1
/*#######################################*/


/*--------------  ESP TYPE  --------------*/

/*--- EDIT ESP ---*/
/*#######################################*/
// #define ESP_32
/*#######################################*/
/*----------------*/

#ifndef ESP_32
#define ESP_8266
#endif

/*----------------------------------------*/


/*----------------  LED  -----------------*/

/*--- EDIT PINS ---*/
#ifdef ESP_32
#define LED_RED 17
#define LED_GREEN 18
#define LED_BLUE 19
#endif
#ifdef ESP_8266
#define LED_RED 14
#define LED_GREEN 12
#define LED_BLUE 13
#endif
/*-----------------*/

/*----------------------------------------*/


/*-------------  MODULE TYPE  -------------*/

/*--------------  PRODUCER  --------------*/

/*--- EDIT TYPE ---*/
/*#######################################*/
#define PRODUCER
/*#######################################*/
/*-----------------*/

#ifdef PRODUCER
/*--- EDIT TYPE ---*/
/*#######################################*/
#define MODULE_TYPE "PROD_NPP"
// #define MODULE_TYPE "PROD_HPP"
// #define MODULE_TYPE "PROD_SPP"
// #define MODULE_TYPE "PROD_CGPP"
// #define MODULE_TYPE "PROD_WPP"
/*#######################################*/
/*-----------------*/

/*--- VARIABLES ---*/
#define UPDATE_INTERVAL 200

#define CHANGE_RATE 5

#define MAX_PERCENTAGE 200
/*-----------------*/

/*- POTENTIOMETER -*/
#define POTENTIOMETER
#ifdef ESP_32
#define POTENTIOMETER_PIN 36
#endif
#ifdef ESP_8266
#define POTENTIOMETER_PIN 3
#endif
/*-----------------*/

/*- ROTARY ENCODER -*/
#ifndef POTENTIOMETER
#define ROTARY_ENCODER
#ifdef ESP_32
#define ROTARY_ENCODER_CLK 32
#define ROTARY_ENCODER_DT 33
#define ROTARY_ENCODER_SW 25
#endif
#ifdef ESP_8266
#endif
#endif
/*-----------------*/

/*---- DISPLAY ----*/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
/*-----------------*/

#endif

/*----------------------------------------*/


/*--------------  CONSUMER  --------------*/

/*--- EDIT TYPE ---*/
#ifndef PRODUCER
#define CONSUMER
/*#######################################*/
#define MODULE_TYPE "CON_FIRST"
// #define MODULE_TYPE "CON_OTHER"
/*#######################################*/
#endif
/*-----------------*/

/*----------------------------------------*/
