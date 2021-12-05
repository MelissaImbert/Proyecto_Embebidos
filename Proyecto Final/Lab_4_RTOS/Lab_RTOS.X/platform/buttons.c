#include "buttons.h"
#include "../framework/UserInterface.h"
#include "../freeRTOS/include/FreeRTOS.h"
#include "../freeRTOS/include/task.h"
#include "../mcc_generated_files/pin_manager.h"

void userInterfaceButton(void *p_param){
    for(;;){
        if(BTN2_GetValue()){
         xTaskCreate( initInterface, "interfaz",  configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+3, NULL );    
         vTaskDelete(NULL); 
       }           
    }
}

void setUmbralButton(void *p_param){
    for(;;){
        if(BTN1_GetValue()){
            umbralset = false;
        }
    }
}