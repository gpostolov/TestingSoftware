/**************************************************************************************************
 ** (c) Copyright 2019: Esteban VOLENTINI <evolentini@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/

/** @file errores.c
 ** @brief Declaraciones de la libreria para el registro de errores
 **
 ** Libreria para el registro del los errores del sistema.
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2019.06.10 | evolentini      | Version inicial del archivo para manejo de errores      |
 **
 ** @addtogroup plataforma
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */
#include <stdlib.h>
#include <string.h>
#include "errores.h"
#include "archivos.h"
#include "esp_log.h"

/* === Definicion y Macros ===================================================================== */

//! Nombre del archivo para almacenar la bitacora de errores del sistema
#define ARCHIVO    "errores.txt"

/* == Declaraciones de tipos de datos internos ================================================= */

/* === Definiciones de variables internas ====================================================== */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de funciones internas ====================================================== */

/* === Definiciones de funciones externas ====================================================== */
void RegistrarMensaje(gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...) {
    va_list argumentos;
    char cadena[128];
    // archivo_t archivo;

    va_start(argumentos, mensaje);
    vsprintf(cadena, mensaje, argumentos);
    va_end(argumentos);

    switch (gravedad) {
        case ERROR:
            ESP_LOGE(funcion, "%d: %s", linea, cadena);
            break;
        case ALERTA:
            ESP_LOGW(funcion, "%d: %s", linea, cadena);
            break;
        case INFORMACION:
            ESP_LOGI(funcion, "%d: %s", linea, cadena);
            break;
        case DEPURACION:
            ESP_LOGI(funcion, "%d: %s", linea, cadena);
            break;
        default:
            break;
    }

    // archivo = ArchivoAbrir(BITACORA_ARCHIVO, "a");
    // ArchivoMover(archivo, 0, ARCHIVO_FINAL);
    // ArchivoEscribir(archivo, cadena, strlen(cadena));
    // ArchivoCerrar(archivo);
}

/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */

