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


uint8_t select =0;
uint8_t count1 =0;
uint8_t count2 =0;

uint8_t RxData1[3][8];
uint8_t RxData2[16][8];
uint8_t RxBuffer[8];
uint8_t RxData[8];
uint8_t TxData[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
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

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_USART1_UART_Init(void);
void sendrequest(uint8_t *RxBuffer, CAN_HandleTypeDef *hcan);
void SplitAndSendData(UART_HandleTypeDef *huart);
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  TxHeader.DLC = 8;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.RTR = CAN_RTR_REMOTE;

  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
  sFilterConfig.FilterIdHigh = 0x90<< 5;
  sFilterConfig.FilterIdLow =  0x90 << 5; ;
  sFilterConfig.FilterMaskIdHigh =0xF0<< 5;
  sFilterConfig.FilterMaskIdLow = 0xF0<< 5 ;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;

  HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);

  HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING );

  HAL_CAN_Start(&hcan1);

  HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) ;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // send requete
	   sendrequest(RxBuffer,&hcan1);
	   SplitAndSendData(&huart1);

  /* USER CODE END 3 */
}

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
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  hcan1.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
void sendrequest(uint8_t *RxBuffer, CAN_HandleTypeDef *hcan) {
    if (strcmp((char *)RxBuffer, "soc") == 0) {
        TxHeader.StdId = IDR_soc;
    } else if (strcmp((char *)RxBuffer, "volt") == 0) {
        TxHeader.StdId = IDR_volt;
    } else if (strcmp((char *)RxBuffer, "temp") == 0) {
        TxHeader.StdId = IDR_temp;
    } else if (strcmp((char *)RxBuffer, "mos") == 0) {
        TxHeader.StdId = IDR_mos;
    } else if (strcmp((char *)RxBuffer, "cell_volt") == 0) {
        TxHeader.StdId = IDR_cell_volt;
    } else if (strcmp((char *)RxBuffer, "status") == 0) {
        TxHeader.StdId = IDR_status;
    } else if (strcmp((char *)RxBuffer, "cell_temp") == 0) {
        TxHeader.StdId = IDR_cell_temp;
    } else if (strcmp((char *)RxBuffer, "cell_balance") == 0) {
        TxHeader.StdId = IDR_cell_balance;
    } else if (strcmp((char *)RxBuffer, "failure") == 0) {
        TxHeader.StdId = IDR_failure;
    } else {
        return;
    }

    HAL_CAN_AddTxMessage(hcan, &TxHeader, TxData, &TxMailbox);


    HAL_Delay(500);

    // Clear RxBuffer
    memset(RxBuffer, 0x00, sizeof(RxBuffer));
}


void SplitAndSendData(UART_HandleTypeDef *huart) {

    		  if (select ==1) {
    		      uint16_t cumulative_voltage = (RxData[0] << 8) | RxData[1];
    		      float cumulative_voltage_real = cumulative_voltage * 0.1;

    		      uint16_t gather_voltage = (RxData[2] << 8) | RxData[3];
    		      float gather_voltage_real = gather_voltage * 0.1;

    		      uint16_t current_raw = (RxData[4] << 8) | RxData[5];
    		      float current_real = (current_raw - 30000) * 0.1;

    		      uint16_t soc = (RxData[6] << 8) | RxData[7];
    		      float soc_real = soc * 0.1;

    		      char data_string[100];
    		      sprintf(data_string,
    		              "Cumulative Voltage: %d.%d V, Gather Voltage: %d.%d V, Current: %d.%d A, SOC: %d.%d%%\n ",
    		              (int)cumulative_voltage_real, (int)(cumulative_voltage_real * 10) % 10,
    		              (int)gather_voltage_real, (int)(gather_voltage_real * 10) % 10,
    		              (int)current_real, (int)(current_real * 10) % 10,
    		              (int)soc_real, (int)(soc_real * 10) % 10);


    		      HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    		      for (int i = 0; i < sizeof(RxBuffer); i++) {
    		          RxBuffer[i] = 0;
    		      }

    		  }
    		  else if (select == 2)
    		  {
    			  	  	  	  	  uint16_t max_cell_voltage = (RxData[0] << 8) | RxData[1];
    						      uint8_t max_voltage_cell_no = RxData[2];
    						      uint16_t min_cell_voltage = (RxData[3] << 8) | RxData[4];
    						      uint8_t min_voltage_cell_no = RxData[5];
    						      char data_string[100];
    						      sprintf(data_string,
    						              "Max Cell Voltage: %d.%d V, Max Voltage Cell No: %d, Min Cell Voltage: %d.%d V, Min Voltage Cell No: %d\n",
    						              max_cell_voltage / 10, (max_cell_voltage % 10),
    						              max_voltage_cell_no,
    						              min_cell_voltage / 10, (min_cell_voltage % 10),
    						              min_voltage_cell_no);

    						      	      	  HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }
    		  else if (select == 3)
    		  {

    			  			     int8_t max_temp_raw = RxData[0];
    			  			     float max_temperature = max_temp_raw - 40.0;
    			  			     uint8_t max_temp_cell_no = RxData[1];
    			  			     int8_t min_temp_raw = RxData[2];
    			  			     float min_temperature = min_temp_raw - 40.0;
    			  			     uint8_t min_temp_cell_no = RxData[3];
    			  			   char data_string[100];
    			  			    sprintf(data_string,
    			  			            "Max Temperature: %d °C, Max Temp Cell No: %d, Min Temperature: %d °C, Min Temp Cell No: %d\n",
    			  			            max_temperature, max_temp_cell_no, min_temperature, min_temp_cell_no);
    			  			    HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }
    		  else if (select == 4)
    		  {
    			    uint8_t state = RxData[0];
    			    uint8_t charge_mos_state = RxData[1];
    			    uint8_t discharge_mos_state = RxData[2];
    			    uint8_t bms_life = RxData[3];
    			    uint32_t remaining_capacity = (RxData[4] << 24) | (RxData[5] << 16) | (RxData[6] << 8) | RxData[7];
    			    char data_string[100];
    			    sprintf(data_string,
    			            "State: %d, Charge MOS State: %d, Discharge MOS State: %d, BMS Life: %d cycles, Remaining Capacity: %lu mAh\n",
    			            state, charge_mos_state, discharge_mos_state, bms_life, remaining_capacity);
    			    HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }
    		  else if (select == 6)
    		  {
    			     uint8_t battery_string_count = RxData[0];
    			     uint8_t temperature_count = RxData[1];
    			     uint8_t charger_status = RxData[2];
    			     uint8_t load_status = RxData[3];
    			     uint8_t di_do_state = RxData[4];
    			     uint8_t di1_state = (di_do_state >> 0) & 0x01; // Bit 0
    			     uint8_t di2_state = (di_do_state >> 1) & 0x01; // Bit 1
    			     uint8_t di3_state = (di_do_state >> 2) & 0x01; // Bit 2
    			     uint8_t di4_state = (di_do_state >> 3) & 0x01; // Bit 3
    			     uint8_t do1_state = (di_do_state >> 4) & 0x01; // Bit 4
    			     uint8_t do2_state = (di_do_state >> 5) & 0x01; // Bit 5
    			     uint8_t do3_state = (di_do_state >> 6) & 0x01; // Bit 6
    			     uint8_t do4_state = (di_do_state >> 7) & 0x01; // Bit 7
    			     char data_string[200];
    			      sprintf(data_string,
    			              "Battery String Count: %d\n"
    			              "Temperature Count: %d\n"
    			              "Charger Status: %d\n"
    			              "Load Status: %d\n"
    			              "DI1 State: %d, DI2 State: %d, DI3 State: %d, DI4 State: %d\n"
    			              "DO1 State: %d, DO2 State: %d, DO3 State: %d, DO4 State: %d\n",
    			              battery_string_count, temperature_count, charger_status, load_status,
    			              di1_state, di2_state, di3_state, di4_state,
    			              do1_state, do2_state, do3_state, do4_state);
    			      	  	  HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }else if (select == 5)
    		  {
    			    uint16_t cell_voltages[48] = {0};
    			    int cell_index = 0;
    			    for (int frame = 0; frame < 16; frame++) {
    			        for (int i = 0; i < 3; i++) {
    			            uint8_t high_byte = RxData1[frame][1 + (i * 2)];
    			            uint8_t low_byte = RxData1[frame][2 + (i * 2)];
    			            cell_voltages[cell_index] = (high_byte << 8) | low_byte;
    			            cell_index++;
    			        }
    			    }
    			    char data_string[400];
    			    for (int i = 0; i < 48; i++) {
    			     sprintf(data_string, "Cell %d Voltage: %d mV\n", i + 1, cell_voltages[i]);
    			     HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    			    }

    		  }
    		  else if (select == 7)
    		  {

    			   int cell_temperatures[21];
    			    int temperature_index = 0;

    			    // Extraction des températures
    			    for (int frame = 0; frame < 3; frame++) {
    			        for (int i = 1; i <= 7; i++) {
    			            int raw_temp = RxData2[frame][i];
    			            cell_temperatures[temperature_index] = raw_temp - 40;  // Conversion en °C
    			            temperature_index++;
    			        }

    			    }
    			    char data_string[400];
    			  		    for (int i = 0; i < 21; i++) {
    			  		     sprintf(data_string, "Cell %d Temperature: %d °C\n", i + 1, cell_temperatures[i]);
    			  		     HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    			  		    }

    		  }
    		  else if (select== 8)
    		  {	uint8_t cell_state [48]={0};
    			  for (int i = 1; i <= 48; i++) {
    			    int byte_index = (i - 1) / 8;               // Trouve l'octet contenant le bit
    			    int bit_index = (i - 1) % 8;                // Trouve la position du bit dans l'octet
    			    cell_state[i]=(RxData[byte_index] >> bit_index) & 0x01;

    		  }
    			  char data_string[400];
    			  		  		    for (int i = 0; i < 48; i++) {
    			  		  		     sprintf(data_string,"Cell %d Balance State: %d\n", i, cell_state[i]);
    			  		  		     HAL_UART_Transmit(&huart, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    			  		  		    }
    		  }
    		  else if (strcmp(RxBuffer, "failuer") == 0)
    		  {
    			  char error_message[256];  // Buffer pour le message d'erreur
    			      int error_detected = 0;   // Indicateur d'erreur

    			      // On commence par vider le message d'erreur
    			      memset(error_message, 0, sizeof(error_message));

    			      // Vérification des bits dans chaque octet
    			      // Byte 0
    			      if (RxData[0] & 0x01) { strcat(error_message, "Cell_H1 Error; "); error_detected = 1; }
    			      if (RxData[0] & 0x02) { strcat(error_message, "Cell_H2 Error; "); error_detected = 1; }
    			      if (RxData[0] & 0x04) { strcat(error_message, "Cell_L1 Error; "); error_detected = 1; }
    			      if (RxData[0] & 0x08) { strcat(error_message, "Cell_L2 Error; "); error_detected = 1; }
    			      if (RxData[0] & 0x10) { strcat(error_message, "Sum_H1 Error; "); error_detected = 1; }
    			      if (RxData[0] & 0x20) { strcat(error_message, "Sum_H2 Error; "); error_detected = 1; }
    			      if (RxData[0] & 0x40) { strcat(error_message, "Sum_L1 Error; "); error_detected = 1; }
    			      if (RxData[0] & 0x80) { strcat(error_message, "Sum_L2 Error; "); error_detected = 1; }

    			      // Byte 1
    			      if (RxData[1] & 0x01) { strcat(error_message, "C_temp_H1 Error; "); error_detected = 1; }
    			      if (RxData[1] & 0x02) { strcat(error_message, "C_temp_H2 Error; "); error_detected = 1; }
    			      if (RxData[1] & 0x04) { strcat(error_message, "C_temp_L1 Error; "); error_detected = 1; }
    			      if (RxData[1] & 0x08) { strcat(error_message, "C_temp_L2 Error; "); error_detected = 1; }
    			      if (RxData[1] & 0x10) { strcat(error_message, "DC_temp_H1 Error; "); error_detected = 1; }
    			      if (RxData[1] & 0x20) { strcat(error_message, "DC_temp_H2 Error; "); error_detected = 1; }
    			      if (RxData[1] & 0x40) { strcat(error_message, "DC_temp_L1 Error; "); error_detected = 1; }
    			      if (RxData[1] & 0x80) { strcat(error_message, "DC_temp_L2 Error; "); error_detected = 1; }

    			      // Byte 2
    			      if (RxData[2] & 0x01) { strcat(error_message, "C_OC_1 Error; "); error_detected = 1; }
    			      if (RxData[2] & 0x02) { strcat(error_message, "C_OC_2 Error; "); error_detected = 1; }
    			      if (RxData[2] & 0x04) { strcat(error_message, "DC_OC_1 Error; "); error_detected = 1; }
    			      if (RxData[2] & 0x08) { strcat(error_message, "DC_OC_2 Error; "); error_detected = 1; }
    			      if (RxData[2] & 0x10) { strcat(error_message, "SOC_H1 Error; "); error_detected = 1; }
    			      if (RxData[2] & 0x20) { strcat(error_message, "SOC_H2 Error; "); error_detected = 1; }
    			      if (RxData[2] & 0x40) { strcat(error_message, "SOC_L1 Error; "); error_detected = 1; }
    			      if (RxData[2] & 0x80) { strcat(error_message, "SOC_L2 Error; "); error_detected = 1; }

    			      // Byte 3
    			      if (RxData[3] & 0x01) { strcat(error_message, "DI_VOLT_1 Error; "); error_detected = 1; }
    			      if (RxData[3] & 0x02) { strcat(error_message, "DI_VOLT_2 Error; "); error_detected = 1; }
    			      if (RxData[3] & 0x04) { strcat(error_message, "DDI_TEMP_1 Error; "); error_detected = 1; }
    			      if (RxData[3] & 0x08) { strcat(error_message, "DI_TEMP_2 Error; "); error_detected = 1; }

    			      // Byte 4
    			      if (RxData[4] & 0x01) { strcat(error_message, "C_mos_TEMP_H Error; "); error_detected = 1; }
    			      if (RxData[4] & 0x02) { strcat(error_message, "DC_mos_TEMP_H Error; "); error_detected = 1; }
    			      if (RxData[4] & 0x04) { strcat(error_message, "C_mos_TEMP_SEN Error; "); error_detected = 1; }
    			      if (RxData[4] & 0x08) { strcat(error_message, "DC_mos_TEMP_SEN Error; "); error_detected = 1; }
    			      if (RxData[4] & 0x10) { strcat(error_message, "C_mos_ADH Error; "); error_detected = 1; }
    			      if (RxData[4] & 0x20) { strcat(error_message, "DC_mos_ADH Error; "); error_detected = 1; }
    			      if (RxData[4] & 0x40) { strcat(error_message, "C_mos_OP_C Error; "); error_detected = 1; }
    			      if (RxData[4] & 0x80) { strcat(error_message, "DC_mos_OP_C Error; "); error_detected = 1; }

    			      // Byte 5
    			      if (RxData[5] & 0x01) { strcat(error_message, "AFE_COLL Error; "); error_detected = 1; }
    			      if (RxData[5] & 0x02) { strcat(error_message, "VOLT_COLL Error; "); error_detected = 1; }
    			      if (RxData[5] & 0x04) { strcat(error_message, "CELL_TEMP_SEN Error; "); error_detected = 1; }
    			      if (RxData[5] & 0x08) { strcat(error_message, "EEPROM Error; "); error_detected = 1; }
    			      if (RxData[5] & 0x10) { strcat(error_message, "RTC Error; "); error_detected = 1; }
    			      if (RxData[5] & 0x20) { strcat(error_message, "PRECH Error; "); error_detected = 1; }
    			      if (RxData[5] & 0x40) { strcat(error_message, "COMM Error; "); error_detected = 1; }
    			      if (RxData[5] & 0x80) { strcat(error_message, "INTER_COMM Error; "); error_detected = 1; }

    			      // Byte 6
    			      if (RxData[6] & 0x01) { strcat(error_message, "CU_MOD Error; "); error_detected = 1; }
    			      if (RxData[6] & 0x02) { strcat(error_message, "SUL_VOLT_DET Error; "); error_detected = 1; }
    			      if (RxData[6] & 0x04) { strcat(error_message, "SHORT_CIR Error; "); error_detected = 1; }
    			      if (RxData[6] & 0x08) { strcat(error_message, "LOW_VOLT Error; "); error_detected = 1; }

    			      // Si une erreur a été détectée, envoyer le message
    			      if (error_detected) {
    			    	  HAL_UART_Transmit(&huart, (uint8_t*)error_message, strlen(error_message), 100);
    			      }
    			      else {
    			    	  HAL_UART_Transmit(&huart, "No Errors Detected.", 100, HAL_MAX_DELAY);
    			      }





    		  }


    	  }




void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
    	 if (RxHeader.StdId == ID_soc) {
    						select = 1;
    					}
    	        else if (RxHeader.StdId == ID_volt) {
    						select = 2 ;
    					}
    	        else if (RxHeader.StdId == ID_temp) {
    	                	select = 3 ;
    	                }
    	        else if (RxHeader.StdId == ID_mos) {
    	                	select = 4 ;
    	                }
    	        else if (RxHeader.StdId == ID_cell_volt) {

    	                	select = 5 ;
    	                	memcpy(RxData1[count1], RxData, RxHeader.DLC);
    	                	            count1++;
    	                	            if (count1 == 15) {
    	                	                count1 = 0; // Wrap around
    	                	            }

    	                }
    	        else if (RxHeader.StdId == ID_status) {
    	                	select = 6 ;
    	                }
    	        else if (RxHeader.StdId == ID_cell_temp) {
    	                	select = 7 ;
    	                	memcpy(RxData2[count2], RxData, RxHeader.DLC);
    	                	            count2++;
    	                	            if (count2 == 2) {
    	                	                count2 = 0; // Wrap around
    	                	            }

    	                }
    	        else if (RxHeader.StdId == ID_cell_balance) {
    	                	select = 8 ;
    	                }
    	        else if (RxHeader.StdId == ID_failure) {
    	                	select = 9 ;
    	                }
    	        else {
    	        	select = 0 ;
    	        }



    }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        HAL_UART_Receive_IT(&huart1, RxBuffer, sizeof(RxBuffer));
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
