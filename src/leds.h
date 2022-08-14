#include <stdint.h>
#include "errores.h"

typedef enum led_status_e {
    LED_STATUS_OFF = 0,
    LED_STATUS_ON = 1
}led_status_t;

void LedsCreate (uint16_t *address, registro_errores_t errores);
void LedsSingleTurnOn (uint8_t led);
void LedsSingleTurnOff (uint8_t led);
void LedsAllTurnOn (void);
void LedsAllTurnOff (void);
led_status_t LedsRequestLedStatus (uint8_t led);
