#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"

#ifdef __cplusplus
extern "C" {
#endif

    void SystemClock_Config(void);
//    void main_init(void);
    void MX_GPIO_Init(void);
    void MX_SPI1_Init(void);
    //SPI_HandleTypeDef SpiHandle;
    void HAL_SPI1_IRQHandler(SPI_HandleTypeDef *hspi);

#ifdef __cplusplus
}
#endif
/* 
 RLS2381BBB вид сверху (орентируйся по 12 ноге которой нет), 
 распаян на порт B проца STM32F401CC

1 - B2          12 - нет ноги
2 - B1          11 - B4
3 - B12         10 - B5
4 - B13          9 - B6
5 - B14          8 - B7
6 - B0           7 - B8
*/ 
extern void _show();
    
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
typedef StaticEventGroup_t osStaticEventGroupDef_t;

/* Private variables ---------------------------------------------------------*/
extern SPI_HandleTypeDef hspi1;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Max6675 */
osThreadId_t Max6675Handle;
uint32_t Max6675Buffer[ 128 ];
osStaticThreadDef_t Max6675ControlBlock;
const osThreadAttr_t Max6675_attributes = {
  .name = "Max6675",
  .cb_mem = &Max6675ControlBlock,
  .cb_size = sizeof(Max6675ControlBlock),
  .stack_mem = &Max6675Buffer[0],
  .stack_size = sizeof(Max6675Buffer),
  .priority = (osPriority_t) osPriorityLow,
};

void StartDefaultTask(void *argument);
void StartMax6675(void *argument);

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
#if 1
  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Max6675 */
  Max6675Handle = osThreadNew(StartMax6675, NULL, &Max6675_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
#else 
  MX_FREERTOS_Init();
#endif
  /* Start scheduler */
  osKernelStart();
      
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
#define BUFFERSIZE 2
/* Buffer used for transmission */
//uint16_t aTxBuffer[] = {0X5555,0XAAAA};
/* Buffer used for reception */
uint16_t aRxBuffer[BUFFERSIZE];
const int FILTER_SIZE = 16;
uint16_t Filter[FILTER_SIZE];
uint32_t cFilter = 0; //позиция в буфере

void TxSpiIT(SPI_HandleTypeDef *hspi);
void StartMax6675(void *argument)
{
  /* USER CODE BEGIN StartMax6675 */
  /* Infinite loop */
  HAL_GPIO_WritePin(GPIOB, 
                      L5_Pin|L6_Pin|L7_Pin|L8_Pin|L1_Pin|L2_Pin|L3_Pin|L4_Pin
                      , GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, H0_Pin|H1_Pin|H2_Pin , GPIO_PIN_RESET);


  for(;;)
  {
    uint32_t t= 0;
    TxSpiIT(&hspi1);
    osDelay(2000);
    // усреднение по 16 отсчётам
    Filter[cFilter++] = aRxBuffer[0]>>3;
    if( cFilter >= 16 ) cFilter = 0;
    t=0;
    for(int i=0;i<16;i++){
      t+=Filter[i];
    }
    Display( t>>4 );
    
  }
  /* USER CODE END StartMax6675 */
}


/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  HAL_GPIO_WritePin(LED_GREEN_BOARD_GPIO_Port, LED_GREEN_BOARD_Pin,GPIO_PIN_SET);
  for(;;)
  {
    //HAL_GPIO_TogglePin(LED_GREEN_BOARD_GPIO_Port, LED_GREEN_BOARD_Pin);
    _show();
  }
  /* USER CODE END 5 */
}
//---------------------------------------------------------------

// TxSpiIT(&hspi1);
void TxSpiIT(SPI_HandleTypeDef *hspi)
{
  /* Enable TXE, RXNE and ERR interrupt */
  __HAL_SPI_ENABLE_IT(hspi, ( SPI_IT_TXE | SPI_IT_RXNE /*| SPI_IT_ERR*/));

  /* Enable SPI peripheral */
  __HAL_SPI_ENABLE(hspi);

}

void HAL_SPI1_IRQHandler(SPI_HandleTypeDef *hspi)
{
  uint32_t itsource = hspi->Instance->CR2;
  uint32_t itflag   = hspi->Instance->SR;

  if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) == RESET) &&
      (SPI_CHECK_FLAG(itflag, SPI_FLAG_TXE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_TXE) != RESET))
  {
    hspi->Instance->DR = 0xAA55;
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);
    return;
  }

  /* SPI in mode Receiver ----------------------------------------------------*/
  if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) == RESET) &&
      (SPI_CHECK_FLAG(itflag, SPI_FLAG_RXNE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_RXNE) != RESET))
  {
    /* Receive data in 16 Bit mode */
    aRxBuffer[0]=(uint16_t)(hspi->Instance->DR);

    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);

    return;
  }

  __disable_irq();

  /* SPI in Error Treatment --------------------------------------------------*/
  if (((SPI_CHECK_FLAG(itflag, SPI_FLAG_MODF) != RESET) || (SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) != RESET)
       || (SPI_CHECK_FLAG(itflag, SPI_FLAG_FRE) != RESET)) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_ERR) != RESET))
  {
    while (1){ }
  }
  while (1){ }
}

