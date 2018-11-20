/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "STM32_RTC.H"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
//#include "STM32F10x_BitBand.H"


_calendar_obj calendar;    //时钟结构体
//平均的月份日期表
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
/*rtc中断向量配置*/
void NVIC_ConfigurationRTC(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void RTC_Configuration(void)
{
  /* 使能PWR和BKP时钟 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
  /* 使能对后备寄存器的访问 */ 
  PWR_BackupAccessCmd(ENABLE);
  /* 复位BKP寄存器 */ 
  BKP_DeInit();
  /* 使能LSE */ 
  RCC_LSEConfig(RCC_LSE_ON);
  /*等待启动完成 */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {}
  /* 将 RTC时钟设置为LSE这个32.768KHZ的晶振*/ 
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  /* 使能RTC Clock */ 
  RCC_RTCCLKCmd(ENABLE);
  /* 等待同步 */ 
  RTC_WaitForSynchro();
  /* 等待对RTC寄存器最后的写操作完成*/             
  RTC_WaitForLastTask();
  /* 配置了预分频值: 设置RTC时钟周期为1s */
  //RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)*/   //24小时会快9秒
  RTC_SetPrescaler(32775); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)*/
  /* 等待对RTC寄存器最后的写操作完成 */
  RTC_WaitForLastTask();
  /* 使能RTC秒中断 */ 
  RTC_ITConfig(RTC_IT_SEC, ENABLE);
  /* 等待对RTC寄存器最后的写操作完成 */         
  RTC_WaitForLastTask();
      
      
  RTC_WaitForSynchro();//等待RTC寄存器同步完成
  RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能RTC秒中断
  RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
//  GPIO_SetBits(GPIOG, GPIO_Pin_14);//点亮D2
  
  NVIC_ConfigurationRTC();
  RTC_Get();//更新时间
}
void RTC_Init(void)
{
//  /*如果是第一次配置时钟，则执行RCC_Configuration()进行配置*/
//  if(BKP_ReadBackupRegister(BKP_DR1)!=0x1016)
//  {
//    RCC_Configuration();
//    RTC_Set(2016,5,11,9,7,55);
//    GPIO_SetBits(GPIOD, GPIO_Pin_13);//点亮D1
//    BKP_WriteBackupRegister(BKP_DR1, 0x1016);//向执行的后备寄存器中写入用户程序数据
//  }
//  else
//  {
//    RTC_WaitForSynchro();//等待RTC寄存器同步完成
//    RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能RTC秒中断
//    RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
//    GPIO_SetBits(GPIOG, GPIO_Pin_14);//点亮D2
//  }
  
  RTC_WaitForSynchro();//等待RTC寄存器同步完成
  RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能RTC秒中断
  RTC_WaitForLastTask();//等待最近一次对RTC寄存器的写操作完成
//  GPIO_SetBits(GPIOG, GPIO_Pin_14);//点亮D2
  
  NVIC_ConfigurationRTC();
  RTC_Get();//更新时间
}
u8 Is_Leap_Year(u16 pyear)
{
  if(pyear%4==0)//首先需能被4整除
  {
    if(pyear%100==0)
    {
        if(pyear%400==0)    return 1;//如果以00结尾，还要能被400整除
        else    return 0;
    }
    else
        return 1;
  }
  else
    return 0;
}
/*
*设置时钟
*把输入的时钟转换为秒钟
*以1970年1月1日为基准
*1970~2099年为合法年份
返回值：0，成功；其它：错误
*/
u8 RTC_Set(u16 year,u8 mon,u8 day,u8 hour,u8 min,u8 sec)
{
    u16 t;
    u32 secCount=0;
    if(year<1970||year>2099)
        return 1;//3?′í
    for(t=1970;t<year;t++)    //把所有年份的秒钟相加
    {
        if(Is_Leap_Year(t))//闰年
            secCount+=31622400;//闰年的秒钟数
        else
            secCount+=31536000;    
    }
    mon-=1;//先减掉一个月再算秒数（如现在是5月10日，则只需要算前4个月的天数，再加上10天，然后计算秒数）
    for(t=0;t<mon;t++)
    {
        secCount+=(u32)mon_table[t]*86400;//月份秒钟数相加
        if(Is_Leap_Year(year)&&t==1)
            secCount+=86400;//闰年，2月份增加一天的秒钟数
    }
    
    secCount+=(u32)(day-1)*86400;//把前面日期的秒钟数相加（这一天还没过完，所以-1）
    secCount+=(u32)hour*3600;//小时秒钟数
    secCount+=(u32)min*60;//分钟秒钟数
    secCount+=sec;
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR    | RCC_APB1Periph_BKP,ENABLE);
//    PWR_BackupAccessCmd(ENABLE);
    RTC_SetCounter(secCount);//设置RTC计数器的值
    RTC_WaitForLastTask();    //等待最近一次对RTC寄存器的写操作完成
    RTC_Get();//更新时间
    return 0;
}

/*
得到当前的时间
成功返回0，错误返回其它
*/
u8 RTC_Get(void)
{
  static u16 dayCount=0;
  u32 secCount=0;
  u32 tmp=0;
  u16 tmp1=0;
  secCount=RTC_GetCounter();
  tmp=secCount/86400;//得到天数
  if(dayCount!=tmp)//超过一天
  {
    dayCount=tmp;
    tmp1=1970;//从1970年开始
    while(tmp>=365)
    {
      if(Is_Leap_Year(tmp1))//是闰年
      {
          if(tmp>=366)    
              tmp-=366;//减掉闰年的天数
          else
          {
          //    tmp1++;
              break;
          }
      }
      else
          tmp-=365;//平年
      tmp1++;
    }
    calendar.w_year=tmp1;//得到年份
    tmp1=0;
    while(tmp>=28)//超过一个月
    {
      if(Is_Leap_Year(calendar.w_year)&&tmp1==1)  //当年是闰年且轮循到2月
      {
          if(tmp>=29)    
              tmp-=29;
          else
              break;
      }
      else
      {
          if(tmp>=mon_table[tmp1])//平年
              tmp-=mon_table[tmp1];
          else
              break;
      }
      tmp1++;
    }
    calendar.w_month=tmp1+1;//得到月份，tmp1=0表示1月，所以要加1
    calendar.w_date=tmp+1;    //得到日期，因为这一天还没过完，所以tmp只到其前一天，但是显示的时候要显示正常日期
  }
  tmp=secCount%86400;//得到秒钟数
  calendar.hour=tmp/3600;//小时
  calendar.min=(tmp%3600)/60;//分钟
  calendar.sec=(tmp%3600)%60;//秒
  return 0;
}
/*
RTC时钟中断
每秒触发一次
*/
void RTC_IRQHandler(void)
{         
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//秒钟中断
    {                            
        RTC_Get();//更新时间
      
     }
    if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)//闹钟中断
    {
        RTC_ClearITPendingBit(RTC_IT_ALR);//清闹钟中断        
  }                                                    
    RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);//清闹钟中断
    RTC_WaitForLastTask();                                                   
}


