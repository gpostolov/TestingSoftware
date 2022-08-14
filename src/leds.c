#include "leds.h"

#define LEDS_OFFSET     1
#define FIRST_BIT_ON    1
#define LEDS_ALL_OFF    0x0000
#define LEDS_ALL_ON    	0xFFFF

/* Private */
static uint16_t *puerto;
static registro_errores_t NotificarError;

static uint16_t LedToMask(uint8_t led) {
    return (FIRST_BIT_ON << (led - LEDS_OFFSET));
}

/* Public */
void LedsCreate (uint16_t *address, registro_errores_t errores) {
    puerto = address;
    NotificarError = errores;
    LedsAllTurnOff();
}

void LedsSingleTurnOn (uint8_t led) {
    if( led > 16 ) {
        NotificarError(ALERTA, __FUNCTION__, __LINE__, "Numero de LED invalido");
    } else {
        *puerto |= LedToMask(led);
    }
}

void LedsSingleTurnOff (uint8_t led) {
    if( led > 16 ) {
        NotificarError(ALERTA, __FUNCTION__, __LINE__, "Numero de LED invalido");
    } else {
        *puerto &= ~LedToMask(led);
    }
}

void LedsAllTurnOn (void) {
    *puerto = LEDS_ALL_ON;
}

void LedsAllTurnOff (void) {
    *puerto = LEDS_ALL_OFF;
}

led_status_t LedsRequestLedStatus (uint8_t led){
    if( led > 16 ) {
        NotificarError(ALERTA, __FUNCTION__, __LINE__, "Numero de LED invalido");
    } else {
        if ((*puerto) & LedToMask(led)){
            return LED_STATUS_ON;
        }else{
            return LED_STATUS_OFF;
        }
    }
}
