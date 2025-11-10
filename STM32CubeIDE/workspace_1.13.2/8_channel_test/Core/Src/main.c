/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include <stdio.h>
#include <stdlib.h>  // pour rand()
#include <time.h>
#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "EIGHTCHANNEL.h"
#include "EIGHTCHANNEL_data.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART2_UART_Init(void);
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
	/* USER CODE BEGIN PV */
	char buf[100];
	int buf_len = 0;
	ai_handle ai_model = AI_HANDLE_NULL;
	ai_error ai_err;
	ai_i32 nbatch;
	float y_val;
	uint32_t timestamp;

	// Mémoire pour le modèle
	AI_ALIGNED(4) ai_u8 activations[AI_EIGHTCHANNEL_DATA_ACTIVATIONS_SIZE];
	AI_ALIGNED(4) ai_i8 in_data[AI_EIGHTCHANNEL_IN_1_SIZE];
	AI_ALIGNED(4) ai_i8 out_data[AI_EIGHTCHANNEL_OUT_1_SIZE];

	// Buffers d’entrée et de sortie
	ai_buffer* ai_input = NULL;
	ai_buffer* ai_output = NULL;
	ai_u16 n_input = 0, n_output = 0;
	/* USER CODE END PV */

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
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim6);

  // Création du réseau
  ai_err = ai_eightchannel_create(&ai_model, AI_EIGHTCHANNEL_DATA_CONFIG);
  if (ai_err.type != AI_ERROR_NONE) {
      buf_len = sprintf(buf, "Error: model create failed\r\n");
      HAL_UART_Transmit(&huart2, (uint8_t*)buf, buf_len, 100);
      Error_Handler();
  }

  // Initialisation du réseau
  ai_network_params ai_params = {
      AI_EIGHTCHANNEL_DATA_WEIGHTS(ai_eightchannel_data_weights_get()),
      AI_EIGHTCHANNEL_DATA_ACTIVATIONS(activations)
  };
  if (!ai_eightchannel_init(ai_model, &ai_params)) {
      buf_len = sprintf(buf, "Error: model init failed\r\n");
      HAL_UART_Transmit(&huart2, (uint8_t*)buf, buf_len, 100);
      Error_Handler();
  }

  // Récupération des buffers
  ai_input = ai_eightchannel_inputs_get(ai_model, &n_input);
  ai_output = ai_eightchannel_outputs_get(ai_model, &n_output);

  if (!ai_input || !ai_output || n_input == 0 || n_output == 0) {
      buf_len = sprintf(buf, "Error: invalid I/O\r\n");
      HAL_UART_Transmit(&huart2, (uint8_t*)buf, buf_len, 100);
      Error_Handler();
  }




ai_input[0].data = AI_HANDLE_PTR(in_data);
  ai_output[0].data = AI_HANDLE_PTR(out_data);

  buf_len = sprintf(buf, "Model ready!\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t*)buf, buf_len, 100);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  srand(HAL_GetTick());
  while (1)
  {

	  // Test 1 : valeurs très grandes
	//  float sample_input[8] = {1.0, -0.5, 0.2, -0.3, 0.5, -0.3, 0.4, 0.1};

	  // Test 2 : valeurs dans [−100, 100]
	// float sample_input[8] = {50, -40, 25, 60, -10, 30, -5, 80}
	  // Test 3 : valeurs entre [−1e-3, 1e-3]
	// float sample_input[8] = {0.001, -0.0005, 0.0007, -0.0008, 0.0006, -0.0003, 0.0004, 0.0001};
	  float sample_input[8] = {8e-04,-0.00038,-9e-05,-2e-05,0.00022,-2e-05,1e-04,5e-05};

	 // Moyennes et écarts-types calculés sur X_train
	  float mean[8] = {-7.96011128e-06,-9.66981720e-06,-9.66191935e-06,-9.05605807e-06,-1.71333915e-05,-1.17907679e-05,-9.62428404e-06,-1.23505565e-05};
	  float std[8]  = {0.00020818,0.00012829,0.00013016,0.00025104,0.0003306,0.00026214,0.00016807,0.00022023};
	  float input_scale = 0.070308536f;
	  int input_zero_point = -12;
	  // Normalisation


      for (int i = 0; i < 8; i++) {
          float norm = (sample_input[i] - mean[i]) / std[i];   // Normalisation
          int quant = (int)round(norm / input_scale) + input_zero_point;
          if (quant > 127) quant = 127;
          if (quant < -128) quant = -128;
          in_data[i] = (int8_t)quant;
      }/*
	  for (int i = 0; i < 8; i++) {
	      in_data[i] = (int8_t)((sample_input[i] - mean[i]) / (std[i] * scale) + zero_point);
	  }*/


      // Timestamp avant l’inférence
      timestamp = htim6.Instance->CNT;

      // Exécution du modèle
      nbatch = ai_eightchannel_run(ai_model, ai_input, ai_output);
      if (nbatch != 1) {
          buf_len = sprintf(buf, "Inference failed\r\n");
          HAL_UART_Transmit(&huart2, (uint8_t*)buf, buf_len, 100);
          Error_Handler();
      }


      // 🧮 Calcul simple du softmax de façon stable (on peut aussi seulement utiliser argmax)
      // Pour éviter overflow et pour un affichage simple, on calcule argmax et on calcule probabilités relatives scaled.
      // Déquantification output int8 -> float
           float output_scale = 0.00390625f;
           int output_zero_point = -128;
           float output_float[AI_EIGHTCHANNEL_OUT_1_SIZE];

           for (int i = 0; i < AI_EIGHTCHANNEL_OUT_1_SIZE; i++) {
               output_float[i] = ((float)out_data[i] - output_zero_point) * output_scale;
           }

           // Trouver la classe prédite
           int predicted_class = 0;
           float max_val = output_float[0];
           for (int i = 1; i < AI_EIGHTCHANNEL_OUT_1_SIZE; i++) {
               if (output_float[i] > max_val) {
                   max_val = output_float[i];
                   predicted_class = i;
               }
           }

           sprintf(buf, "Predicted class: %d | duration: %lu us\r\n", predicted_class,
                   (unsigned long)(htim6.Instance->CNT - timestamp));
           HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 100);

           HAL_Delay(1000);
  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  RCC_OscInitStruct.PLL.PLLN = 168;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 167;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
