#include "main.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

//TC47 Temperature sensor address
#define I2C_ADDRESS 0x48 //0b1001000

//Function prototypes
void GPIOInit();
void UARTInit();

void I2CInit();
<<<<<<< HEAD
void I2C1_EV_IRQHandler(I2C_HandleTypeDef*);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef*);
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef*);

void TimerITInit();
void TIM1_UP_TIM10_IRQHandler();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*);
=======
void I2C1_EV_IRQHandler(I2C_HandleTypeDef* hi2c);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c);

void TimerITInit();
void TIM1_UP_TIM10_IRQHandler();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim);
>>>>>>> fe77baac943656084e7338b8175f01e4335a03e2

//Global variables
GPIO_InitTypeDef GPIO_I2C_SDA_SCL_Config;
I2C_HandleTypeDef I2cHandle;
UART_HandleTypeDef uart_handle;
TIM_HandleTypeDef TimHandle;

uint8_t cmd = 0;
uint8_t buf;

int main(void) {
	//Hardware config
	MPU_Config();
	CPU_CACHE_Enable();
	HAL_Init();
	SystemClock_Config();

	BSP_LED_Init(LED_GREEN);

	GPIOInit();
	I2CInit();
	UARTInit();

	printf("--------------------------------\n"
		   "TC74 - I2C Temperature Measuring\n"
		   "--------------------------------\n");

	TimerITInit();

	while (1) {
		//Timer IT -> I2C Transmit IT -> I2C Receive IT -> print
	}

}
//GPIO Pin settings-----------------------------------------------
void GPIOInit() {
	//D14 (B9) & D15 (B8)

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_I2C_SDA_SCL_Config.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_I2C_SDA_SCL_Config.Mode = GPIO_MODE_AF_OD; //Open-drain for I2C
	GPIO_I2C_SDA_SCL_Config.Pull = GPIO_PULLUP;
	GPIO_I2C_SDA_SCL_Config.Speed = GPIO_SPEED_FAST;
	GPIO_I2C_SDA_SCL_Config.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB, &GPIO_I2C_SDA_SCL_Config);
}
//I2C settings---------------------------------------------------
void I2CInit() {
	__HAL_RCC_I2C1_CLK_ENABLE();

	I2cHandle.Instance             = I2C1;
	I2cHandle.Init.Timing          = 0x40912732;
	I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;

	HAL_I2C_Init(&I2cHandle);

	HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0x01, 0x00);
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
}

void I2C1_EV_IRQHandler(I2C_HandleTypeDef *hi2c) {
	HAL_I2C_EV_IRQHandler(&I2cHandle);
}

<<<<<<< HEAD
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	HAL_I2C_Master_Receive_IT(&I2cHandle, I2C_ADDRESS << 1, (uint8_t*) &buf, 1);
}
=======
//void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
//	HAL_I2C_Master_Receive_IT(&I2cHandle, I2C_ADDRESS << 1, (uint8_t*) &buf, 1);
//}
>>>>>>> fe77baac943656084e7338b8175f01e4335a03e2

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	printf("Temperature: %d�C\n", buf);
}

//Timer interrupt-------------------------------------------------------
void TimerITInit() {

	__HAL_RCC_TIM1_CLK_ENABLE();

	TimHandle.Instance               = TIM1;
	TimHandle.Init.Period            = 8000; //Period time = 8000 / 4000Hz = 2s
	TimHandle.Init.Prescaler         = 54000; //Using 1/54000 speed of 216MHz (= 4 kHz)
	TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;

	HAL_TIM_Base_Init(&TimHandle);
	HAL_TIM_Base_Start_IT(&TimHandle);

	HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0x0F, 0x00);
	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}

void TIM1_UP_TIM10_IRQHandler() {
	HAL_TIM_IRQHandler(&TimHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
<<<<<<< HEAD
	HAL_I2C_Master_Transmit_IT(&I2cHandle, I2C_ADDRESS << 1, (uint8_t*) &cmd, 1);
=======
	//HAL_I2C_Master_Transmit_IT(&I2cHandle, I2C_ADDRESS << 1, (uint8_t*) &cmd, 1);
	HAL_I2C_Master_Receive_IT(&I2cHandle, I2C_ADDRESS << 1, (uint8_t*) &buf, 1);
>>>>>>> fe77baac943656084e7338b8175f01e4335a03e2
}
//UART----------------------------------------------------------
void UARTInit() {
	uart_handle.Init.BaudRate = 115200;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;

	BSP_COM_Init(COM1, &uart_handle);
}

PUTCHAR_PROTOTYPE {
	HAL_UART_Transmit(&uart_handle, (uint8_t *) &ch, 1, 0xFFFF);
	return ch;
}
