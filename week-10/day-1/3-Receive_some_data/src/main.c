#include "main.h"
#include "string.h"

void UARTSettings(UART_HandleTypeDef);
void UARTPinSettings(UART_HandleTypeDef);

UART_HandleTypeDef UartHandle;
char ch;

int main(void) {
	//Hardware config
	MPU_Config();
	CPU_CACHE_Enable();
	HAL_Init();
	SystemClock_Config();

	BSP_LED_Init(LED_GREEN);
	BSP_LED_On(LED_GREEN);

	UARTPinSettings(UartHandle);
	UARTSettings(UartHandle);

	while (1) {
		HAL_UART_Receive(&UartHandle, (uint8_t*) &ch, 1, 0xFFFF);

		HAL_UART_Transmit(&UartHandle, (uint8_t*) &ch, 1, 0xFFFF);
	}

}
void UARTSettings(UART_HandleTypeDef huart) {
	UartHandle.Instance         = USART1;
	UartHandle.Init.BaudRate    = 115200;
	UartHandle.Init.WordLength  = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits    = UART_STOPBITS_1;
	UartHandle.Init.Parity      = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl   = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode        = UART_MODE_TX_RX;

	HAL_UART_Init(&UartHandle);
}

void UARTPinSettings(UART_HandleTypeDef huart) {
	GPIO_InitTypeDef gpio_init_structure;

	  /* Enable GPIO clock */
	  __HAL_RCC_GPIOA_CLK_ENABLE(); //DISCOVERY_COMx_TX_GPIO_CLK_ENABLE(COM);
	  __HAL_RCC_GPIOB_CLK_ENABLE(); //DISCOVERY_COMx_RX_GPIO_CLK_ENABLE(COM);

	  /* Enable USART clock */
	  __HAL_RCC_USART1_CLK_ENABLE(); //DISCOVERY_COMx_CLK_ENABLE(COM);

	  /* Configure USART Tx as alternate function */
	  gpio_init_structure.Pin = GPIO_PIN_9; //DISCOVERY_COM1_TX_PIN;
	  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	  gpio_init_structure.Speed = GPIO_SPEED_FAST;
	  gpio_init_structure.Pull = GPIO_PULLUP;
	  gpio_init_structure.Alternate = GPIO_AF7_USART1; //DISCOVERY_COM1_TX_AF;
	  HAL_GPIO_Init(GPIOA, &gpio_init_structure);

	  /* Configure USART Rx as alternate function */
	  gpio_init_structure.Pin = GPIO_PIN_7; //DISCOVERY_COM1_RX_PIN;
	  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	  gpio_init_structure.Alternate = GPIO_AF7_USART1; //DISCOVERY_COM1_RX_AF;
	  HAL_GPIO_Init(GPIOB, &gpio_init_structure);
}
