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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t TxData_SOC[8] = {0x03, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t TxData_volt[8] = {0x03, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t TxData_temp[8] = {0x55, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t TxData_mos[8] = {0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t TxData_status[8] = {0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t TxData_cell_volt[16][8]={
		{0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x00},  // Frame 0
		    {0x01, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x00},  // Frame 1
		    {0x02, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x00},  // Frame 2
		    {0x03, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x00},  // Frame 3
		    {0x04, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0x00},  // Frame 4
		    {0x05, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0x00},  // Frame 5
		    {0x06, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x00},  // Frame 6
		    {0x07, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x00},  // Frame 7
		    {0x08, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x00},  // Frame 8
		    {0x09, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x00},  // Frame 9
		    {0x0A, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x00},  // Frame 10
		    {0x0B, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x00},  // Frame 11
		    {0x0C, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x00},  // Frame 12
		    {0x0D, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x00},  // Frame 13
		    {0x0E, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x00},  // Frame 14
		    {0x0F, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x00}   // Frame 15
};

uint8_t TxData_cell_temp[3][8] = {
    {0x00, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30},  // Frame 0
    {0x01, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37},  // Frame 1
    {0x02, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E}   // Frame 2
};


uint8_t TxData_cell_balance[8] = {0x03, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t TxData_failuer[8] = {0x03, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


uint8_t ID_soc = 0x90;
uint8_t ID_volt = 0x91;
uint8_t ID_temp = 0x92;
uint8_t ID_mos = 0x93;
uint8_t ID_cell_volt = 0x94;
uint8_t ID_status = 0x95;
uint8_t ID_cell_temp= 0x96;
uint8_t ID_cell_balance= 0x97;
uint8_t ID_failure= 0x98;


uint8_t IDR_soc = 0x10;
uint8_t IDR_volt = 0x11;
uint8_t IDR_temp = 0x12;
uint8_t IDR_mos = 0x13;
uint8_t IDR_cell_volt = 0x14;
uint8_t IDR_status = 0x15;
uint8_t IDR_cell_temp= 0x16;
uint8_t IDR_cell_balance= 0x17;
uint8_t IDR_failure= 0x18;
uint8_t select = 0;

uint8_t RxData[8];

CAN_RxHeaderTypeDef RxHeader;
CAN_TxHeaderTypeDef TxHeader;
CAN_FilterTypeDef sFilterConfig;
uint32_t TxMailbox;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */
   TxHeader.DLC = 8;
   TxHeader.IDE = CAN_ID_STD;
   TxHeader.RTR = CAN_RTR_DATA;

   sFilterConfig.FilterBank = 0;
   sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
   sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
   sFilterConfig.FilterIdHigh = 0x10<< 5  | (1 << 4);
   sFilterConfig.FilterMaskIdHigh =0xF0 << 5 | (1 << 4);
   sFilterConfig.FilterIdLow =  0x10<< 5 | (1 << 4);
   sFilterConfig.FilterMaskIdLow = 0xF0<< 5  | (1 << 4);
   sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
   sFilterConfig.FilterActivation = ENABLE;

   HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);

   HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING );

   HAL_CAN_Start(&hcan1);

  // HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) ;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (select == 1)
	  {
		        TxHeader.StdId = ID_soc ;
		        HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_SOC, &TxMailbox) ;
		        select = 0 ;

	  }else if (select == 2 )
	  {
	        TxHeader.StdId = ID_volt ;
	        HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_volt, &TxMailbox) ;
	        select = 0 ;
	  }
	  else if (select == 3 )
	  	  {
	        TxHeader.StdId = ID_temp ;
	        HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_temp , &TxMailbox) ;
	        select = 0 ;
	  	  }
	  else if (select == 4 )
	  	  {
	        TxHeader.StdId = ID_mos ;
	        HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_mos , &TxMailbox) ;
	        select = 0 ;
	  	  }
	  else if (select == 5 )
	  	  {
	        TxHeader.StdId = ID_cell_volt ;
	        for (int i = 0; i < 16; i++) {
	        HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_cell_volt[i] , &TxMailbox) ;
	  	  }select = 0 ;}
	  else if (select == 6 )
	  	  {
		  TxHeader.StdId = ID_status ;
		  HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_status , &TxMailbox) ;
		  select = 0 ;
	  	  }
	  else if (select == 7 )
	  	  {   TxHeader.StdId = ID_cell_temp ;
		  for (int i = 0; i < 3; i++) {
			  HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_cell_temp[i], &TxMailbox) ;

		    }
		  select = 0 ;
}
	  else if (select == 8 )
	  	  {
		  TxHeader.StdId = ID_cell_balance ;
		  HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_cell_balance , &TxMailbox) ;
		  select = 0 ;
	  	  }
	  else if (select == 9 )
	  	  {
		  TxHeader.StdId = ID_failure ;
		  HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData_failuer , &TxMailbox) ;
		  select = 0 ;
	  	  }

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 16;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_5TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
        if (RxHeader.StdId == IDR_soc) {
					select = 1;
				}
        else if (RxHeader.StdId == IDR_volt) {
					select = 2 ;
				}
        else if (RxHeader.StdId == IDR_temp) {
                	select = 3 ;
                }
        else if (RxHeader.StdId == IDR_mos) {
                	select = 4 ;
                }
        else if (RxHeader.StdId == IDR_cell_volt) {
                	select = 5 ;
                }
        else if (RxHeader.StdId == IDR_status) {
                	select = 6 ;
                }
        else if (RxHeader.StdId == IDR_cell_temp) {
                	select = 7 ;
                }
        else if (RxHeader.StdId == IDR_cell_balance) {
                	select = 8 ;
                }
        else if (RxHeader.StdId == IDR_failure) {
                	select = 9 ;
                }
        else {
        	select = 0 ;
        }

    	//HAL_UART_Transmit(&huart1, RxData, sizeof(RxData), 100);


    	HAL_Delay(100);




    }
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
