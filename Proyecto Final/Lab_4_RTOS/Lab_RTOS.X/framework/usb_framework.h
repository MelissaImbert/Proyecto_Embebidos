/* ************************************************************************** */
/** USB Framework

  @File Name
    usb_framework.c

  @Description
    Implements framework level control of the USB peripheral
 */
/* ************************************************************************** */

#ifndef _USB_FRAMEWORK_H    /* Guard against multiple inclusion */
#define _USB_FRAMEWORK_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/** Tamaño del buffer de recepción del USB

  @Summary
    Especifica el tamaño en bytes del buffer de recepción del USB

  @Remarks
    Esta definido como 254 en base a la documentación de la función
    putUSBUSART (archivo usb_device_cdc.h), que especifica el largo que se puede
    esperar debe ser menor a 255
 */
#define USB_RX_BUFFER_SIZE  254

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/**
  @Function
    bool USB_isReady( void )

  @Summary
    Indica si el USB está listo para ser usado

  @Description
    Indica si el USB está listo para ser usado.
    Es necesario llamar esta función periódicamente para mantener en
    funcionamiento el USB

  @Precondition
    El periférico USB Device Lite debe estar configurado en el Microchip
    Code Configurator (MCC)

  @Parameters
    Ninguno

  @Returns
    <ul>
      <li>true  El USB está listo para ser usado
      <li>false El USB no está listo para ser usado
    </ul>

  @Example
    @code
    if( USB_isReady() ) {
        // Send data through USB
    }
 */
bool USB_isReady(void);

/**
  @Function
    uint8_t USB_recieve(void)

  @Summary
    Chequea si se recibió datos por USB

  @Description
    Chequea si se recibió datos por USB. En caso de haber recibido, los copia
    al buffer de recepción del USB y devuelve la cantidad de bytes recibidos

  @Precondition
    USB_isReady debe haber devuelto "true"

  @Parameters
    Ninguno

  @Returns
    Cantidad de bytes recibidos por USB. Si no se recibieron datos, devuelve 0

  @Example
    @code
    if( USB_isReady() ) {
        USB_recieve();
        // Procesar datos recibidos
    }
 */
uint8_t USB_recieve(void);

/**
  @Function
    uint8_t* USB_getRxBuffer( void )

  @Summary
    Devuelve un puntero al buffer de recepción del USB

  @Description
    Devuelve un puntero al buffer de recepción del USB

  @Precondition
    USB_isReady debe haber devuelto "true"

  @Parameters
    Ninguno

  @Returns
    Puntero al buffer de recepción del USB

  @Example
    @code
    if( USB_isReady() ) {
        USB_recieve();
        if( strcmp( USB_getRxBuffer(), "Hola Mundo" ) == 0 ) {
            // Se recibió "Hola Mundo" por USB
        }
    }
 */
uint8_t* USB_getRxBuffer(void);

/**
  @Function
    bool USB_sendString( uint8_t* p_data )

  @Summary
    Envía datos por USB

  @Description
    Envía datos por USB, chequeando primero que el USB esté libre para enviar datos

  @Precondition
    USB_isReady debe haber devuelto "true"

  @Parameters
    Puntero a la dirección donde se encuentran los datos a enviar por USB

  @Returns
    <ul>
      <li>true  El USB estaba listo para enviar datos y se enviaron
      <li>false El USB no estaba listo para enviar datos
    </ul>

  @Example
    @code
    if( USB_isReady() ) {
        USB_sentString( "Hola Mundo" );
    }
 */
void USB_sendString(uint8_t* p_data);

#endif /* _USB_FRAMEWORK_H */

/* *****************************************************************************
 End of File
 */
