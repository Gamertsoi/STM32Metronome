/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "math.h"
#include "Pattern.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t exitUserface = 0;
uint16_t BPM = 60;
uint8_t mode = 0;
uint8_t back = 0;
uint8_t currentUserface = 0;
uint8_t first = 1;
uint8_t digit = 0;
uint8_t note = 0;
uint8_t triggered = 0;
uint8_t prev = 0;
uint8_t now = 0;
uint8_t numberToShow = 1;
uint8_t err=0;
uint8_t patternstr[12];
uint8_t bit = 0;
uint8_t bar = 0;
uint8_t toggle = 0;
uint8_t tempstr[12];
uint8_t a = 0;
uint8_t b = 0;
uint8_t bit2 = 0;
uint8_t bar2 = 0;
uint8_t a2 = 0;
uint8_t b2 = 0;
uint16_t arr = 0;
char str[2];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FSMC_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Userface1()
{
	LCD_Clear ( 0, 0, 240, 360, WHITE );
	LCD_DrawString(32,12,"SELECT YOUR",BLUE,2);	//Userface 1
	LCD_DrawString(88,44,"MODE",BLUE,2);
	LCD_DrawString(16,96,"1 Traditional    mode",BLUE,2);
	LCD_DrawString(16,160,"2 Human voice    mode",BLUE,2);
	LCD_DrawString(16,224,"3 Training       mode",BLUE,2);
	while(!exitUserface)
	{
		switch(mode){
			case 0:
				LCD_DrawString(0,96,">",BLUE,2);
				LCD_DrawString(0,160," ",BLUE,2);
				LCD_DrawString(0,224," ",BLUE,2);
				break;
			case 1:
				LCD_DrawString(0,96," ",BLUE,2);
				LCD_DrawString(0,160,">",BLUE,2);
				LCD_DrawString(0,224," ",BLUE,2);
				break;
			case 2:
				LCD_DrawString(0,96," ",BLUE,2);
				LCD_DrawString(0,160," ",BLUE,2);
				LCD_DrawString(0,224,">",BLUE,2);
		}
	}
}
void displaybpm(){
	char buffer[4];
	sprintf(buffer, "%03d", BPM);
	LCD_DrawString(0,160, buffer,BLUE,10);
}
void Userface3(){
	uint16_t tempbpm = BPM;
	uint8_t tempdigit = digit;
	LCD_Clear ( 0, 0, 240, 360, WHITE );
	LCD_DrawString(48,16,"SELECT",BLUE,3);	//Userface 3
	LCD_DrawString(24,64,"YOUR BPM",BLUE,3);
	if(mode!=2){
		switch(note){
		case 0:
			if(err == 0) LCD_DrawString(24,112,"(10-260)",BLUE,3);
			else LCD_DrawString(24,112,"(10-260)",RED,3);
			break;
		case 1:
			if(err == 0) LCD_DrawString(24,112,"(10-130)",BLUE,3);
			else LCD_DrawString(24,112,"(10-130)",RED,3);
			break;
		case 2:
			if(err ==0) LCD_DrawString(36,112,"(10-65)",BLUE,3);
			else LCD_DrawString(36,112,"(10-65)",RED,3);
		}
	}
	if(mode == 2){
		if(err == 0) LCD_DrawString(24,112,"(60-256)",BLUE,3);
		else LCD_DrawString(24,112,"(60-256)",RED,3);
	}
	err = 0;
	displaybpm();
	while (!exitUserface){
		if(BPM != tempbpm){
			tempbpm = BPM;
			displaybpm();
		}
		if(digit != tempdigit){
			LCD_DrawBlank(80*tempdigit+10,290,60,10,WHITE);
			tempdigit = digit;
		}
		LCD_DrawBlank(80*digit+10,290,60,10,BLUE);
	}
}
void Userface2()
{
	LCD_Clear ( 0, 0, 240, 360, WHITE );
	LCD_DrawString(32,12,"SELECT YOUR",BLUE,2);	//Userface 2
	LCD_DrawString(40,44,"BASIC NOTE",BLUE,2);
	LCD_DrawString(16,96,"1 4th note       mode",BLUE,2);
	LCD_DrawString(16,160,"2 8th note       mode",BLUE,2);
	LCD_DrawString(16,224,"3 16th note      mode",BLUE,2);
	while(!exitUserface)
	{
		switch(note){
			case 0:
				LCD_DrawString(0,96,">",BLUE,2);
				LCD_DrawString(0,160," ",BLUE,2);
				LCD_DrawString(0,224," ",BLUE,2);
				break;
			case 1:
				LCD_DrawString(0,96," ",BLUE,2);
				LCD_DrawString(0,160,">",BLUE,2);
				LCD_DrawString(0,224," ",BLUE,2);
				break;
			case 2:
				LCD_DrawString(0,96," ",BLUE,2);
				LCD_DrawString(0,160," ",BLUE,2);
				LCD_DrawString(0,224,">",BLUE,2);
		}
	}
}
void Userface4() {
    LCD_Clear(0, 0, 240, 360, WHITE);
    numberToShow = 0;
    uint16_t psc = 1;
    uint8_t i;
    for(i = 0;i< note;i++){
    	psc = 2*psc;
    }
    arr = 2000*60 / (BPM*psc) - 1;
    __HAL_TIM_SET_AUTORELOAD(&htim3, arr);
//  __HAL_TIM_SET_AUTORELOAD(&htim2, arr/2);
//  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse);
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	//HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Base_Start_IT(&htim3);
//	HAL_TIM_Base_Start_IT(&htim2);
	while(!exitUserface){
	}
	//HAL_TIM_Base_Stop_IT(&htim4);
	HAL_TIM_Base_Stop_IT(&htim3);
//	HAL_TIM_Base_Stop_IT(&htim2);
	//__HAL_TIM_SET_COUNTER(&htim4, 0);
	__HAL_TIM_SET_COUNTER(&htim3, 0);
//	__HAL_TIM_SET_COUNTER(&htim2, 0);
//	if(toggle == 1){
//		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
//		toggle = 0;
//	}
}
void updatestr(uint8_t *str) {
    // Shift elements from index 2 to the end of the array
//    for (size_t i = 0; i < 12; i++) {
//        patternstr[i] = patternstr[i + 2];
//    }
	for (size_t i = 0; i < 12; i++){
		str[i] = rand () % 7;
	}
    // Fill the last two elements with zeros (or a value of your choice)
//    patternstr[10] = rand() % 7;
//    patternstr[11] = rand() % 7;
}
void DrawNote(uint8_t *str){
	uint8_t i;
	for(i = 0; i < 12; i++){
	  LCD_DrawNote(24+(i%2)*96,16+48*(i/2),str[i],BLUE,3);
	}
}
void DrawUpdateNote(uint8_t *str, uint8_t i, uint16_t usColor){
	uint8_t t = i+1;
	for(i = i; i < t; i++){
	  LCD_DrawNote(24+(i%2)*96,16+48*(i/2),str[i],usColor,3);
	}
}
void Userface5() {
	LCD_Clear(0, 0, 240, 360, WHITE);
	uint8_t i; // Get the current time
    unsigned int seed = clock();

    srand(seed); // Seed the random number generator
	for(i = 0; i < 12; i++){
		patternstr[i] = rand() % 7;
	}
	DrawNote(patternstr);
    bit = 0;
    bar = 0;
    a = 0;
    b = 0;
    bit2 = 0;
    bar2 = 0;
    a2 = 0;
    b2 = 0;
    uint16_t psc = 4;
    arr = 2000*60 / (BPM*psc) - 1;
    __HAL_TIM_SET_AUTORELOAD(&htim3, 1);
    __HAL_TIM_SET_AUTORELOAD(&htim2, 1);
	//HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	while(!exitUserface){
	}
	//HAL_TIM_Base_Stop_IT(&htim4);
	HAL_TIM_Base_Stop_IT(&htim3);
	HAL_TIM_Base_Stop_IT(&htim2);
	//__HAL_TIM_SET_COUNTER(&htim4, 0);
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	if(toggle == 1){
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
		toggle = 0;
	}
    bit = 0;
    bar = 0;
    a = 0;
    b = 0;
    bit2 = 0;
    bar2 = 0;
    a2 = 0;
    b2 = 0;
}
void changeUserface() {
    // Increment the userface index
	if(!first){
		if(!back && currentUserface != 3){
			if(currentUserface == 2){
					if(mode != 2){
						switch(note){
						case 0:
							if(BPM>=10&&BPM<=260){
								currentUserface = (currentUserface + 1);
							}
							break;
						case 1:
							if(BPM>=10&&BPM<=130){
								currentUserface = (currentUserface + 1);
							}
							break;
						case 2:
							if(BPM>=10&&BPM<=65){
								currentUserface = (currentUserface + 1);
							}
						}
					}
					else{
						if(BPM>=60&&BPM<=256){
							currentUserface = (currentUserface + 1);
						}
					}
					if(currentUserface!=3){
						err=1;
					}
				}
			else{
				if(mode == 2&&currentUserface == 0){
					currentUserface = (currentUserface + 2);
				}
				else {
					currentUserface = (currentUserface + 1);
				}
			}
		}
		if(back && currentUserface != 0){
			if(mode == 2&&currentUserface == 2){
				currentUserface = (currentUserface - 1);
			}
			currentUserface = (currentUserface - 1);
		}
	}
//	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	back = 0;
	exitUserface = 0;
	first = 0;
    // Switch to the next userface
    switch (currentUserface) {
        case 0:
            Userface1();
            break;
        case 1:
            Userface2();
            break;
        case 2:
            Userface3();
            break;
        case 3:
        	if(mode == 2){
        		Userface5();
        	}
        	else {
        		Userface4();
        	}
    }
}

//void InitTimer() {
//    // Configure and start the timer
//    uint16_t arr = 1000*60 / BPM - 1;
//    uint16_t pulse = arr / 2; // Calculate pulse width
//    __HAL_TIM_SET_AUTORELOAD(&htim3, arr);
//    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse);
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
//}
//
//uint32_t MeasureFunctionExecutionTime(void (*func)()) {
//    // Get start tick
//    uint32_t start = __HAL_TIM_GET_COUNTER(&htim3);
//
//    // Execute the function
//    func();
//
//    // Get end tick
//    uint32_t end = __HAL_TIM_GET_COUNTER(&htim3);
//
//    // Calculate elapsed ticks
//    uint32_t elapsed;
//    if (end >= start) {
//        elapsed = end - start;
//    } else {
//        // Handle timer overflow
//        elapsed = (htim2.Instance->ARR - start) + end;
//    }
//
//    return elapsed; // Return elapsed ticks
//}
//
//void TestFunction() {
//	while(numberToShow < 4){
//		sprintf(str, "%d", numberToShow);
//		LCD_DrawString(40, 0, str, BLUE, 20);
//		numberToShow = (numberToShow % 4) + 1;
//	}
//}
/* USER CODE END 0 */

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
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FSMC_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  LCD_INIT();
//  InitTimer();
//
//  uint32_t ticks = MeasureFunctionExecutionTime(TestFunction);
//  int time_in_seconds = ticks;
//  char buffer[5];
//  sprintf(buffer, "%04d", time_in_seconds);
//  LCD_DrawString(0,160, buffer,BLUE,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	changeUserface();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_1);
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 35999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 35999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 35999;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 999;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA4 PA5 PA6
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 255;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2){
//		if(mode == 2){
			if(toggle == 1&& a==25){
				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
				toggle = 0;
			}
			if(b == 0){
				if (pattern[4 * patternstr[bar/4] + bit] == 1 && a == 0) {  //4 * patternstr[bar/4] + bit
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
					toggle = 1;
				}
			}
			if(b == 1){
				if (pattern[4 * tempstr[bar/4] + bit] == 1 && a == 0) {  //4 * patternstr[bar/4] + bit
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
					toggle = 1;
				}
			}
			if(a == 1){
				if(bit==3&&bar==47){
					b = (b+1)%2;
				}
		        bit = (bit + 1) % 4;
		        bar = (bar + 1) % 48;
			}
//		}
		a = (a + 1) % (60*arr/BPM);
	}
    if (htim == &htim3) {
        // Check if the pattern condition is met
    	if(mode!=2){
    		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    		switch(note){
    		case 0:
    			sprintf(str, "%d", numberToShow+1);
				LCD_DrawString(40, 0, str, BLUE, 20);
				numberToShow = (numberToShow+1) % 4;
				break;
    		case 1:
    			if(numberToShow%2 == 0){
    				sprintf(str, "%d", numberToShow/2+1);
    				LCD_DrawString(40, 0, str, BLUE, 20);
    			}
    			else{
    				LCD_DrawString(40, 0, "N", BLUE, 20);
    			}
    			numberToShow = (numberToShow+1) % 8;
    			break;
    		case 2:
    			switch(numberToShow%4){
    			case 0:
    				sprintf(str, "%d", numberToShow/4+1);
    				LCD_DrawString(40, 0, str, BLUE, 20);
    				break;
    			case 1:
    				LCD_DrawString(40, 0, "E", BLUE, 20);
    				break;
    			case 2:
    				LCD_DrawString(40, 0, "N", BLUE, 20);
    				break;
    			case 3:
    				LCD_DrawString(40, 0, "A", BLUE, 20);
    			}
    			numberToShow = (numberToShow+1) % 16;
    		}
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    	}
        // If bar and bit conditions are met, update the pattern string
    	else{
    		if(bar2 /4 == 0 && bit2 == 3 && a2 == 1){
    			if(b2 == 0){
    				updatestr(tempstr);
    			}
       			else{
     				updatestr(patternstr);
       			}
    		}
    		if(bit2 == 3 && a2 == 26){
    			if(b2 == 0){
    				DrawUpdateNote(tempstr,bar2 /4, RED);
    			}
       			else{
       				DrawUpdateNote(patternstr,bar2 /4,BLUE);
       			}
    			if(bar2 /4 == 11){
    				b2 = (b2+1)%2;
    			}
    		}
//    		if (bar2 /4 == 5 && bit2 == 3 && a2 == 1) {
//    			if(b2 == 0){
//        			updatestr(tempstr);
//    			}
//    			else{
//    				updatestr(patternstr);
//    			}
//    		}
////    		if (bar2 /4 == 11 && bit2 == 3 && a2 == 26) {
////    			if(b2 == 0){
////        			DrawNote(tempstr);
////    			}
////    			else{
////    				DrawNote(patternstr);
////    			}
////    			b2 = (b2+1)%2;
////    		}
//    		if (bar2 /4 == 6 && bit2 == 3 && a2 == 26) {
//    			if(b2 == 0){
//        			DrawUpdateNote(tempstr,0,RED);
//    			}
//    			else{
//    				DrawUpdateNote(patternstr,0,BLUE);
//    			}
//    		}
//    		if (bar2 /4 == 7 && bit2 == 3 && a2 == 26) {
//    			if(b2 == 0){
//        			DrawUpdateNote(tempstr,2,RED);
//    			}
//    			else{
//    				DrawUpdateNote(patternstr,2,BLUE);
//    			}
//    		}
//    		if (bar2 /4 == 8 && bit2 == 3 && a2 == 26) {
//    			if(b2 == 0){
//        			DrawUpdateNote(tempstr,4,RED);
//    			}
//    			else{
//    				DrawUpdateNote(patternstr,4,BLUE);
//    			}
//    		}
//    		if (bar2 /4 == 9 && bit2 == 3 && a2 == 26) {
//    			if(b2 == 0){
//        			DrawUpdateNote(tempstr,6,RED);
//    			}
//    			else{
//    				DrawUpdateNote(patternstr,6,BLUE);
//    			}
//    		}
//    		if (bar2 /4 == 10 && bit2 == 3 && a2 == 26) {
//    			if(b2 == 0){
//        			DrawUpdateNote(tempstr,8,RED);
//    			}
//    			else{
//    				DrawUpdateNote(patternstr,8,BLUE);
//    			}
//    		}
//    		if (bar2 /4 == 11 && bit2 == 3 && a2 == 26) {
//    			if(b2 == 0){
//        			DrawUpdateNote(tempstr,10,RED);
//    			}
//    			else{
//    				DrawUpdateNote(patternstr,10,BLUE);
//    			}
//    			b2 = (b2+1)%2;
//    		}
			if(a2 == 0){
		        bit2 = (bit2 + 1) % 4;
		        bar2 = (bar2 + 1) % 48;
			}
    		a2 = (a2 + 1) % (60*arr/BPM);
    	}
    }

        // Update bit and bar
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
