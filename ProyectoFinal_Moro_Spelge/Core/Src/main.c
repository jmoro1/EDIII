/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
#include "semphr.h"

/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId PIDTaskHandle;
osThreadId TomaDeDatosTaskHandle;
SemaphoreHandle_t xSemaphore;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void StartDefaultTask(void const * argument);
void PIDTask(void *pvParameters);
void TomaDeDatosTask(void *pvParameters);

/**
  * @brief  The application entry point.
  * @retval int
  */
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


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  xSemaphore = xSemaphoreCreateBinary();
  if (xSemaphore != NULL) {
    xSemaphoreGive(xSemaphore);
  }
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  xTaskCreate(PIDTask, "PIDTask", 128, NULL, osPriorityAboveNormal, &PIDTaskHandle);
  xTaskCreate(TomaDeDatosTask, "TomaDeDatosTask", 128, NULL, osPriorityNormal, &TomaDeDatosTaskHandle);
  /* USER CODE END RTOS_THREADS */

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

/**
  * @brief  Function implementing the PIDTask thread.
  * @param  pvParameters: Not used
  * @retval None
  */
void PIDTask(void *pvParameters) {
  /* USER CODE BEGIN 4 */
  for (;;) {
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
      // Código de control PID
      xSemaphoreGive(xSemaphore);
    }
    vTaskDelay(10);
  }
  /* USER CODE END 4 */
}

/**
  * @brief  Function implementing the TomaDeDatosTask thread.
  * @param  pvParameters: Not used
  * @retval None
  */
void TomaDeDatosTask(void *pvParameters) {
  /* USER CODE BEGIN 5 */
  for (;;) {
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
      // Código de toma de datos
      xSemaphoreGive(xSemaphore);
    }
    vTaskDelay(100);
  }
  /* USER CODE END 5 */
}

/**
  * @brief Function implementing the defaultTask thread.
  * @param argument: Not used
  * @retval None
  */
void StartDefaultTask(void const * argument) {
  /* USER CODE BEGIN 6 */
  for(;;) {
    osDelay(1);
  }
  /* USER CODE END 6 */
}
