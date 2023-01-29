#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"

/*
1 - B2
2 - B1          11 - B4
3 - B12         10 - B5
4 - B13          9 - B6
5 - B14          8 - B7
6 - B0           7 - B8
*/ 


const uint16_t SALL =  L1_Pin // средная
                    | L2_Pin // нижная с права
                    | L3_Pin // точка
                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
                    | L6_Pin // Верхний слева
                    | L7_Pin // верхний
                    | L8_Pin; // нижний слева

const uint16_t  S0 =(
//                      L1_Pin // средная
                      L2_Pin // нижная с права
//                    | L3_Pin // точка
                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
                    | L6_Pin // Верхний слева
                    | L7_Pin // верхний
                    | L8_Pin); // нижний слева

const uint16_t S1 = (
//                     L1_Pin // средная
                     L2_Pin // нижная с права
//                    | L3_Pin // точка
//                    | L4_Pin // нижний
                    | L5_Pin); // верхний с права
//                    | L6_Pin // верхний слева
//                    | L7_Pin // верхний
//                    | L8_Pin // нижний слева

const uint16_t S2 =   L1_Pin // средная
//                    | L2_Pin // нижная с права
//                    | L3_Pin // точка
                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
//                    | L6_Pin // верхний слева
                    | L7_Pin // верхний
                    | L8_Pin; // нижний слева

const uint16_t S3 =   L1_Pin // средная
                    | L2_Pin // нижная с права
//                    | L3_Pin // точка
                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
//                    | L6_Pin // Верхний слева
                    | L7_Pin;// верхний
//                    | L8_Pin; // нижний слева

const uint16_t S4 =   L1_Pin // средная
                    | L2_Pin // нижная с права
//                    | L3_Pin // точка
//                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
                    | L6_Pin; // Верхний слева
//                    | L7_Pin // верхний
//                    | L8_Pin; // нижний слева

const uint16_t S5 =   L1_Pin // средная
                    | L2_Pin // нижная с права
//                    | L3_Pin // точка
                    | L4_Pin // нижний
//                    | L5_Pin // верхний с права
                    | L6_Pin // Верхний слева
                    | L7_Pin;// верхний
//                    | L8_Pin; // нижний слева

const uint16_t S6 =   L1_Pin // средная
                    | L2_Pin // нижная с права
//                    | L3_Pin // точка
                    | L4_Pin // нижний
//                    | L5_Pin // верхний с права
                    | L6_Pin // Верхний слева
                    | L7_Pin // верхний
                    | L8_Pin; // нижний слева

const uint16_t S7 = //  L1_Pin // средная
                      L2_Pin // нижная с права
//                    | L3_Pin // точка
//                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
//                    | L6_Pin // Верхний слева
                    | L7_Pin; // верхний
//                    | L8_Pin; // нижний слева

const uint16_t S8 =   L1_Pin // средная
                    | L2_Pin // нижная с права
//                    | L3_Pin // точка
                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
                    | L6_Pin // Верхний слева
                    | L7_Pin // верхний
                    | L8_Pin; // нижний слева

const uint16_t S9 =   L1_Pin // средная
                    | L2_Pin // нижная с права
//                    | L3_Pin // точка
                    | L4_Pin // нижний
                    | L5_Pin // верхний с права
                    | L6_Pin // Верхний слева
                    | L7_Pin;// верхний
//                    | L8_Pin; // нижний слева

const uint16_t BS = 0;
const uint16_t STOCHKA= L3_Pin; // точка
const uint16_t DIGIT[] = { S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, STOCHKA, BS};

/*
void showA(void)
{
    HAL_GPIO_WritePin(GPIOB, L1_Pin , GPIO_PIN_RESET); // средная
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L1_Pin , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, L2_Pin , GPIO_PIN_RESET); // нижная с права
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L2_Pin , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, L3_Pin , GPIO_PIN_RESET); // точка
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L3_Pin , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, L4_Pin , GPIO_PIN_RESET); // нижний
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L4_Pin , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, L5_Pin , GPIO_PIN_RESET); // верхний с права
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L5_Pin , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, L6_Pin , GPIO_PIN_RESET); // Верхний слева
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L6_Pin , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, L7_Pin , GPIO_PIN_RESET);  // верхний
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L7_Pin , GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, L8_Pin , GPIO_PIN_RESET); // нижний слева
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, L8_Pin , GPIO_PIN_SET);
}
*/

void ss(uint16_t s){
    HAL_GPIO_WritePin(GPIOB, s    , GPIO_PIN_RESET); 
    HAL_GPIO_WritePin(GPIOB, SALL-s, GPIO_PIN_SET); 
}

static uint32_t light = 50;
static uint16_t dig[]={0,0,0};

void Display(uint16_t arg)
{
    static uint16_t old = 0;
    if(old != arg){
      if(arg>3999){
        dig[0] = DIGIT[10];
        dig[1] = DIGIT[10];
        dig[2] = DIGIT[10];
      }else{
        old = arg;
        //uint16_t n = arg;
        // dig[0] = DIGIT[n%10]; n/=10;
        // dig[1] = (n>0) ? DIGIT[n%10] :DIGIT[11]; n/=10;
        // dig[2] = (n>0) ? DIGIT[n]    :DIGIT[11];

        if(arg<40){
        uint16_t n=arg*(100/4);
        dig[0] = DIGIT[n%10]; n/=10;
        dig[1] = DIGIT[n%10]; n/=10;
        dig[2] = DIGIT[n] | STOCHKA;
        }
        else if(arg<400){
        uint16_t n=(arg*10)/4;
        dig[0] = DIGIT[n%10]; n/=10;
        dig[1] = DIGIT[n%10] | STOCHKA; n/=10; 
        dig[2] = DIGIT[n];
        }else{
        // >400
        uint16_t n=arg/4;
        dig[0] = DIGIT[n%10]; n/=10;
        dig[1] = DIGIT[n%10]; n/=10;
        dig[2] = DIGIT[n];
        }
      }
    }
}

void Light(uint32_t arg){light=arg;}

void _show()
{
    ss(dig[2]);
    if(dig[2]) HAL_GPIO_WritePin(GPIOB, H0_Pin , GPIO_PIN_SET);  // старший
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, H0_Pin , GPIO_PIN_RESET);
    osDelay(light);

    ss(dig[1]);
    if(dig[1]) HAL_GPIO_WritePin(GPIOB, H2_Pin , GPIO_PIN_SET);  // средний
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, H2_Pin , GPIO_PIN_RESET);
    osDelay(light);

    ss(dig[0]);
    HAL_GPIO_WritePin(GPIOB, H1_Pin , GPIO_PIN_SET); // младший
    osDelay(1);
    HAL_GPIO_WritePin(GPIOB, H1_Pin , GPIO_PIN_RESET);
    osDelay(light);
}
