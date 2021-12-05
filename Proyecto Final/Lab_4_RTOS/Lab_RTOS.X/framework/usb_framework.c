/* ************************************************************************** */
/** USB Framework

  @File Name
    usb_framework.c

  @Description
    Implements framework level control of the USB peripheral
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "usb_framework.h"
#include "../mcc_generated_files/usb/usb.h"
#include <string.h>
#include "../mcc_generated_files/usb/usb_device_cdc.h"
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/** Buffer de recepción del USB

  @Summary
    Buffer donde se almacenarán los bytes recibidos por USB
 */
static uint8_t usb_rxBuffer[USB_RX_BUFFER_SIZE];

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/**
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 )

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.

    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/**
  @Function
    bool USB_isReady( void )

  @Summary
    Indica si el USB está listo para ser usado
 */
bool USB_isReady( void ) {
    if( (USBGetDeviceState() >= CONFIGURED_STATE) && !USBIsDeviceSuspended() ) {
        CDCTxService();
        return true;
    }
    else {
        return false;
    }
}

/**
  @Function
    uint8_t USB_recieve(void)

  @Summary
    Chequea si se recibió datos por USB
 */
uint8_t USB_recieve( void ) {
    memset(usb_rxBuffer, 0, sizeof (usb_rxBuffer));
    return getsUSBUSART(usb_rxBuffer, sizeof (usb_rxBuffer));
}

/**
  @Function
    uint8_t* USB_getRxBuffer( void )

  @Summary
    Devuelve un puntero al buffer de recepción del USB
 */
uint8_t* USB_getRxBuffer( void ) {
    return usb_rxBuffer;
}

/**
  @Function
    bool USB_sendString( uint8_t* p_data )

  @Summary
    Envía datos por USB
 */
void USB_sendString( uint8_t* p_data ) {
        putsUSBUSART(p_data);
}

/* *****************************************************************************
 End of File
 */
