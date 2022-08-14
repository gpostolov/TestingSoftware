#include "unity.h"
#include "leds.h"

/**
* * Lista con los test que quiero realizar
* - Con la inicializacion todos los LEDs quedan apagados
* - Prender un LED individual
* - Apagar un LED individual
* - Prender y apagar multiples LEDs
* - Prender todos los LEDs de una vez
* - Apagar todos los LEDs de una vez
* - Consultar el estado de un LED que esta encendido
* - Consultar el estado de un LED que esta apagado
* - Revisar limites de los parametros
* - Revisar parametros fuera de los limites
*/

gravedad_t gravedad_registrada;
int linea_registrada;
 
void RegistrarError(gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...){
    gravedad_registrada = gravedad;
    linea_registrada = linea;
}

//Esta funcion se ejecuta siempre antes de cada test
uint16_t leds_virtuales; //Pasa a ser una variable global
void setUp(void) {
    linea_registrada = 0;
    gravedad_registrada = ERROR - 1;
    LedsCreate(&leds_virtuales, RegistrarError);
}

//Con la inicializacion todos los LEDs quedan apagados
void test_todos_los_leds_quedan_apagados(void) {
    uint16_t leds_virtuales = 0xFFFF;
    LedsCreate(&leds_virtuales, RegistrarError);
    TEST_ASSERT_EQUAL(0x0000, leds_virtuales);
}

//Prender un LED individual
void test_prender_un_led_individual(void) {
    LedsSingleTurnOn(3);
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales);
}

//Apagar un LED individual
void test_apagar_un_led_individual(void) {
    LedsSingleTurnOn(3);
    LedsSingleTurnOff(3);
    TEST_ASSERT_EQUAL(0, leds_virtuales);
}

//Prender y apagar multiples LEDs
void test_prender_y_apagar_multiples_leds(void) {
    LedsSingleTurnOn(3);
    LedsSingleTurnOn(7);
    LedsSingleTurnOff(7);
    TEST_ASSERT_EQUAL(1 << 2, leds_virtuales);
}

//Prender todos los LEDs de una vez
void test_prender_todos_los_leds(void) {
    LedsAllTurnOn();
    TEST_ASSERT_EQUAL(0xFFFF, leds_virtuales);
}

//Apagar todos los LEDs de una vez
void test_apagar_todos_los_leds(void) {
    LedsSingleTurnOn(3);
    LedsSingleTurnOn(7);
    LedsAllTurnOff();
    TEST_ASSERT_EQUAL(0x0000, leds_virtuales);
}

//Consultar el estado de un LED que esta encendido
void test_consultar_el_estado_de_un_LED_encendido(void) {
    LedsSingleTurnOn(3);
    TEST_ASSERT_EQUAL(1, LedsRequestLedStatus(3));
}

//Consultar el estado de un LED que esta apagado
void test_consultar_el_estado_de_un_LED_apagado(void) {
    TEST_ASSERT_EQUAL(0, LedsRequestLedStatus(3));
}

//Prender un led invalido
void test_prender_un_led_invalido(void) {
    LedsSingleTurnOn(17);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
}

//Consultar por un led invalido
void test_consultar_un_led_invalido(void) {
    LedsRequestLedStatus(18);
    TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
    TEST_ASSERT_GREATER_THAN(1, linea_registrada);
}