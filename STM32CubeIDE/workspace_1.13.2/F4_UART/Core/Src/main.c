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

uint8_t RxData_cell_temp[3][8] = {
    {0x00, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30},  // Frame 0
    {0x01, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37},  // Frame 1
    {0x02, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E}   // Frame 2
};


uint8_t TxData_cell_balance[8] = {0x03, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t TxData_failuer[8] = {0x03, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static char RxBuffer[50];
static char commandBuffer[50];

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    printf("UART RX Callback entered!\n");
    if (huart->Instance == USART2) {
    //Increased buffer size for potential longer commands.


    	    /* USER CODE BEGIN 3 */
    		  if (strcmp(RxBuffer, "soc") == 0) {
    		      uint16_t cumulative_voltage = (TxData_SOC[0] << 8) | TxData_SOC[1];
    		      float cumulative_voltage_real = cumulative_voltage * 0.1;

    		      uint16_t gather_voltage = (TxData_SOC[2] << 8) | TxData_SOC[3];
    		      float gather_voltage_real = gather_voltage * 0.1;

    		      uint16_t current_raw = (TxData_SOC[4] << 8) | TxData_SOC[5];
    		      float current_real = (current_raw - 30000) * 0.1;

    		      uint16_t soc = (TxData_SOC[6] << 8) | TxData_SOC[7];
    		      float soc_real = soc * 0.1;

    		      char data_string[100];
    		      sprintf(data_string,
    		              "Cumulative Voltage: %d.%d V, Gather Voltage: %d.%d V, Current: %d.%d A, SOC: %d.%d%%\n ",
    		              (int)cumulative_voltage_real, (int)(cumulative_voltage_real * 10) % 10,
    		              (int)gather_voltage_real, (int)(gather_voltage_real * 10) % 10,
    		              (int)current_real, (int)(current_real * 10) % 10,
    		              (int)soc_real, (int)(soc_real * 10) % 10);


    		      HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    		      for (int i = 0; i < sizeof(RxBuffer); i++) {
    		          RxBuffer[i] = 0;
    		      }

    		  }
    		  else if (strcmp(RxBuffer, "volt") == 0)
    		  {
    			  	  	  	  	  uint16_t max_cell_voltage = (TxData_volt[0] << 8) | TxData_volt[1];
    						      uint8_t max_voltage_cell_no = TxData_volt[2];
    						      uint16_t min_cell_voltage = (TxData_volt[3] << 8) | TxData_volt[4];
    						      uint8_t min_voltage_cell_no = TxData_volt[5];
    						      char data_string[100];
    						      sprintf(data_string,
    						              "Max Cell Voltage: %d.%d V, Max Voltage Cell No: %d, Min Cell Voltage: %d.%d V, Min Voltage Cell No: %d\n",
    						              max_cell_voltage / 10, (max_cell_voltage % 10),
    						              max_voltage_cell_no,
    						              min_cell_voltage / 10, (min_cell_voltage % 10),
    						              min_voltage_cell_no);

    						      	      	  HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }
    		  else if (strcmp(RxBuffer, "temp") == 0)
    		  {

    			  			     int8_t max_temp_raw = TxData_temp[0];
    			  			     float max_temperature = max_temp_raw - 40.0;
    			  			     uint8_t max_temp_cell_no = TxData_temp[1];
    			  			     int8_t min_temp_raw = TxData_temp[2];
    			  			     float min_temperature = min_temp_raw - 40.0;
    			  			     uint8_t min_temp_cell_no = TxData_temp[3];
    			  			   char data_string[100];
    			  			    sprintf(data_string,
    			  			            "Max Temperature: %d °C, Max Temp Cell No: %d, Min Temperature: %d °C, Min Temp Cell No: %d\n",
    			  			            max_temperature, max_temp_cell_no, min_temperature, min_temp_cell_no);
    			  			    HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }
    		  else if (strcmp(RxBuffer, "mos") == 0)
    		  {
    			    uint8_t state = TxData_mos[0];
    			    uint8_t charge_mos_state = TxData_mos[1];
    			    uint8_t discharge_mos_state = TxData_mos[2];
    			    uint8_t bms_life = TxData_mos[3];
    			    uint32_t remaining_capacity = (TxData_mos[4] << 24) | (TxData_mos[5] << 16) | (TxData_mos[6] << 8) | TxData_mos[7];
    			    char data_string[100];
    			    sprintf(data_string,
    			            "State: %d, Charge MOS State: %d, Discharge MOS State: %d, BMS Life: %d cycles, Remaining Capacity: %lu mAh\n",
    			            state, charge_mos_state, discharge_mos_state, bms_life, remaining_capacity);
    			    HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }
    		  else if (strcmp(RxBuffer, "status") == 0)
    		  {
    			     uint8_t battery_string_count = TxData_status[0];
    			     uint8_t temperature_count = TxData_status[1];
    			     uint8_t charger_status = TxData_status[2];
    			     uint8_t load_status = TxData_status[3];
    			     uint8_t di_do_state = TxData_status[4];
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
    			      	  	  HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);

    		  }else if (strcmp(RxBuffer, "cell_volt") == 0)
    		  {
    			    uint16_t cell_voltages[48] = {0};
    			    int cell_index = 0;
    			    for (int frame = 0; frame < 16; frame++) {
    			        for (int i = 0; i < 3; i++) {
    			            uint8_t high_byte = TxData_cell_volt[frame][1 + (i * 2)];
    			            uint8_t low_byte = TxData_cell_volt[frame][2 + (i * 2)];
    			            cell_voltages[cell_index] = (high_byte << 8) | low_byte;
    			            cell_index++;
    			        }
    			    }
    			    char data_string[400];
    			    for (int i = 0; i < 48; i++) {
    			     sprintf(data_string, "Cell %d Voltage: %d mV\n", i + 1, cell_voltages[i]);
    			     HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    			    }

    		  }
    		  else if (strcmp(RxBuffer, "cell_temp") == 0)
    		  {

    			   int cell_temperatures[21];
    			    int temperature_index = 0;

    			    // Extraction des températures
    			    for (int frame = 0; frame < 3; frame++) {
    			        for (int i = 1; i <= 7; i++) {
    			            int raw_temp = RxData_cell_temp[frame][i];
    			            cell_temperatures[temperature_index] = raw_temp - 40;  // Conversion en °C
    			            temperature_index++;
    			        }

    			    }
    			    char data_string[400];
    			  		    for (int i = 0; i < 21; i++) {
    			  		     sprintf(data_string, "Cell %d Temperature: %d °C\n", i + 1, cell_temperatures[i]);
    			  		     HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    			  		    }

    		  }
    		  else if (strcmp(RxBuffer, "cell_balance") == 0)
    		  {	uint8_t cell_state [48]={0};
    			  for (int i = 1; i <= 48; i++) {
    			    int byte_index = (i - 1) / 8;               // Trouve l'octet contenant le bit
    			    int bit_index = (i - 1) % 8;                // Trouve la position du bit dans l'octet
    			    cell_state[i]=(TxData_cell_balance[byte_index] >> bit_index) & 0x01;

    		  }
    			  char data_string[400];
    			  		  		    for (int i = 0; i < 48; i++) {
    			  		  		     sprintf(data_string,"Cell %d Balance State: %d\n", i, cell_state[i]);
    			  		  		     HAL_UART_Transmit(&huart2, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
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
    			      if (TxData_failuer[0] & 0x01) { strcat(error_message, "Cell_H1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[0] & 0x02) { strcat(error_message, "Cell_H2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[0] & 0x04) { strcat(error_message, "Cell_L1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[0] & 0x08) { strcat(error_message, "Cell_L2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[0] & 0x10) { strcat(error_message, "Sum_H1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[0] & 0x20) { strcat(error_message, "Sum_H2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[0] & 0x40) { strcat(error_message, "Sum_L1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[0] & 0x80) { strcat(error_message, "Sum_L2 Error; "); error_detected = 1; }

    			      // Byte 1
    			      if (TxData_failuer[1] & 0x01) { strcat(error_message, "C_temp_H1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[1] & 0x02) { strcat(error_message, "C_temp_H2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[1] & 0x04) { strcat(error_message, "C_temp_L1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[1] & 0x08) { strcat(error_message, "C_temp_L2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[1] & 0x10) { strcat(error_message, "DC_temp_H1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[1] & 0x20) { strcat(error_message, "DC_temp_H2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[1] & 0x40) { strcat(error_message, "DC_temp_L1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[1] & 0x80) { strcat(error_message, "DC_temp_L2 Error; "); error_detected = 1; }

    			      // Byte 2
    			      if (TxData_failuer[2] & 0x01) { strcat(error_message, "C_OC_1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[2] & 0x02) { strcat(error_message, "C_OC_2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[2] & 0x04) { strcat(error_message, "DC_OC_1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[2] & 0x08) { strcat(error_message, "DC_OC_2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[2] & 0x10) { strcat(error_message, "SOC_H1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[2] & 0x20) { strcat(error_message, "SOC_H2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[2] & 0x40) { strcat(error_message, "SOC_L1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[2] & 0x80) { strcat(error_message, "SOC_L2 Error; "); error_detected = 1; }

    			      // Byte 3
    			      if (TxData_failuer[3] & 0x01) { strcat(error_message, "DI_VOLT_1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[3] & 0x02) { strcat(error_message, "DI_VOLT_2 Error; "); error_detected = 1; }
    			      if (TxData_failuer[3] & 0x04) { strcat(error_message, "DDI_TEMP_1 Error; "); error_detected = 1; }
    			      if (TxData_failuer[3] & 0x08) { strcat(error_message, "DI_TEMP_2 Error; "); error_detected = 1; }

    			      // Byte 4
    			      if (TxData_failuer[4] & 0x01) { strcat(error_message, "C_mos_TEMP_H Error; "); error_detected = 1; }
    			      if (TxData_failuer[4] & 0x02) { strcat(error_message, "DC_mos_TEMP_H Error; "); error_detected = 1; }
    			      if (TxData_failuer[4] & 0x04) { strcat(error_message, "C_mos_TEMP_SEN Error; "); error_detected = 1; }
    			      if (TxData_failuer[4] & 0x08) { strcat(error_message, "DC_mos_TEMP_SEN Error; "); error_detected = 1; }
    			      if (TxData_failuer[4] & 0x10) { strcat(error_message, "C_mos_ADH Error; "); error_detected = 1; }
    			      if (TxData_failuer[4] & 0x20) { strcat(error_message, "DC_mos_ADH Error; "); error_detected = 1; }
    			      if (TxData_failuer[4] & 0x40) { strcat(error_message, "C_mos_OP_C Error; "); error_detected = 1; }
    			      if (TxData_failuer[4] & 0x80) { strcat(error_message, "DC_mos_OP_C Error; "); error_detected = 1; }

    			      // Byte 5
    			      if (TxData_failuer[5] & 0x01) { strcat(error_message, "AFE_COLL Error; "); error_detected = 1; }
    			      if (TxData_failuer[5] & 0x02) { strcat(error_message, "VOLT_COLL Error; "); error_detected = 1; }
    			      if (TxData_failuer[5] & 0x04) { strcat(error_message, "CELL_TEMP_SEN Error; "); error_detected = 1; }
    			      if (TxData_failuer[5] & 0x08) { strcat(error_message, "EEPROM Error; "); error_detected = 1; }
    			      if (TxData_failuer[5] & 0x10) { strcat(error_message, "RTC Error; "); error_detected = 1; }
    			      if (TxData_failuer[5] & 0x20) { strcat(error_message, "PRECH Error; "); error_detected = 1; }
    			      if (TxData_failuer[5] & 0x40) { strcat(error_message, "COMM Error; "); error_detected = 1; }
    			      if (TxData_failuer[5] & 0x80) { strcat(error_message, "INTER_COMM Error; "); error_detected = 1; }

    			      // Byte 6
    			      if (TxData_failuer[6] & 0x01) { strcat(error_message, "CU_MOD Error; "); error_detected = 1; }
    			      if (TxData_failuer[6] & 0x02) { strcat(error_message, "SUL_VOLT_DET Error; "); error_detected = 1; }
    			      if (TxData_failuer[6] & 0x04) { strcat(error_message, "SHORT_CIR Error; "); error_detected = 1; }
    			      if (TxData_failuer[6] & 0x08) { strcat(error_message, "LOW_VOLT Error; "); error_detected = 1; }

    			      // Si une erreur a été détectée, envoyer le message
    			      if (error_detected) {
    			    	  HAL_UART_Transmit(&huart2, (uint8_t*)error_message, strlen(error_message), 100);
    			      }
    			      else {
    			    	  HAL_UART_Transmit(&huart2, "No Errors Detected.", 100, HAL_MAX_DELAY);
    			      }





    		  }
    		  HAL_UART_Receive(&huart2, RxBuffer, sizeof(RxBuffer),100);

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
