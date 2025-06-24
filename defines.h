#pragma once

/*--------------  ESP TYPE  --------------*/

/*--- EDIT ESP ---*/
// #define ESP_32
/*----------------*/

#ifndef ESP_32
#define ESP_8266
#endif

/*----------------------------------------*/


/*-------------  MODULE TYPE  -------------*/

/*-- EDIT REGION --*/
#define REGION 2
/*-----------------*/

/*--------------  PRODUCER  --------------*/

// #define PRODUCER

/*--- EDIT TYPE ---*/
#ifdef PRODUCER
#define MODULE_TYPE "PROD_NPP"
// #define MODULE_TYPE "PROD_HPP"
// #define MODULE_TYPE "PROD_SPP"
// #define MODULE_TYPE "PROD_CGPP"
// #define MODULE_TYPE "PROD_WPP"
#endif
/*-----------------*/

/*--- EDIT PINS ---*/
#ifdef PRODUCER
#define ROTARY_ENCODER_CLK 15
#define ROTARY_ENCODER_DT 13
#define ROTARY_ENCODER_SW 12
#endif
/*-----------------*/

/*----------------------------------------*/


/*--------------  CONSUMER  --------------*/

/*--- EDIT TYPE ---*/
#ifndef PRODUCER
#define CONSUMER
#define MODULE_TYPE "CON_FIRST"
// #define MODULE_TYPE "CON_OTHER"
#endif
/*-----------------*/

/*--- EDIT PINS ---*/
#ifdef CONSUMER
#define LED_RED 4
#define LED_GREEN 5
#define LED_BLUE 3
#endif
/*-----------------*/

/*----------------------------------------*/
