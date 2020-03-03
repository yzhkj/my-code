#include "UserData.h"


//////////////////////////////////////////////////////////////////////////////
/// ÓÃÍ¾: ÕâÊÇ¿ØÖÆ°å²É¼¯ANG(±ä¾à½¬½Ç¶È)µÄ·½·¨¼¯
/// ×ÊÔ´: TIM?
///       Òı½Å:         ÖĞ¶ÏÊ±ÖÓ:
/// ·½·¨: PWM²¶»ñ³õÊ¼»¯   ²¶»ñÖĞ¶ÏÊı¾İ½âÎö¼°´¦Àí
///
//////////////////////////////////////////////////////////////////////////////

void PWM2_CH1_Cap_Init(u32 arr,u16 psc);


///³õÊ¼»¯
void ANG_Int(u32 arr,u16 psc) {
    PWM2_CH1_Cap_Init(arr,psc);
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PWM2²¶»ñÅäÖÃ  Ê¹ÓÃ¶¨Ê±Æ÷4 ×÷ÎªPWM2 µÄ¶¨Ê±Æ÷
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TIM_ICInitTypeDef  PWM2_ICInitStructure;

//¶¨Ê±Æ÷4Í¨µÀ1ÊäÈë²¶»ñÅäÖÃ
//arr£º×Ô¶¯ÖØ×°Öµ(TIM2,TIM5ÊÇ32Î»µÄ!!)
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
void PWM2_CH1_Cap_Init(u32 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1Ê±ÖÓÊ¹ÄÜ
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//Ê¹ÄÜPORTEÊ±ÖÓ

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  ÏÂÀ­
    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//³õÊ¼»¯PE9

    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9¸´ÓÃÎ»¶¨Ê±Æ÷1

    TIM_DeInit(TIM1); //ÖØÉè³ÉÄ¬ÈÏÖµ
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//Ê±ÖÓ·Ö¸îÖµ

    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //ÍøÉÏĞÂ¼ÓµÄ²¿·Ö
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//³õÊ¼»¯Ê±ÖÓTIM1


    //³õÊ¼»¯PWM2ÊäÈë²¶»ñ²ÎÊı
    PWM2_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
    PWM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//ÉÏÉıÑØ²¶»ñ
    PWM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//Ó³Éäµ½TI1ÉÏ
    PWM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ
    PWM2_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨

//    TIM_PWMIConfig(TIM1, &PWM2_ICInitStructure);
//    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1); //Ñ¡Ôñic1ÎªÊ¼ÖÕ´¥·¢Ô´
//    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);//TIM ´ÓÄ£Ê½ ´¥·¢ĞÅºÅµÄÉÏÉıÑØÖØĞÂ³õÊ¼»¯¼ÆÊıÆ÷ºÍ´¥·¢¼Ä´æÆ÷µÄ¸üĞÂÊÂ¼ş
//    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //Æô¶¯¶¨Ê±Æ÷±»¶¯´¥·¢
    TIM_ICInit(TIM1, &PWM2_ICInitStructure);

    TIM_ITConfig(TIM1
                 ,TIM_IT_Update
                 |TIM_IT_CC1
                 ,ENABLE);					//ÔÊĞí¸üĞÂÖĞ¶Ï ,ÔÊĞíCC1IE²¶»ñÖĞ¶Ï

    // TIM_ClearFlag(TIM1, TIM_IT_Update|TIM_IT_CC1);// Çå³ıÖĞ¶Ï±êÖ¾Î»


    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//ÇÀÕ¼ÓÅÏÈ¼¶4
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;				//×ÓÓÅÏÈ¼¶1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQÍ¨µÀÊ¹ÄÜ
    NVIC_Init(&NVIC_InitStructure);									//¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯VIC¼Ä´æÆ÷¡
    TIM_Cmd(TIM1,ENABLE ); 					//Ê¹ÄÜ¶¨Ê±Æ÷1
}


//²¶»ñ×´Ì¬
//[7]:0,Ã»ÓĞ³É¹¦µÄ²¶»ñ;1,³É¹¦²¶»ñµ½Ò»´Î.
//[6]:0,»¹Ã»²¶»ñµ½µÍµçÆ½;1,ÒÑ¾­²¶»ñµ½µÍµçÆ½ÁË.
//[5:0]:²¶»ñµÍµçÆ½ºóÒç³öµÄ´ÎÊı(¶ÔÓÚ32Î»¶¨Ê±Æ÷À´Ëµ,1us¼ÆÊıÆ÷¼Ó1,Òç³öÊ±¼ä:4294Ãë)
u8  PWM2CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×´Ì¬
u32	PWM2CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(PWM2/TIM5ÊÇ32Î»)
u32	PWM2CH1_CAPTURE_VAL_CYC;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)

//PWM2  ¶¨Ê±Æ÷1ÖĞ¶Ï·şÎñ³ÌĞò
void TIM1_CC_IRQHandler(void)
{

    if((PWM2CH1_CAPTURE_STA&0X80)==0)//»¹Î´³É¹¦²¶»ñ
    {
        if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//Òç³ö
        {
            if(PWM2CH1_CAPTURE_STA&0X40)//ÒÑ¾­²¶»ñµ½¸ßµçÆ½ÁË
            {
                if((PWM2CH1_CAPTURE_STA&0X3F)==0X3F)//¸ßµçÆ½Ì«³¤ÁË
                {
                    PWM2CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñÁËÒ»´Î
                    PWM2CH1_CAPTURE_VAL=0XFFFFFFFF;
                }

                else
                    PWM2CH1_CAPTURE_STA++;
            }
        }
        if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//²¶»ñ2·¢Éú²¶»ñÊÂ¼ş
        {


            if(PWM2CH1_CAPTURE_STA&0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
            {
                PWM2CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñµ½Ò»´Î¸ßµçÆ½Âö¿í
                PWM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.

                PWM2CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM1);

                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉıÑØ²¶»ñ
            }

            else  								//»¹Î´¿ªÊ¼,µÚÒ»´Î²¶»ñÉÏÉıÑØ
            {
                PWM2CH1_CAPTURE_STA=0;			//Çå¿Õ
                PWM2CH1_CAPTURE_VAL=0;
                PWM2CH1_CAPTURE_STA|=0X40;		//±ê¼Ç²¶»ñµ½ÁËÉÏÉıÑØ
                TIM_Cmd(TIM1,DISABLE ); 		//¹Ø±Õ¶¨Ê±Æ÷1
                TIM_SetCounter(TIM1,0);
                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
                TIM_Cmd(TIM1,ENABLE ); 			//Ê¹ÄÜ¶¨Ê±Æ÷1
            }
        }
    }
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //Çå³ıÖĞ¶Ï±êÖ¾Î»
}
