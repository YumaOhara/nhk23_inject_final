//robomaster用
#include <main.h>
#include "stm32f1xx_hal_uart.h"		// SBDBTとUART通信をするためのライブラリ

// UART用構造体変数
extern UART_HandleTypeDef huart2;
extern uint8_t RxBuffer[8];

extern uint8_t B;
extern uint8_t A;
extern uint8_t X;
extern uint8_t Y;
extern uint8_t RIGHT;
extern uint8_t DOWN;
extern uint8_t LEFT;
extern uint8_t UP;
extern uint8_t R1;
extern uint8_t R2;
extern uint8_t L1;
extern uint8_t L2;
extern uint8_t START;
extern uint8_t BACK;
extern uint8_t RightAxisX;
extern uint8_t RightAxisY;
extern uint8_t LeftAxisX;
extern uint8_t LeftAxisY;

// タイマ用構造体変数
extern TIM_HandleTypeDef htim1;

volatile int32_t left = 500;
volatile int32_t center = 500;
volatile int32_t right = 500;


// メイン関数
void main_cpp(void)
{
	// UART開始
	HAL_UART_Receive_IT(&huart2, RxBuffer, 8);

	// LED緑を点灯
	HAL_GPIO_WritePin(GPIOC, GREEN_LED_Pin, GPIO_PIN_SET);

	// 無効化後、黄色LEDを消灯、赤色LEDを点灯
	HAL_GPIO_WritePin(GPIOC, YELLOW_LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, RED_LED_Pin, GPIO_PIN_SET);

	// 有効化後、黄色LEDを点灯、赤色LEDを消灯
	HAL_GPIO_WritePin(GPIOC, YELLOW_LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, RED_LED_Pin, GPIO_PIN_RESET);


	// メインループ
	while(1)
	{

		// もし、BACKボタンが押されている(BACK == 1)なら、
		if(BACK == 1)
		{

			// 無効化後、黄色LEDを消灯、赤色LEDを点灯
			HAL_GPIO_WritePin(GPIOC, YELLOW_LED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RED_LED_Pin, GPIO_PIN_SET);

			// LED緑を点灯
			HAL_GPIO_WritePin(GPIOC, GREEN_LED_Pin, GPIO_PIN_SET);

			//PWM無効化
			//tim1
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_4);
		}

		// もし、STARTボタンが押されている(START == 1)なら、
		if(START == 1)
		{
			// 有効化後、黄色LEDを点灯、赤色LEDを消灯
			HAL_GPIO_WritePin(GPIOC, YELLOW_LED_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, RED_LED_Pin, GPIO_PIN_RESET);

			// LED緑を点灯
			HAL_GPIO_WritePin(GPIOC, GREEN_LED_Pin, GPIO_PIN_SET);

			//PWM有効化
			//tim1
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);

			//max pulse
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 999);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 999);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 999);
			HAL_Delay(100);
			//min pulse
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);


		}
		//CH1 left X
		//CH2 center Y
		//CH3 right B

		while(LEFT == 1){
			if(X == 1){
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 900);
			}
			if(B == 1){
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 900);
			}
			if(Y == 1){
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 930);
			}
		}

		while(DOWN == 1){
			if(Y == 1){
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 650);
			}
		}

		if(X == 1){
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 550);
		}

		if(Y == 1){
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 580);
		}

		if(B == 1){
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 550);
		}

		if(A == 1){
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);
		}


	}
}
