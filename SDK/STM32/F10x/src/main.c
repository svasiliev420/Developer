#include "main.h"
#include <string.h>

int main(void);
void init_LED(void);
void init_TIM2(void);
void init_USART1(void);
char USART1_putc(const char ch);
int USART1_puts(const char * str);


void delay(uint32_t time_delay)
{
	uint32_t i;
	for (i = 0; i < time_delay; i++);
}

int main()
{
	init_LED();
	
	for(;;)
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_9, !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9));
		delay(25 * 2048);
	}

	return 0;
}

void init_LED()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_Init(GPIOC, &(GPIO_InitTypeDef)
	{
		.GPIO_Pin	= GPIO_Pin_9| GPIO_Pin_8;
		.GPIO_Speed = GPIO_Speed_50MHz;
		.GPIO_Mode	= GPIO_Mode_Out_PP;
	});

}

void init_TIM2()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_Init(&(NVIC_InitTypeDef) 
	{
		.NVIC_IRQChannel					= TIM2_IRQn;
		.NVIC_IRQChannelCmd					= ENABLE;
		.NVIC_IRQChannelSubPriority			= 1;
		.NVIC_IRQChannelPreemptionPriority	= 0;
	});

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitStructure.TIM_ClockDivision 			= TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode 				= TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter 		= 0x0000;
	TIM_TimeBaseInitStructure.TIM_Prescaler 				= TIMER_PRESCALER;
	TIM_TimeBaseInitStructure.TIM_Period 					= TIMER_MAX_PERIOD;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

}/*init_TIM2*/

/*------------------------- init_USART1 ---------------------------*/
void init_USART1()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate            = 115200;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = (USART_Mode_Rx | USART_Mode_Tx);

	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1, ENABLE);

}

char USART1_putc(const char ch)
{
	uint32_t cnt = 100000;

	USART_SendData(USART1, (uint8_t) ch );

	while ( (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) && cnt-- );

	return (0 == cnt) ? -1 : ch;
}

int USART1_puts(const char * str)
{
	int r	= -1;
	int size= 0;

	uint8_t i;

	if (str == NULL)
		return r;

	size = strlen(str);

	for (i = 0; i < size; i++)
	{
		 if ( USART1_putc( *(str + i) ) == -1 )
			 return r;
	}

	r = 0;
	return r;
}

void TIM2_IRQHandler(void)
{
	BitAction state = !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_8);
	GPIO_WriteBit(GPIOC, GPIO_Pin_8,state);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
