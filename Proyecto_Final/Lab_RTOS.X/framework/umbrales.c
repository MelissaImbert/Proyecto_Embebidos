#include "umbrales.h"


#define LED_QTY_IN_ARRAY 8 

float umbral_brusco=5;
float umbral_choque=8;

static ws2812_t ledArray[LED_QTY_IN_ARRAY];

// (2^16)-1 = 65535, preciso dividir este valor en 8 umbrales por lo tanto c/u abarca 8191 (aprox))
int dividir_umbrales(uint16_t valor){
    if(valor >= 7*8191){
        return 7;
    }
    if(valor >= 6*8191){ 
        return 6;
    }
    if(valor >= 5*8191){
        return 5;
    }
    if(valor >= 4*8191){
        return 4;
    }
    if(valor >= 3*8191){
        return 3;
    }
    if(valor >= 2*8191){
        return 2;
    }
    if(valor >= 8191){
        return 1;
    }
    if(valor <= 8191){
        return 0;
    }  
}


void definir_umbral(void){
    int numero_de_leds;
    do{
    uint16_t value = ANALOG_getResult();
    numero_de_leds=dividir_umbrales(value);
    
    switch(numero_de_leds){
        case 0:
            ledArray={BLUE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK};
            break;
        case 1:
            ledArray={BLUE,BLUE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK};
            break;
        case 2:
            ledArray={BLUE,BLUE,BLUE,BLACK,BLACK,BLACK,BLACK,BLACK};
            break;
        case 3:
            ledArray={BLUE,BLUE,BLUE,BLUE,BLACK,BLACK,BLACK,BLACK};
            break;
        case 4:
            ledArray={BLUE,BLUE,BLUE,BLUE,BLUE,BLACK,BLACK,BLACK};
            break;    
        case 5:
            ledArray={BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLACK,BLACK};
            break;
        case 6:
            ledArray={BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLACK};
            break;    
        case 7:
            ledArray={BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE};
            break;    
          }
        WS2812_send(ledArray, LED_QTY_IN_ARRAY);   
        } while (BOTON = 1);  //interrupcion de boton distinto del de interfaz para indicar confirmacion de valor     
    }


//6535 ---- 10
//entrada --x  ---> entrada*10/6535
//hago regla de 3 para saber a que valor de aceleracion corresponde el valor establecido por el adc (umbral)

//preciso una funcion que relacione el valor del acelerometro con los umbrales establecidos

void relacion_adc_acelerometro_brusco(void){
    int value = dividir_umbrales(ANALOG_getResult())+1;
    //si mi aceleracion maxima es 10, haciendo regla de 3 con value
    //8 -- 10  
    //value--x --> value*10/7=x 
    float aux = value*10/8;
    if (aux<=umbral_choque){
        umbral_brusco = aux;
    }else{
        //imprime error
    }
}

void relacion_adc_acelerometro_choque(void){
    int value = dividir_umbrales(ANALOG_getResult())+1;
    //si mi aceleracion maxima es 10, haciendo relga de 3 con value
    //7 -- 10  
    //value--x --> value*10/7=x 
    float aux = value*10/8;
    if (aux>=umbral_brusco){
        umbral_choque = aux;
        
    }else{
        //imprime error      
    }
}

void UMBRAL(int param){
    switch(param){
        case 0:
            definir_umbral();
            relacion_adc_acelerometro_brusco();
            
            break;
        case 1:
            definir_umbral();
            relacion_adc_acelerometro_choque();
     
            break;
        default:
            //seleccione denuevo?
            return;       
    }              
    
}