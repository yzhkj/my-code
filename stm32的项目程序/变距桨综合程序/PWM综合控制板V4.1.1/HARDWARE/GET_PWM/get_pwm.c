////#include "get_pwm.h"
////#include "led.h"
////#include "usart.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM1²¶»ñÅäÖÃ    Ê¹ÓÃ¶¨Ê±Æ÷3 ×÷ÎªPWM1 µÄ¶¨Ê±Æ÷
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM1_ICInitStructure;

//////¶¨Ê±Æ÷3Í¨µÀ1ÊäÈë²¶»ñÅäÖÃ
//////arr£º×Ô¶¯ÖØ×°Öµ(TIM4,TIM5ÊÇ32Î»µÄ!!)
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM1_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//TIM3Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//Ê¹ÄÜPORTAÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 					//GPIOA6
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//ÏÂÀ­
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//³õÊ¼»¯PA6

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 		//PA6¸´ÓÃÎ»¶¨Ê±Æ÷3


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷


////    //³õÊ¼»¯PWM1ÊäÈë²¶»ñ²ÎÊı
////    PWM1_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
////    PWM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//ÉÏÉıÑØ²¶»ñ
////    PWM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//Ó³Éäµ½TI1ÉÏ
////    PWM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ
////    PWM1_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
////    TIM_ICInit(TIM3, &PWM1_ICInitStructure);
////    TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//ÔÊĞí¸üĞÂÖĞ¶Ï ,ÔÊĞíCC1IE²¶»ñÖĞ¶Ï

//////    //³õÊ¼»¯TIM14 Channel1 PWMÄ£Ê½
//////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
//////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
//////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔµÍ
//////    TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM1 4OC1
//////    TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM14ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
//////    TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEÊ¹ÄÜ


////    TIM_Cmd(TIM3,ENABLE ); 					//Ê¹ÄÜ¶¨Ê±Æ÷3


////    //ÖĞ¶ÏÅäÖÃ
////    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//ÇÀÕ¼ÓÅÏÈ¼¶2
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;				//×ÓÓÅÏÈ¼¶0
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQÍ¨µÀÊ¹ÄÜ
////    NVIC_Init(&NVIC_InitStructure);									//¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯VIC¼Ä´æÆ÷¡¢


////}


//////²¶»ñ×´Ì¬
//////[7]:0,Ã»ÓĞ³É¹¦µÄ²¶»ñ;1,³É¹¦²¶»ñµ½Ò»´Î.
//////[6]:0,»¹Ã»²¶»ñµ½µÍµçÆ½;1,ÒÑ¾­²¶»ñµ½µÍµçÆ½ÁË.
//////[5:0]:²¶»ñµÍµçÆ½ºóÒç³öµÄ´ÎÊı(¶ÔÓÚ32Î»¶¨Ê±Æ÷À´Ëµ,1us¼ÆÊıÆ÷¼Ó1,Òç³öÊ±¼ä:4294Ãë)
////u8  PWM1CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×´Ì¬
////u32	PWM1CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)
////u32	PWM1CH1_CAPTURE_VAL_CYC;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)
////u32 PWM1Data;//ÎÒµÄ¼ÆÊıÖµ

//////PWM1 ¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñ³ÌĞò  PWM1¿Ú
////void TIM3_IRQHandler(void)
////{

////    if((PWM1CH1_CAPTURE_STA&0X80)==0)//»¹Î´³É¹¦²¶»ñ
////    {
////        if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//Òç³ö
////        {
////            if(PWM1CH1_CAPTURE_STA&0X40)//ÒÑ¾­²¶»ñµ½¸ßµçÆ½ÁË
////            {
////                if((PWM1CH1_CAPTURE_STA&0X3F)==0X3F)//¸ßµçÆ½Ì«³¤ÁË
////                {
////                    PWM1CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñÁËÒ»´Î
////                    PWM1CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else {
////                    PWM1CH1_CAPTURE_STA++;
////                }
////            }
////        }
////        if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//²¶»ñ1·¢Éú²¶»ñÊÂ¼ş
////        {

////            if(PWM1CH1_CAPTURE_STA&0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
////            {
////                PWM1CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñµ½Ò»´Î¸ßµçÆ½Âö¿í
////                PWM1CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.

////                PWM1CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM3);
////                TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉıÑØ²¶»ñ    TIM_ICPolarity_Rising
////            }

////            else  								//»¹Î´¿ªÊ¼,µÚÒ»´Î²¶»ñÉÏÉıÑØ
////            {
////                PWM1CH1_CAPTURE_STA=0;			//Çå¿Õ
////                PWM1CH1_CAPTURE_VAL=0;
////                PWM1CH1_CAPTURE_STA|=0X40;		//±ê¼Ç²¶»ñµ½ÁËÉÏÉıÑØ
////                TIM_Cmd(TIM3,DISABLE ); 		//¹Ø±Õ¶¨Ê±Æ÷5
////                TIM_SetCounter(TIM3,0);
////                TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂ½µÑØ²¶»ñ   TIM_ICPolarity_Falling
////                TIM_Cmd(TIM3,ENABLE ); 			//Ê¹ÄÜ¶¨Ê±Æ÷5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //Çå³ıÖĞ¶Ï±êÖ¾Î»
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2 Êä³öÅäÖÃ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWMÊä³ö³õÊ¼»¯
//////arr£º×Ô¶¯ÖØ×°Öµ
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM1_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //´Ë²¿·ÖĞèÊÖ¶¯ĞŞ¸ÄIO¿ÚÉèÖÃ
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//TIM3Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//Ê¹ÄÜPORTAÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 					//GPIOA6
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//ÏÂÀ­
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//³õÊ¼»¯PA6

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 		//PA6¸´ÓÃÎ»¶¨Ê±Æ÷3


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷


////    //³õÊ¼»¯TIM12 Channel1 PWMÄ£Ê½
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔµÍ
////    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM1 4OC1
////    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM12ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
////    TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEÊ¹ÄÜ

////    TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIM2
////}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2²¶»ñÅäÖÃ  Ê¹ÓÃ¶¨Ê±Æ÷4 ×÷ÎªPWM2 µÄ¶¨Ê±Æ÷
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM2_ICInitStructure;

//////¶¨Ê±Æ÷4Í¨µÀ1ÊäÈë²¶»ñÅäÖÃ
//////arr£º×Ô¶¯ÖØ×°Öµ(TIM2,TIM5ÊÇ32Î»µÄ!!)
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM2_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//Ê¹ÄÜPORTEÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  ÏÂÀ­
////    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//³õÊ¼»¯PE9

////    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9¸´ÓÃÎ»¶¨Ê±Æ÷1

////    TIM_DeInit(TIM1); //ÖØÉè³ÉÄ¬ÈÏÖµ
////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//Ê±ÖÓ·Ö¸îÖµ

////    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //ÍøÉÏĞÂ¼ÓµÄ²¿·Ö
////    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//³õÊ¼»¯Ê±ÖÓTIM1


////    //³õÊ¼»¯PWM2ÊäÈë²¶»ñ²ÎÊı
////    PWM2_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
////    PWM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//ÉÏÉıÑØ²¶»ñ
////    PWM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//Ó³Éäµ½TI1ÉÏ
////    PWM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ
////    PWM2_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨

//////    TIM_PWMIConfig(TIM1, &PWM2_ICInitStructure);
//////    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1); //Ñ¡Ôñic1ÎªÊ¼ÖÕ´¥·¢Ô´
//////    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);//TIM ´ÓÄ£Ê½ ´¥·¢ĞÅºÅµÄÉÏÉıÑØÖØĞÂ³õÊ¼»¯¼ÆÊıÆ÷ºÍ´¥·¢¼Ä´æÆ÷µÄ¸üĞÂÊÂ¼ş
//////    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //Æô¶¯¶¨Ê±Æ÷±»¶¯´¥·¢
////    TIM_ICInit(TIM1, &PWM2_ICInitStructure);

////    TIM_ITConfig(TIM1
////                 ,TIM_IT_Update
////                 |TIM_IT_CC1
////                 ,ENABLE);					//ÔÊĞí¸üĞÂÖĞ¶Ï ,ÔÊĞíCC1IE²¶»ñÖĞ¶Ï

////    // TIM_ClearFlag(TIM1, TIM_IT_Update|TIM_IT_CC1);// Çå³ıÖĞ¶Ï±êÖ¾Î»


////    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//ÇÀÕ¼ÓÅÏÈ¼¶3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//×ÓÓÅÏÈ¼¶1
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQÍ¨µÀÊ¹ÄÜ
////    NVIC_Init(&NVIC_InitStructure);									//¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯VIC¼Ä´æÆ÷¡
////    TIM_Cmd(TIM1,ENABLE ); 					//Ê¹ÄÜ¶¨Ê±Æ÷1
////}


//////²¶»ñ×´Ì¬
//////[7]:0,Ã»ÓĞ³É¹¦µÄ²¶»ñ;1,³É¹¦²¶»ñµ½Ò»´Î.
//////[6]:0,»¹Ã»²¶»ñµ½µÍµçÆ½;1,ÒÑ¾­²¶»ñµ½µÍµçÆ½ÁË.
//////[5:0]:²¶»ñµÍµçÆ½ºóÒç³öµÄ´ÎÊı(¶ÔÓÚ32Î»¶¨Ê±Æ÷À´Ëµ,1us¼ÆÊıÆ÷¼Ó1,Òç³öÊ±¼ä:4294Ãë)
////u8  PWM2CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×´Ì¬
////u32	PWM2CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(PWM2/TIM5ÊÇ32Î»)
////u32	PWM2CH1_CAPTURE_VAL_CYC;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)

//////PWM2  ¶¨Ê±Æ÷1ÖĞ¶Ï·şÎñ³ÌĞò
////void TIM1_CC_IRQHandler(void)
////{

////    if((PWM2CH1_CAPTURE_STA&0X80)==0)//»¹Î´³É¹¦²¶»ñ
////    {
////        if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//Òç³ö
////        {
////            if(PWM2CH1_CAPTURE_STA&0X40)//ÒÑ¾­²¶»ñµ½¸ßµçÆ½ÁË
////            {
////                if((PWM2CH1_CAPTURE_STA&0X3F)==0X3F)//¸ßµçÆ½Ì«³¤ÁË
////                {
////                    PWM2CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñÁËÒ»´Î
////                    PWM2CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }

////                else
////                    PWM2CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//²¶»ñ2·¢Éú²¶»ñÊÂ¼ş
////        {


////            if(PWM2CH1_CAPTURE_STA&0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
////            {
////                PWM2CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñµ½Ò»´Î¸ßµçÆ½Âö¿í
////                PWM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.

////                PWM2CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM1);

////                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉıÑØ²¶»ñ
////            }

////            else  								//»¹Î´¿ªÊ¼,µÚÒ»´Î²¶»ñÉÏÉıÑØ
////            {
////                PWM2CH1_CAPTURE_STA=0;			//Çå¿Õ
////                PWM2CH1_CAPTURE_VAL=0;
////                PWM2CH1_CAPTURE_STA|=0X40;		//±ê¼Ç²¶»ñµ½ÁËÉÏÉıÑØ
////                TIM_Cmd(TIM1,DISABLE ); 		//¹Ø±Õ¶¨Ê±Æ÷1
////                TIM_SetCounter(TIM1,0);
////                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
////                TIM_Cmd(TIM1,ENABLE ); 			//Ê¹ÄÜ¶¨Ê±Æ÷1
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //Çå³ıÖĞ¶Ï±êÖ¾Î»
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2 Êä³öÅäÖÃ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWMÊä³ö³õÊ¼»¯
//////arr£º×Ô¶¯ÖØ×°Öµ
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM2_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //´Ë²¿·ÖĞèÊÖ¶¯ĞŞ¸ÄIO¿ÚÉèÖÃ
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//Ê¹ÄÜPORTEÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  ÏÂÀ­
////    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//³õÊ¼»¯PE9

////    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9¸´ÓÃÎ»¶¨Ê±Æ÷1

////    TIM_DeInit(TIM1); //ÖØÉè³ÉÄ¬ÈÏÖµ
////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//Ê±ÖÓ·Ö¸îÖµ

////    // TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //ÍøÉÏĞÂ¼ÓµÄ²¿·Ö
////    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//³õÊ¼»¯Ê±ÖÓTIM1

////    //³õÊ¼»¯TIM12 Channel1 PWMÄ£Ê½
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔµÍ
////    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM1 4OC1

////    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM12ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷

////    TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEÊ¹ÄÜ

////    TIM_Cmd(TIM1, ENABLE);  //Ê¹ÄÜTIM2
////}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM3²¶»ñÅäÖÃ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM3_ICInitStructure;

//////¶¨Ê±Æ÷3Í¨µÀ1ÊäÈë²¶»ñÅäÖÃ
//////arr£º×Ô¶¯ÖØ×°Öµ(TIM4,TIM5ÊÇ32Î»µÄ!!)
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM3_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  		//TIM5Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//Ê¹ÄÜPORTAÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//ÏÂÀ­
////    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//³õÊ¼»¯PB14

////    GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); 		//PB14¸´ÓÃÎ»¶¨Ê±Æ÷12


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);


////    //³õÊ¼»¯TIM5ÊäÈë²¶»ñ²ÎÊı
////    PWM3_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
////    PWM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//ÉÏÉıÑØ²¶»ñ
////    PWM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//Ó³Éäµ½TI1ÉÏ
////    PWM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ
////    PWM3_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
////    TIM_ICInit(TIM12, &PWM3_ICInitStructure);

////    TIM_ITConfig(TIM12,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//ÔÊĞí¸üĞÂÖĞ¶Ï ,ÔÊĞíCC1IE²¶»ñÖĞ¶Ï

////    TIM_Cmd(TIM12,ENABLE ); 					//Ê¹ÄÜ¶¨Ê±Æ÷5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//ÇÀÕ¼ÓÅÏÈ¼¶3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;				//×ÓÓÅÏÈ¼¶2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQÍ¨µÀÊ¹ÄÜ
////    NVIC_Init(&NVIC_InitStructure);									//¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯VIC¼Ä´æÆ÷¡¢


////}


//////²¶»ñ×´Ì¬
//////[7]:0,Ã»ÓĞ³É¹¦µÄ²¶»ñ;1,³É¹¦²¶»ñµ½Ò»´Î.
//////[6]:0,»¹Ã»²¶»ñµ½µÍµçÆ½;1,ÒÑ¾­²¶»ñµ½µÍµçÆ½ÁË.
//////[5:0]:²¶»ñµÍµçÆ½ºóÒç³öµÄ´ÎÊı(¶ÔÓÚ32Î»¶¨Ê±Æ÷À´Ëµ,1us¼ÆÊıÆ÷¼Ó1,Òç³öÊ±¼ä:4294Ãë)
////u8  PWM3CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×´Ì¬
////u32	PWM3CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)
////u32	PWM3CH1_CAPTURE_VAL_CYC;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)

//////¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñ³ÌĞò
////void TIM8_BRK_TIM12_IRQHandler(void)
////{

////    if((PWM3CH1_CAPTURE_STA&0X80)==0)//»¹Î´³É¹¦²¶»ñ
////    {
////        if(TIM_GetITStatus(TIM12, TIM_IT_Update) != RESET)//Òç³ö
////        {
////            if(PWM3CH1_CAPTURE_STA&0X40)//ÒÑ¾­²¶»ñµ½¸ßµçÆ½ÁË
////            {
////                if((PWM3CH1_CAPTURE_STA&0X3F)==0X3F)//¸ßµçÆ½Ì«³¤ÁË
////                {
////                    PWM3CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñÁËÒ»´Î
////                    PWM3CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }

////                else
////                    PWM3CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM12, TIM_IT_CC1) != RESET)//²¶»ñ1·¢Éú²¶»ñÊÂ¼ş
////        {

////            if(PWM3CH1_CAPTURE_STA&0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
////            {
////                PWM3CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñµ½Ò»´Î¸ßµçÆ½Âö¿í
////                PWM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM12);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.

////                PWM3CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM12);

////                TIM_OC1PolarityConfig(TIM12,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉıÑØ²¶»ñ
////            }

////            else  								//»¹Î´¿ªÊ¼,µÚÒ»´Î²¶»ñÉÏÉıÑØ
////            {
////                PWM3CH1_CAPTURE_STA=0;			//Çå¿Õ
////                PWM3CH1_CAPTURE_VAL=0;
////                PWM3CH1_CAPTURE_STA|=0X40;		//±ê¼Ç²¶»ñµ½ÁËÉÏÉıÑØ
////                TIM_Cmd(TIM12,DISABLE ); 		//¹Ø±Õ¶¨Ê±Æ÷5
////                TIM_SetCounter(TIM12,0);
////                TIM_OC1PolarityConfig(TIM12,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
////                TIM_Cmd(TIM12,ENABLE ); 			//Ê¹ÄÜ¶¨Ê±Æ÷5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM12, TIM_IT_CC1|TIM_IT_Update); //Çå³ıÖĞ¶Ï±êÖ¾Î»
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM3 Êä³öÅäÖÃ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWMÊä³ö³õÊ¼»¯
//////arr£º×Ô¶¯ÖØ×°Öµ
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM3_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //´Ë²¿·ÖĞèÊÖ¶¯ĞŞ¸ÄIO¿ÚÉèÖÃ
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  		//TIM5Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//Ê¹ÄÜPORTAÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 					//GPIOA5
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//ÏÂÀ­
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//³õÊ¼»¯pa5

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2); 		//Pa5¸´ÓÃÎ»¶¨Ê±Æ÷2


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
////    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷2

////    //³õÊ¼»¯TIM12 Channel1 PWMÄ£Ê½
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔµÍ
////    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM1 4OC1

////    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM12ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷

////    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEÊ¹ÄÜ

////    TIM_Cmd(TIM2, ENABLE);  //Ê¹ÄÜTIM2
////}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM4 Êä³öÅäÖÃ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWMÊä³ö³õÊ¼»¯
//////arr£º×Ô¶¯ÖØ×°Öµ
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM4_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //´Ë²¿·ÖĞèÊÖ¶¯ĞŞ¸ÄIO¿ÚÉèÖÃ

////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//Ê¹ÄÜPORTFÊ±ÖÓ

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); //GPIOA1¸´ÓÃÎª¶¨Ê±Æ÷2

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOA1
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
////    GPIO_Init(GPIOA,&GPIO_InitStructure);              //³õÊ¼»¯PA0

////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷2

////    //³õÊ¼»¯TIM2 Channel1 PWMÄ£Ê½
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔµÍ
////    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM1 4OC1

////    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM2ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷

////    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEÊ¹ÄÜ

////    TIM_Cmd(TIM2, ENABLE);  //Ê¹ÄÜTIM2
////}


/////////////////////////////////////////////////
///////PW4 ÊäÈëÅäÖÃ
/////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM4_ICInitStructure;
////void PWM4_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM5Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 		//Ê¹ÄÜPORTAÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//ÏÂÀ­
////    GPIO_Init(GPIOD,&GPIO_InitStructure); 						//³õÊ¼»¯PB14

////    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); 		//PB14¸´ÓÃÎ»¶¨Ê±Æ÷4


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);


////    //³õÊ¼»¯TIM5ÊäÈë²¶»ñ²ÎÊı
////    PWM4_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
////    PWM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//ÉÏÉıÑØ²¶»ñ
////    PWM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//Ó³Éäµ½TI1ÉÏ
////    PWM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ
////    PWM4_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
////    TIM_ICInit(TIM4, &PWM4_ICInitStructure);
////    TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//ÔÊĞí¸üĞÂÖĞ¶Ï ,ÔÊĞíCC1IE²¶»ñÖĞ¶Ï

////    TIM_Cmd(TIM4,ENABLE ); 					//Ê¹ÄÜ¶¨Ê±Æ÷5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//ÇÀÕ¼ÓÅÏÈ¼¶3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//×ÓÓÅÏÈ¼¶2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQÍ¨µÀÊ¹ÄÜ
////    NVIC_Init(&NVIC_InitStructure);									//¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯VIC¼Ä´æÆ÷¡¢
////}

//////²¶»ñ×´Ì¬
//////[7]:0,Ã»ÓĞ³É¹¦µÄ²¶»ñ;1,³É¹¦²¶»ñµ½Ò»´Î.
//////[6]:0,»¹Ã»²¶»ñµ½µÍµçÆ½;1,ÒÑ¾­²¶»ñµ½µÍµçÆ½ÁË.
//////[5:0]:²¶»ñµÍµçÆ½ºóÒç³öµÄ´ÎÊı(¶ÔÓÚ32Î»¶¨Ê±Æ÷À´Ëµ,1us¼ÆÊıÆ÷¼Ó1,Òç³öÊ±¼ä:4294Ãë)
////u8  PWM4CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×´Ì¬
////u32	PWM4CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)
////u32	PWM4CH1_CAPTURE_VAL_CYC;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)

////void TIM4_IRQHandler(void) {

////    if((PWM4CH1_CAPTURE_STA&0X80)==0)//»¹Î´³É¹¦²¶»ñ
////    {
////        if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//Òç³ö
////        {
////            if(PWM4CH1_CAPTURE_STA&0X40)//ÒÑ¾­²¶»ñµ½¸ßµçÆ½ÁË
////            {
////                if((PWM4CH1_CAPTURE_STA&0X3F)==0X3F)//¸ßµçÆ½Ì«³¤ÁË
////                {
////                    PWM4CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñÁËÒ»´Î
////                    PWM4CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else
////                    PWM4CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//²¶»ñ1·¢Éú²¶»ñÊÂ¼ş
////        {

////            if(PWM4CH1_CAPTURE_STA&0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
////            {
////                PWM4CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñµ½Ò»´Î¸ßµçÆ½Âö¿í
////                PWM4CH1_CAPTURE_VAL=TIM_GetCapture1(TIM4);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.

////                PWM4CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM4);

////                TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉıÑØ²¶»ñ//TIM_ICPolarity_Falling
////            }

////            else  								//»¹Î´¿ªÊ¼,µÚÒ»´Î²¶»ñÉÏÉıÑØ
////            {
////                PWM4CH1_CAPTURE_STA=0;			//Çå¿Õ
////                PWM4CH1_CAPTURE_VAL=0;
////                PWM4CH1_CAPTURE_STA|=0X40;		//±ê¼Ç²¶»ñµ½ÁËÉÏÉıÑØ
////                TIM_Cmd(TIM4,DISABLE); 		//¹Ø±Õ¶¨Ê±Æ÷5
////                TIM_SetCounter(TIM4,0);
////                TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂ½µÑØ²¶»ñ//TIM_ICPolarity_Rising
////                TIM_Cmd(TIM4,ENABLE ); 			//Ê¹ÄÜ¶¨Ê±Æ÷5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_Update); //Çå³ıÖĞ¶Ï±êÖ¾Î»
////}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM5 Êä³öÅäÖÃ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////PWMÊä³ö³õÊ¼»¯
//////arr£º×Ô¶¯ÖØ×°Öµ
//////psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////void PWM5_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //´Ë²¿·ÖĞèÊÖ¶¯ĞŞ¸ÄIO¿ÚÉèÖÃ

////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM2Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//Ê¹ÄÜPORTFÊ±ÖÓ

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //GPIOA0¸´ÓÃÎª¶¨Ê±Æ÷5

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOA0
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
////    GPIO_Init(GPIOA,&GPIO_InitStructure);              //³õÊ¼»¯PA0

////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   //×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷2

////    //³õÊ¼»¯TIM5 Channel1 PWMÄ£Ê½
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔµÍ
////    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM1 4OC1

////    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM2ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷

////    TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPEÊ¹ÄÜ

////    TIM_Cmd(TIM5, ENABLE);  //Ê¹ÄÜTIM2
////}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM5 Êä³öÅäÖÃ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM5_ICInitStructure;
////void PWM5_CH1_Cap_Init(u32 arr,u16 psc) {
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  		//TIM5Ê±ÖÓÊ¹ÄÜ
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//Ê¹ÄÜPORTAÊ±ÖÓ

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//ÏÂÀ­
////    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//³õÊ¼»¯PB14

////    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11); 		//PB14¸´ÓÃÎ»¶¨Ê±Æ÷4


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);


////    //³õÊ¼»¯TIM5ÊäÈë²¶»ñ²ÎÊı
////    PWM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
////    PWM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//ÉÏÉıÑØ²¶»ñ
////    PWM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//Ó³Éäµ½TI1ÉÏ
////    PWM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ
////    PWM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
////    TIM_ICInit(TIM11, &PWM5_ICInitStructure);
////    TIM_ITConfig(TIM11,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//ÔÊĞí¸üĞÂÖĞ¶Ï ,ÔÊĞíCC1IE²¶»ñÖĞ¶Ï

////    TIM_Cmd(TIM11,ENABLE ); 					//Ê¹ÄÜ¶¨Ê±Æ÷5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn ;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//ÇÀÕ¼ÓÅÏÈ¼¶3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//×ÓÓÅÏÈ¼¶2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQÍ¨µÀÊ¹ÄÜ
////    NVIC_Init(&NVIC_InitStructure);									//¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯VIC¼Ä´æÆ÷¡¢
////}
//////²¶»ñ×´Ì¬
//////[7]:0,Ã»ÓĞ³É¹¦µÄ²¶»ñ;1,³É¹¦²¶»ñµ½Ò»´Î.
//////[6]:0,»¹Ã»²¶»ñµ½µÍµçÆ½;1,ÒÑ¾­²¶»ñµ½µÍµçÆ½ÁË.
//////[5:0]:²¶»ñµÍµçÆ½ºóÒç³öµÄ´ÎÊı(¶ÔÓÚ32Î»¶¨Ê±Æ÷À´Ëµ,1us¼ÆÊıÆ÷¼Ó1,Òç³öÊ±¼ä:4294Ãë)
////u8  PWM5CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×´Ì¬
////u32	PWM5CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)
////u32	PWM5CH1_CAPTURE_VAL_CYC;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)
////void TIM1_TRG_COM_TIM11_IRQHandler(void) {
////    if((PWM5CH1_CAPTURE_STA&0X80)==0)//»¹Î´³É¹¦²¶»ñ
////    {
////        if(TIM_GetITStatus(TIM11, TIM_IT_Update) != RESET)//Òç³ö
////        {
////            if(PWM5CH1_CAPTURE_STA&0X40)//ÒÑ¾­²¶»ñµ½¸ßµçÆ½ÁË
////            {
////                if((PWM5CH1_CAPTURE_STA&0X3F)==0X3F)//¸ßµçÆ½Ì«³¤ÁË
////                {
////                    PWM5CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñÁËÒ»´Î
////                    PWM5CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else
////                    PWM5CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM11, TIM_IT_CC1) != RESET)//²¶»ñ1·¢Éú²¶»ñÊÂ¼ş
////        {

////            if(PWM5CH1_CAPTURE_STA&0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
////            {
////                PWM5CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñµ½Ò»´Î¸ßµçÆ½Âö¿í
////                PWM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM11);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.

////                PWM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM11);

////                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉıÑØ²¶»ñ//TIM_ICPolarity_Falling
////            }

////            else  								//»¹Î´¿ªÊ¼,µÚÒ»´Î²¶»ñÉÏÉıÑØ
////            {
////                PWM5CH1_CAPTURE_STA=0;			//Çå¿Õ
////                PWM5CH1_CAPTURE_VAL=0;
////                PWM5CH1_CAPTURE_STA|=0X40;		//±ê¼Ç²¶»ñµ½ÁËÉÏÉıÑØ
////                TIM_Cmd(TIM11,DISABLE); 		//¹Ø±Õ¶¨Ê±Æ÷5
////                TIM_SetCounter(TIM11,0);
////                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂ½µÑØ²¶»ñ//TIM_ICPolarity_Rising
////                TIM_Cmd(TIM11,ENABLE ); 			//Ê¹ÄÜ¶¨Ê±Æ÷5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM11, TIM_IT_CC1|TIM_IT_Update); //Çå³ıÖĞ¶Ï±êÖ¾Î»
////}



////// TIM_ICInitTypeDef  TIM5_ICInitStructure;

////// //¶¨Ê±Æ÷5Í¨µÀ1ÊäÈë²¶»ñÅäÖÃ
////// //arr£º×Ô¶¯ÖØ×°Öµ(TIM4,TIM5ÊÇ32Î»µÄ!!)
////// //psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
////// void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
////// {
////// 	GPIO_InitTypeDef GPIO_InitStructure;
////// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////// 	NVIC_InitTypeDef NVIC_InitStructure;


////// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  		//TIM5Ê±ÖÓÊ¹ÄÜ
////// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//Ê¹ÄÜPORTAÊ±ÖÓ

////// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 					//GPIOA0
////// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//¸´ÓÃ¹¦ÄÜ
////// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//ËÙ¶È100MHz
////// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//ÍÆÍì¸´ÓÃÊä³ö
////// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//ÏÂÀ­
////// 	GPIO_Init(GPIOA,&GPIO_InitStructure); 						//³õÊ¼»¯PA0

////// 	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); 		//PA0¸´ÓÃÎ»¶¨Ê±Æ÷5


////// 	TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//¶¨Ê±Æ÷·ÖÆµ
////// 	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//ÏòÉÏ¼ÆÊıÄ£Ê½
////// 	TIM_TimeBaseStructure.TIM_Period=arr;   					//×Ô¶¯ÖØ×°ÔØÖµ
////// 	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////// 	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);


////// 	//³õÊ¼»¯TIM5ÊäÈë²¶»ñ²ÎÊı
////// 	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	Ñ¡ÔñÊäÈë¶Ë IC1Ó³Éäµ½TI1ÉÏ
////// 	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//ÉÏÉıÑØ²¶»ñ
////// 	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//Ó³Éäµ½TI1ÉÏ
////// 	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//ÅäÖÃÊäÈë·ÖÆµ,²»·ÖÆµ
////// 	TIM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ÅäÖÃÊäÈëÂË²¨Æ÷ ²»ÂË²¨
////// 	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

////// 	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//ÔÊĞí¸üĞÂÖĞ¶Ï ,ÔÊĞíCC1IE²¶»ñÖĞ¶Ï

////// 	TIM_Cmd(TIM5,ENABLE ); 					//Ê¹ÄÜ¶¨Ê±Æ÷5


////// 	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
////// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;			//ÇÀÕ¼ÓÅÏÈ¼¶3
////// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;				//×ÓÓÅÏÈ¼¶3
////// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQÍ¨µÀÊ¹ÄÜ
////// 	NVIC_Init(&NVIC_InitStructure);									//¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯VIC¼Ä´æÆ÷¡¢


////// }


////// //²¶»ñ×´Ì¬
////// //[7]:0,Ã»ÓĞ³É¹¦µÄ²¶»ñ;1,³É¹¦²¶»ñµ½Ò»´Î.
////// //[6]:0,»¹Ã»²¶»ñµ½µÍµçÆ½;1,ÒÑ¾­²¶»ñµ½µÍµçÆ½ÁË.
////// //[5:0]:²¶»ñµÍµçÆ½ºóÒç³öµÄ´ÎÊı(¶ÔÓÚ32Î»¶¨Ê±Æ÷À´Ëµ,1us¼ÆÊıÆ÷¼Ó1,Òç³öÊ±¼ä:4294Ãë)
////// u8  TIM5CH1_CAPTURE_STA=0;	//ÊäÈë²¶»ñ×´Ì¬
////// u32	TIM5CH1_CAPTURE_VAL;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)
////// u32	TIM5CH1_CAPTURE_VAL_CYC;	//ÊäÈë²¶»ñÖµ(TIM4/TIM5ÊÇ32Î»)

////// //¶¨Ê±Æ÷5ÖĞ¶Ï·şÎñ³ÌĞò
////// void TIM5_IRQHandler(void)
////// {

//////  	if((TIM5CH1_CAPTURE_STA&0X80)==0)//»¹Î´³É¹¦²¶»ñ
////// 	{
////// 		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//Òç³ö
////// 		{
////// 			if(TIM5CH1_CAPTURE_STA&0X40)//ÒÑ¾­²¶»ñµ½¸ßµçÆ½ÁË
////// 			{
////// 				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//¸ßµçÆ½Ì«³¤ÁË
////// 				{
////// 					TIM5CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñÁËÒ»´Î
////// 					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
////// 				}

////// 				else
////// 					TIM5CH1_CAPTURE_STA++;
////// 			}
////// 		}
////// 		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//²¶»ñ1·¢Éú²¶»ñÊÂ¼ş
////// 		{

////// 			if(TIM5CH1_CAPTURE_STA&0X40)		//²¶»ñµ½Ò»¸öÏÂ½µÑØ
////// 			{
////// 				TIM5CH1_CAPTURE_STA|=0X80;		//±ê¼Ç³É¹¦²¶»ñµ½Ò»´Î¸ßµçÆ½Âö¿í
////// 				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//»ñÈ¡µ±Ç°µÄ²¶»ñÖµ.

////// 				TIM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM5);

////// 	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ÉèÖÃÎªÉÏÉıÑØ²¶»ñ
////// 			}

////// 			else  								//»¹Î´¿ªÊ¼,µÚÒ»´Î²¶»ñÉÏÉıÑØ
////// 			{
////// 				TIM5CH1_CAPTURE_STA=0;			//Çå¿Õ
////// 				TIM5CH1_CAPTURE_VAL=0;
////// 				TIM5CH1_CAPTURE_STA|=0X40;		//±ê¼Ç²¶»ñµ½ÁËÉÏÉıÑØ
////// 				TIM_Cmd(TIM5,DISABLE ); 		//¹Ø±Õ¶¨Ê±Æ÷5
////// 	 			TIM_SetCounter(TIM5,0);
////// 	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ÉèÖÃÎªÏÂ½µÑØ²¶»ñ
////// 				TIM_Cmd(TIM5,ENABLE ); 			//Ê¹ÄÜ¶¨Ê±Æ÷5
////// 			}
////// 		}
//////  	}
////// 	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //Çå³ıÖĞ¶Ï±êÖ¾Î»
////// }

