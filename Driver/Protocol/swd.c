#include "swd.h"

#include "stdint.h"
//#include "errors.h"
//#include "stdbool.h"

#include "debug_cm.h"


#ifndef SWD_DEBUG
#define SWD_DEBUG       0
#endif

#if (SWD_DEBUG == 1)
#include "stdio.h"
#define SWD_TRACE   printf
#else
#define SWD_TRACE(...)
#endif

/*  以下寄存器具体功能参见权威指南  */
/*  SCB_Type
#define CPUID 0xE000ED00//CPUID寄存器
#define ICSR  0xE000ED04//中断控制及状态寄存器
#define VTOR  0xE000ED08//向量表偏移量寄存器
#define AIRCR 0xE000ED0C//应用程序中断及复位控制寄存器
*/
#define DHCSR 0xE000EDF0 	//调试停机控制及状态寄存器    R/W
#define DCRSR 0xE000EDF4 	//调试内核寄存器选择者寄存器   W
#define DCRDR 0xE000EDF8 	//调试内核寄存器数据寄存器    R/W
#define DEMCR 0xE000EDFC	//调试及监视器控制寄存器       R/W
/***     -END-           **/

#define REGWnR (1 << 16)

#define MAX_TIMEOUT 1

/* Read 32-bit word from target memory. */
// AP CSW register, base value
#define CSW_VALUE (CSW_RESERVED | CSW_MSTRDBG | CSW_HPROT | CSW_DBGSTAT | CSW_SADDRINC)

/*******************************************************************************
*函数名			:	SWD_TransRequest
*功能描述		:	发送起始请求
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char SWD_TransRequest(unsigned char request)
{
	unsigned char ack 		= 0;
	unsigned char bit 		= 0;
	unsigned char parity	=	0;
	unsigned char num 		= 0;
  unsigned char temp 		= 0;
  SWJRequestDef *Request=(SWJRequestDef*)&request;
  
  request=request<<1;
	//=============计算校验位：request低4位1的个数为奇数校验为1，否则为0
  temp  = request&0x0F;
	for(num=0;num<4;num++)
	{
    parity  += temp&0x01;
    temp>>=1;
  }
  Request->Start  = 0x01;
  Request->Parity = parity&0x01;  
  Request->Stop   = 0x00;
  Request->Park   = 0x01;
  
	SWDIO_SET_OUTPUT();		//SWDIO设置为输出
	SWDIO_SET();//SWDIO_OUT(1)
  SWDIO_CLR();//SWDIO_OUT(0)
  SWDIO_SET();//SWDIO_OUT(1)
	/* Packet Request */
	SW_WRITE_BIT(Request->Start);     /* Start Bit */		//起始位：值为1
	SW_WRITE_BIT(Request->APnDP);     /* APnDP Bit */		//寄存器访问方式：0-DPACC访问，1-APACC访问
	SW_WRITE_BIT(Request->RnW);       /* RnW Bit */			//读写位：0-写，1-读
	SW_WRITE_BIT(Request->Addr0);     /* Addr2 Bit */				//DP或者AP寄存器的地址区域，低位先发送--低位
	SW_WRITE_BIT(Request->Addr1);     /* Addr3 Bit */				//DP或者AP寄存器的地址区域，低位先发送--高位
	SW_WRITE_BIT(Request->Parity);    /* Parity Bit */		//奇偶校验位：0-APnDP到Addr中1的个数为偶数；1--APnDP到Addr中1的个数为奇数
	SW_WRITE_BIT(Request->Stop);      /* Stop Bit */			//停止位：值为0
	SW_WRITE_BIT(Request->Park);      /* Park Bit */			//单一位：传输该位时，主机拉高然后不再驱动该位
  
	SWDIO_SET_INPUT();			//SWDIO设置为输入

	/* Turnaround */
	//    for(n = 1; n; n--)
	//    {
	//        SW_CLOCK_CYCLE();
	//    }
	SW_CLOCK_CYCLE();
	/* Acknowledge response */	//读应答
	for(num = 0; num < 3; num++)
	{
			bit = SW_READ_BIT();		//读一位数据
			ack  |= bit << num;
	}
	return ack;
}

/*******************************************************************************
*函数名			:	SWD_TransferOnce
*功能描述		:	单次传输：读/写传输
*输入				: request-请求参数；*data-读数据时为保存数据指针，写数据时为待写入的数据
*返回值			:	ack 状态
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char SWD_TransferOnce(unsigned long request, unsigned long *data)
{
    unsigned long ack = 0;
    unsigned long bit;
    unsigned long val;
    unsigned long parity;
    unsigned long n;

		ack = SWD_TransRequest(request);
  
    switch(ack)
    {
        case DAP_TRANSFER_OK:			//应答OK，根据请求类型执行相应操作
						//读数据请求
            if(request & DAP_TRANSFER_RnW)  /* read data */
            {
                val = 0;
                parity = 0;

                for(n = 32; n; n--)
                {
                    bit = SW_READ_BIT();  /* Read RDATA[0:31] */
                    parity += bit;
                    val >>= 1;
                    val  |= bit << 31;
                }

                bit = SW_READ_BIT();    /* Read Parity */

                if((parity ^ bit) & 1)
                {
                    ack = DAP_TRANSFER_ERROR;		//0x08传输错误--校验错误	
                }

                if(data) 
									*data = val;

                /* Turnaround */
                for(n = 1; n; n--)
                {
                    SW_CLOCK_CYCLE();
                }

                SWDIO_SET_OUTPUT();		//SWDIO设置为输出
            }
						//写数据请求
            else    /* write data */
            {
                /* Turnaround */
                for(n = 1; n; n--)
                {
                    SW_CLOCK_CYCLE();
                }

                SWDIO_SET_OUTPUT();	//SWDIO设置为输出
                /* Write data */
                val = *data;
                parity = 0;

                for(n = 32; n; n--)
                {
                    SW_WRITE_BIT(val); /* Write WDATA[0:31] */
                    parity += val;
                    val >>= 1;
                }

                SW_WRITE_BIT(parity);/* Write Parity Bit */
            }

            /* Idle cycles */
            SWDIO_SET_OUTPUT();		//SWDIO设置为输出
            
            for(n = 0; n < 8; n++)
            {
                SW_WRITE_BIT(0);
            }
						SWDIO_SET();
            return (ack);

        case DAP_TRANSFER_WAIT:
        case DAP_TRANSFER_FAULT:

            /* WAIT or FAULT response */
            if(0 && ((request & DAP_TRANSFER_RnW) != 0))
            {
                for(n = 32 + 1; n; n--)
                {
                    SW_CLOCK_CYCLE();  /* Dummy Read RDATA[0:31] + Parity */
                }
            }

            /* Turnaround */
            for(n = 1; n; n--)
            {
                SW_CLOCK_CYCLE();
            }

            SWDIO_SET_OUTPUT();		//SWDIO设置为输出

            if(0 && ((request & DAP_TRANSFER_RnW) == 0))
            {
                SWCLK_CLR();

                for(n = 32 + 1; n; n--)
                {
                    SW_CLOCK_CYCLE();  /* Dummy Write WDATA[0:31] + Parity */
                }
            }

            SWDIO_SET();
            for(n = 0; n < 8; n++)
            {
                SW_WRITE_BIT(0);
            }
            return (ack);

        default:
            break;
    }

    /* Protocol error */
    for(n = 1 + 32 + 1; n; n--)
    {
        SW_CLOCK_CYCLE();      /* Back off data phase */
    }

    SWDIO_SET_OUTPUT();		//SWDIO设置为输出
    
    for(n = 0; n < 8; n++)
    {
        SW_WRITE_BIT(0);
    }
		SWDIO_SET();
    return (ack);
}
/*******************************************************************************
*函数名			:	SWD_Transfer
*功能描述		:	数据传输-读写，失败时在最大重试范围内重试
*输入				: request-请求参数；*data-读数据时为保存数据指针，写数据时为待写入的数据
*返回值			:	ack 状态
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char SWD_Transfer(unsigned long request, unsigned long *data)
{
    unsigned char i, ack;

    for(i = 0; i < MAX_SWD_RETRY; i++)
    {
        ack = SWD_TransferOnce(request, data);		//单次传输：读/写传输

        // if ack != WAIT
        if(ack != DAP_TRANSFER_WAIT)
        {
            return ack;
        }
    }
    return ack;
}

//count 时钟个数
//swdio_logic swdio此时状态
/*
static void SWJ_SendClock(unsigned long count, unsigned char swdio_logic)
{
    while(count--)
    {
        SW_WRITE_BIT((swdio_logic) ? (1) : (0));
    }
}
*/
/*******************************************************************************
*函数名			:	SWJ_SendData
*功能描述		:	发送16字节数据
*输入				: request-请求参数；*data-读数据时为保存数据指针，写数据时为待写入的数据
*返回值			:	ack 状态
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
static void SWJ_SendData(uint16_t data)
{
    unsigned char i;

    for(i = 0; i < 16; i++)
    {
        SW_WRITE_BIT(((data & 0x1) == 1) ? (1) : (0));
        data >>= 1;
    }
}
/*******************************************************************************
*函数名			:	Line_Rest
*功能描述		:	线路复位--发送至少50个时钟的DIO-1,这里发56个
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Line_Rest(void)
{
	unsigned long i;
  SWDIO_SET_OUTPUT();
	SWDIO_SET();//SWDIO_OUT(1)
  SWDIO_CLR();//SWDIO_OUT(0)
  SWDIO_SET();//SWDIO_OUT(1)
	for(i = 0; i < 51; i++)
	{
		SW_CLOCK_CYCLE();
	}
	
}

/*******************************************************************************
*函数名			:	SWJ_JTAG2SWD
*功能描述		:	从JTAG切换到SWD模式:
							M3的SWJ-DP接口上电后默认为JTAG-DP
							需要先发送JTAG到SWD的切换命令：至少50个时钟的1,
							然后是16bit的切换序列0xE79E（低位在前）,
							继续发送至少50个时钟的1，令SWD进入线复位状态（line reset）,
							(0x6DB7-老版本ARM的强制切换,为了兼容，两种切换方式都发）,
							最后再发送至少2个0(idle周期),
							然后可以读出IDCODE
*输入				: 
*返回值			:	
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
static unsigned char SWJ_JTAG2SWD(void)
{
    unsigned long i;
	SWDIO_SET_OUTPUT();
	SWDIO_SET();
	//1,需要先发送JTAG到SWD的切换命令：至少50个时钟的1
	Line_Rest();	//线路复位,56个时钟的1
	//2,然后是16bit的切换序列0xE79E（低位在前）强制切换到SWD模式
	SWJ_SendData(0xE79E);//发送16bit的切换序列0xE79E（低位在前）强制切换到SWD模式
	//3,继续发送至少50个时钟的1，令SWD进入线复位状态（line reset）
	Line_Rest();	//线路复位,56个时钟的1
	//2.1,然后是16bit的切换序列0x6DB7（低位在前）老版本ARM强制切换到SWD模式
	SWJ_SendData(0x6DB7);//发送切换序列0x6DB7（低位在前）老版本ARM强制切换到SWD模式
	Line_Rest();	//线路复位,56个时钟的1	
	SWDIO_CLR();
	for(i = 0; i < 16; i++)
	{
			SW_CLOCK_CYCLE();
	}
	SWDIO_SET();//(swdio)PB3输出1
	return 0;
}
/*******************************************************************************
*函数名			:	SWJ_ReadDP
*功能描述		:	读DPACC
*输入				: adr-地址；*val-接收数据指针
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
static unsigned char SWJ_ReadDP(unsigned char adr, unsigned long *val)
{
	unsigned long tmp_in;
	unsigned char ack;
	unsigned char err;

	tmp_in = SWD_REG_DP | SWD_REG_R | SWD_REG_ADR(adr);
	ack = SWD_Transfer(tmp_in, val);

	(ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);
	return err;
}
/*******************************************************************************
*函数名			:	SWJ_WriteDP
*功能描述		:	写DPACC
*输入				: adr-地址；val-待写入数据
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char SWJ_WriteDP(unsigned char adr, unsigned long val)
{
    unsigned long req;
    unsigned char ack;
    unsigned char err;

    req = SWD_REG_DP | SWD_REG_W | SWD_REG_ADR(adr);		//DP访问&写模式&adr
    ack = SWD_Transfer(req, &val);

    (ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);
    return err;
}
/*******************************************************************************
*函数名			:	SWJ_ReadAP
*功能描述		:	读APACC
*输入				: adr-地址；*val-接收数据指针
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char SWJ_ReadAP(unsigned long adr, unsigned long *val)
{
    unsigned char tmp_in, ack, err;

    unsigned long apsel = adr & APSEL;
    unsigned long bank_sel = adr & APBANKSEL;

    if(SWJ_WriteDP(DP_SELECT, apsel | bank_sel))
    {
        return 1;
    }

    tmp_in = SWD_REG_AP | SWD_REG_R | SWD_REG_ADR(adr);

    /* first dummy read */
    ack = SWD_Transfer(tmp_in, val);
    ack = SWD_Transfer(tmp_in, val);

    (ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);
    return err;
}
/*******************************************************************************
*函数名			:	SWJ_WriteAP
*功能描述		:	写APACC
*输入				: adr-地址；val-待写入数据
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char SWJ_WriteAP(unsigned long adr, unsigned long val)
{
    unsigned char req, ack, err;

    unsigned long apsel = adr & APSEL;
    unsigned long bank_sel = adr & APBANKSEL;

    /* write DP select */
    if(SWJ_WriteDP(DP_SELECT, apsel | bank_sel))
    {

    }

    /* write AP data */
    req = SWD_REG_AP | SWD_REG_W | SWD_REG_ADR(adr);
    ack = SWD_Transfer(req, &val);

    /* read DP buff */
    req = SWD_REG_DP | SWD_REG_R | SWD_REG_ADR(DP_RDBUFF);
    ack = SWD_Transfer(req, NULL);
    (ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);

    return err;
}




// Write target memory.
//往目标内存写数据
//1故障 0正常
/*******************************************************************************
*函数名			:	SWJ_WriteData
*功能描述		:	写数据
*输入				: adr-地址；val-待写入数据
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
static unsigned char SWJ_WriteData(unsigned long addr, unsigned long data)
{
    unsigned char req, ack, err;

    SWJ_WriteAP(AP_TAR, addr);

    /* write data */
    req = SWD_REG_AP | SWD_REG_W | AP_DRW;
    ack = SWD_Transfer(req, &data);

    /* read DP buff */
    req = SWD_REG_DP | SWD_REG_R | SWD_REG_ADR(DP_RDBUFF);
    ack = SWD_Transfer(req, NULL);

    (ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);
    return err;
}
/*******************************************************************************
*函数名			:	SWJ_WriteMem8
*功能描述		:	往内存写一个8位数据
*输入				: adr-地址；val-待写入数据
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//往目标内存写数据u8
//1故障 0正常
static unsigned char SWJ_WriteMem8(unsigned long addr, unsigned char val)
{
    unsigned long tmp;
    unsigned char err;

    SWJ_WriteAP(AP_CSW, CSW_VALUE | CSW_SIZE8);

    tmp = val << ((addr & 0x03) << 3);
    err = SWJ_WriteData(addr, tmp);
    return err;
}
/*******************************************************************************
*函数名			:	SWJ_WriteMem32
*功能描述		:	往内存写一个32位数据
*输入				: adr-地址；val-待写入数据
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//往目标内存写数据u32
//1故障 0正常
unsigned char SWJ_WriteMem32(unsigned long addr, unsigned long val)
{
    unsigned char err;

    SWJ_WriteAP(AP_CSW, CSW_VALUE | CSW_SIZE32);
    err = SWJ_WriteData(addr, val);
    return err;
}

/*******************************************************************************
*函数名			:	SWJ_WriteBlock
*功能描述		:	块写入
*输入				: adr-地址；buf-待写入数据起始地址，len-待写入的数据长度
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
// Write 32-bit word aligned values to target memory using address auto-increment.
// size is in bytes.
//
//1故障 0正常
static unsigned char SWJ_WriteBlock(unsigned long addr, unsigned char *buf, unsigned long len)
{
    unsigned char err, req;
    unsigned long size_in_words;
    unsigned long i, ack;

    if(len == 0)  return 0;

    err = 0;
    size_in_words = len / 4;


    err += SWJ_WriteAP(AP_CSW, CSW_VALUE | CSW_SIZE32);

    if(err)
    {
        //SWD_TRACE("AP_CSW, CSW_VALUE | CSW_SIZE32 failed\r\n");
    }

    err += SWJ_WriteAP(AP_TAR, addr);

    if(err) return err;

    /* DRW write */
    req = SWD_REG_AP | SWD_REG_W | (3 << 2);

    for(i = 0; i < size_in_words; i++)
    {
        if(SWD_Transfer(req, (unsigned long *)buf) != DAP_TRANSFER_OK)
        {
            return 1;
        }

        buf += 4;
    }

    /* read DP buff */
    req = SWD_REG_DP | SWD_REG_R | SWD_REG_ADR(DP_RDBUFF);
    ack = SWD_Transfer(req, NULL);

    (ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);
    return 0;
}
/*******************************************************************************
*函数名			:	SWJ_ReadData
*功能描述		:	读数据
*输入				: adr-地址；val-读取的数据存储地址
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
// Read target memory.
//往目标内存读数据
//1故障 0正常
static unsigned char SWJ_ReadData(unsigned long addr, unsigned long *val)
{
    unsigned char req, ack, err;

    SWJ_WriteAP(AP_TAR, addr);

    /* read data */
    req = SWD_REG_AP | SWD_REG_R | AP_DRW;
    ack = SWD_Transfer(req, val);

    /* dummy read */
    req = SWD_REG_DP | SWD_REG_R | SWD_REG_ADR(DP_RDBUFF);
    ack = SWD_Transfer(req, val);

    (ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);
    return err;
}
/*******************************************************************************
*函数名			:	SWJ_ReadMem32
*功能描述		:	从内存读一个32位数据
*输入				: adr-地址；val-读取的数据存储地址
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//往目标内存读数据u32
//1故障 0正常
static unsigned char SWJ_ReadMem32(unsigned long addr, unsigned long *val)
{
    unsigned char err;
    SWJ_WriteAP(AP_CSW, CSW_VALUE | CSW_SIZE32);
    err = SWJ_ReadData(addr, val);
    return err;
}
/*******************************************************************************
*函数名			:	SWJ_ReadMem8
*功能描述		:	从内存读一个8位数据
*输入				: adr-地址；val-读取的数据存储地址
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//往目标内存读数据u8
//1故障 0正常
static unsigned char SWJ_ReadMem8(unsigned long addr, unsigned char *val)
{
    unsigned long tmp;
    unsigned char err;

    SWJ_WriteAP(AP_CSW, CSW_VALUE | CSW_SIZE8);

    err = SWJ_ReadData(addr, &tmp);

    *val = (unsigned char)(tmp >> ((addr & 0x03) << 3));

    return err;
}
/*******************************************************************************
*函数名			:	SWJ_ReadBlock
*功能描述		:	块读取
*输入				: adr-地址；buf-读取的数据存储起始地址，len-待读取的数据长度
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
// Read 32-bit word aligned values from target memory using address auto-increment.
// size is in bytes.
//往目标内存读数据
//1故障 0正常
static unsigned char SWJ_ReadBlock(unsigned long addr, unsigned char *buf, unsigned long len)
{
    unsigned char err, req;
    unsigned long size_in_words;
    unsigned long i, ack;

    if(len == 0)  return 0;

    err = 0;
    size_in_words = len / 4;


    err += SWJ_WriteAP(AP_CSW, CSW_VALUE | CSW_SIZE32);
    err += SWJ_WriteAP(AP_TAR, addr);

    if(err) return err;

    req = SWD_REG_AP | SWD_REG_R | (3 << 2);

    /* dummy read */
    if(SWD_Transfer(req, (unsigned long *)buf) != 0x01)
    {
        return 1;
    }

    for(i = 0; i < size_in_words; i++)
    {
        if(SWD_Transfer(req, (unsigned long *)buf) != DAP_TRANSFER_OK)
        {
            return 1;
        }

        buf += 4;
    }

    /* read DP buff */
    req = SWD_REG_DP | SWD_REG_R | SWD_REG_ADR(DP_RDBUFF);
    ack = SWD_Transfer(req, NULL);

    (ack == DAP_TRANSFER_OK) ? (err = 0) : (err = 1);
    return err;
}

#define TARGET_AUTO_INCREMENT_PAGE_SIZE    (0x400)
/*******************************************************************************
*函数名			:	swd_write_memory
*功能描述		:	写寄存器
*输入				: adr-地址；buf-读取的数据存储起始地址，len-待读取的数据长度
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
// Write unaligned data to target memory.
// size is in bytes.
//往目标内存写数据
//1故障 0正常
unsigned char swd_write_memory(unsigned long address, unsigned char *data, unsigned long size)
{
    unsigned long n;

    // Write bytes until word aligned
    while((size > 0) && (address & 0x3))
    {
        SWJ_WriteMem8(address, *data);
        address++;
        data++;
        size--;
    }

    // Write word aligned blocks
    while(size > 3)
    {
        // Limit to auto increment page size
        n = TARGET_AUTO_INCREMENT_PAGE_SIZE - (address & (TARGET_AUTO_INCREMENT_PAGE_SIZE - 1));

        if(size < n)
        {
            n = size & 0xFFFFFFFC; // Only count complete words remaining
        }

        if(SWJ_WriteBlock(address, data, n))
        {
            SWD_TRACE("SWJ write block failed\r\n");
            return 1;
        }

        address += n;
        data += n;
        size -= n;
    }

    // Write remaining bytes
    while(size > 0)
    {
        SWJ_WriteMem8(address, *data);

        address++;
        data++;
        size--;
    }

    return 0;
}
/*******************************************************************************
*函数名			:	swd_read_memory
*功能描述		:	读寄存器
*输入				: adr-地址；buf-读取的数据存储起始地址，len-待读取的数据长度
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
// Read unaligned data from target memory.
// size is in bytes.
//往目标内存读数据
//1故障 0正常
unsigned char swd_read_memory(unsigned long address, unsigned char *data, unsigned long size)
{
    unsigned long n;

    // Read bytes until word aligned
    while((size > 0) && (address & 0x3))
    {
        SWJ_ReadMem8(address, data);
        address++;
        data++;
        size--;
    }

    // Read word aligned blocks
    while(size > 3)
    {
        // Limit to auto increment page size
        n = TARGET_AUTO_INCREMENT_PAGE_SIZE - (address & (TARGET_AUTO_INCREMENT_PAGE_SIZE - 1));

        if(size < n)
        {
            n = size & 0xFFFFFFFC; // Only count complete words remaining
        }

        if(SWJ_ReadBlock(address, data, n))
        {
            return 1;
        }

        address += n;
        data += n;
        size -= n;
    }

    // Read remaining bytes
    while(size > 0)
    {
        SWJ_ReadMem8(address, data);
        address++;
        data++;
        size--;
    }

    return 0;
}
/*******************************************************************************
*函数名			:	SWJ_ReadMem
*功能描述		:	从目标内存读数据
*输入				: adr-地址；buf-读取的数据存储起始地址，len-待读取的数据长度
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//从目标内存读数据
//1故障 0正常
unsigned char SWJ_ReadMem(unsigned long addr, unsigned char *buf, unsigned long len)
{
    return swd_read_memory(addr, buf, len);
}
/*******************************************************************************
*函数名			:	SWJ_WriteMem
*功能描述		:	往目标内存写数据
*输入				: adr-地址；buf-读取的数据存储起始地址，len-待读取的数据长度
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//往目标内存写数据
//1故障 0正常
unsigned char SWJ_WriteMem(unsigned long addr, unsigned char *buf, unsigned long len)
{
    return swd_write_memory(addr, buf, len);
}

/*******************************************************************************
*函数名			:	SWJ_WaitUntilHalted
*功能描述		:	等目标Halt
*输入				: 
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//等目标Halt
//1故障 0正常
static unsigned char SWJ_WaitUntilHalted(void)
{
    // Wait for target to stop
    unsigned long val, i, timeout = MAX_TIMEOUT;

    for(i = 0; i < timeout; i++)
    {

        if(SWJ_ReadMem32(DBG_HCSR, &val))
        {
            return 1;
        }

        if(val & S_HALT)
        {
            return 0;
        }
    }

    return DAP_TRANSFER_ERROR;		//0x08传输错误--校验错误	
}
/*******************************************************************************
*函数名			:	SWJ_SetTargetState
*功能描述		:	设置目标状态
*输入				: 
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//设置目标复位状态
//1故障 0正常
unsigned char SWJ_SetTargetState(TARGET_RESET_STATE state)
{
    switch(state)
    {
        case RESET_HOLD:
            RESET_CLR();		//REST	=	LOW
            break;

        case RESET_RUN:	
            RESET_CLR();		//REST	=	LOW
            DELAY_US(20 * 1000);
            RESET_SET();		//REST	=	HIGH
            DELAY_US(20 * 1000);
            break;

        case RESET_PROGRAM:
            RESET_CLR();		//REST	=	LOW
            DELAY_US(20);
            //   RESET_SET();
            //   DelayMs(20);

            SWJ_InitDebug();

            // Enable debug
            SWJ_WriteMem32(DBG_HCSR, DBGKEY | C_DEBUGEN);

            // Enable halt on reset
            SWJ_WriteMem32(DBG_EMCR, VC_CORERESET);

            // Reset again
            RESET_CLR();		//REST	=	LOW
            DELAY_US(20 * 1000);
            RESET_SET();		//REST	=	HIGH

            break;

        default:
            break;
    }

    return 0;
}
/*******************************************************************************
*函数名			:	SWJ_WriteCoreReg
*功能描述		:	写目标内核寄存器
*输入				: 
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//写目标核寄存器
//1故障 0正常
static unsigned char SWJ_WriteCoreReg(unsigned long n, unsigned long val)
{
    int i = 0, timeout = MAX_TIMEOUT;

    SWJ_WriteMem32(DCRDR, val);

    SWJ_WriteMem32(DCRSR, n | REGWnR);

    // wait for S_REGRDY
    for(i = 0; i < timeout; i++)
    {
        SWJ_ReadMem32(DHCSR, &val);

        if(val & S_REGRDY)
        {
            return 0;
        }
    }

    return 1;
}
/*******************************************************************************
*函数名			:	SWJ_ReadCoreReg
*功能描述		:	读目标内核寄存器
*输入				: 
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//读目标核寄存器
//1故障 0正常
static unsigned char SWJ_ReadCoreReg(unsigned long n, unsigned long *val)
{
    int i = 0, timeout = MAX_TIMEOUT, err;

    if(SWJ_WriteMem32(DCRSR, n))
        return 1;

    // wait for S_REGRDY
    for(i = 0; i < timeout; i++)
    {

        if(SWJ_ReadMem32(DHCSR, val))
            return 1;

        if(*val & S_REGRDY)
            break;
    }

    if(i == timeout)
        return 1;

    err = SWJ_ReadMem32(DCRDR, val);

    return err;
}
/*******************************************************************************
*函数名			:	swd_write_debug_state
*功能描述		:	写debug状态
*输入				: 
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//写debug状态
//1故障 0正常
unsigned char swd_write_debug_state(DEBUG_STATE *state)
{
    unsigned long i, status;

    SWJ_WriteDP(DP_SELECT, 0);

    // R0, R1, R2, R3
    for(i = 0; i < 4; i++)
    {
        SWJ_WriteCoreReg(i, state->r[i]);
    }

    // R9
    SWJ_WriteCoreReg(9, state->r[9]);

    // R13, R14, R15
    for(i = 13; i < 16; i++)
    {
        SWJ_WriteCoreReg(i, state->r[i]);
    }

    // xPSR
    SWJ_WriteCoreReg(16, state->xpsr);
    SWJ_WriteMem32(DBG_HCSR, DBGKEY | C_DEBUGEN);

    // check status
    SWJ_ReadDP(DP_CTRL_STAT, &status);

    if(status & (STICKYERR | WDATAERR))
    {
        SWD_TRACE("write debug states failed\r\n");
        return 1;
    }

    return 0;
}
/*******************************************************************************
*函数名			:	swd_flash_syscall_exec
*功能描述		:	flash状态回读
*输入				: 
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//flash状态回读????????????????????
//1故障 0正常
unsigned char swd_flash_syscall_exec(const FLASH_SYSCALL *sysCallParam, unsigned long entry, unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4)
{
    DEBUG_STATE state;

    // Call flash algorithm function on target and wait for result.
    state.xpsr     = 0x01000000;          // xPSR: T = 1, ISR = 0
    state.r[0]     = arg1;                   // R0: Argument 1
    state.r[1]     = arg2;                   // R1: Argument 2
    state.r[2]     = arg3;                   // R2: Argument 3
    state.r[3]     = arg4;                   // R3: Argument 4

    state.r[9]     = sysCallParam->static_base;    // SB: Static Base

    state.r[13]    = sysCallParam->stack_pointer;  // SP: Stack Pointer
    state.r[14]    = sysCallParam->breakpoint;       // LR: Exit Point
    state.r[15]    = entry;                           // PC: Entry Point

    if(swd_write_debug_state(&state))
    {
        SWD_TRACE("swd_write_debug_status failed\r\n");
        return 1;
    }

    if(SWJ_WaitUntilHalted())
    {
        SWD_TRACE("SWJ_WaitUntilHalted failed\r\n");
        return 1;
    }

    if(SWJ_ReadCoreReg(0, &state.r[0]))
    {
        SWD_TRACE("SWJ_ReadCoreReg failed\r\n");
        return 1;
    }


    // Flash functions return 0 if successful.
    if(state.r[0] != 0)
    {
        SWD_TRACE("resutlt failed:0x%X\r\n", state.r[0]);
        return 1;
    }

    return 0;
}
/*******************************************************************************
*函数名			:	SWJ_InitDebug
*功能描述		:	将设备JTAG/SWD状态初始化
*输入				: 
*返回值			:	err
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//将设备JTAG/SWD状态初始化
//1故障 0正常
unsigned char SWJ_InitDebug(void)
{
  unsigned long tmp = 0;
  unsigned long val;
  unsigned char ack;
    /*JTAG 转到 SWD*/
    SWJ_JTAG2SWD();
	
    if(SWJ_ReadDP(DP_IDCODE, &val))		//读DPACC
    {
        return 1;
    }
		
    SWD_TRACE("DP_IDCODE:0x%X\r\n", val);

    SWJ_WriteDP(DP_ABORT, STKCMPCLR	|	STKERRCLR	|	WDERRCLR	|	ORUNERRCLR);

    /* Ensure CTRL/STAT register selected in DPBANKSEL */
    //SWJ_WriteDP(DP_SELECT, 0);

    /* Power ups */
    SWJ_WriteDP(DP_CTRL_STAT, CSYSPWRUPREQ | CDBGPWRUPREQ);   // System Power-up Request  // Debug Power-up Request
    
    //等待上电成功
    do
    { 
        ack = SWJ_ReadDP(DP_CTRL_STAT, &tmp);
        if(0!=ack)
        {
            return 0;
        }
    }
    while((tmp & (CDBGPWRUPACK | CSYSPWRUPACK)) != (CDBGPWRUPACK | CSYSPWRUPACK));

    SWJ_WriteDP(DP_CTRL_STAT, CSYSPWRUPREQ | CDBGPWRUPREQ | TRNNORMAL | MASKLANE);
		
		SWDIO_SET_OUTPUT();
		SWDIO_SET();
    return 0;
}

void softdelay(unsigned long us)
{
    volatile unsigned long i, j;

    for(i = 0; i < us; i++)
    {
        for(j = 0; j < 30U; j++)
        {
            __nop();
        }
    }
}
unsigned long sss[10];
void test(void)
{
	unsigned long i = 10, val;
	
    SWDIO_SET_OUTPUT();		//SWDIO设置为输出
    SWCLK_SET_OUTPUT();		//SWCLK设置为输出

    SWCLK_CLR();
    SWDIO_SET();

    
    SWJ_InitDebug();

    while(i--)
    {
        SWJ_ReadDP(DP_IDCODE, &val);
        sss[i] = val;


        softdelay(100);
        //SWJ_WriteAP(0XAA,0X55);
        //SWJ_InitDebug();
    }
    while(1);
}
