#ifndef __SWD_H__
#define __SWD_H__

#include "swd_pin.h"
#include "stdint.h"
#include "debug_cm.h"

//================================================低位先传

//================================================专业术语
/*

DPACC		Debug Port accesses 		调试端口访问
APACC		Access Port accesses		访问端口访问

SELECT	AP Select register			AP选择寄存器

*/

//================================================MEM-AP registers 内存访问端口寄存器
/*

CSW					Control/Status Word register			控制/状态字寄存器
TAR					Transfer Address Register					传输地址寄存器
DRW					Data Read/Write register					数据读/写寄存器
BD0 to BD3	Banked Data Registers							存储数据寄存器
CFG					Configuration register						配置寄存器
BASE				Debug Base Address register				调试基地址寄存器
IDR					Identification Register						设备识别寄存器

*/
#define ERROR                           1
#define SUCCESS                         0
#define MAX_SWD_RETRY   								1				//最大重试次数

// DAP Transfer Response
#define DAP_TRANSFER_OK                 (1<<0)	//0x01正常
#define DAP_TRANSFER_WAIT               (1<<1)	//0x02等待
#define DAP_TRANSFER_FAULT              (1<<2)	//0x04失败
#define DAP_TRANSFER_ERROR              (1<<3)	//0x08传输错误--校验错误	
#define DAP_TRANSFER_MISMATCH           (1<<4)
#define DAP_TRANSFER_TIMEOUT            (1<<5)

/*debug_cm.h已经定义
 Debug Port Register Addresses
#define DP_IDCODE                       0x00    // IDCODE Register (SW Read only)
#define DP_ABORT                        0x00    // Abort Register (SW Write only)
#define DP_CTRL_STAT                    0x04    // Control & Status
#define DP_WCR                          0x04    // Wire Control Register (SW Only)
#define DP_SELECT                       0x08    // Select Register (JTAG R/W & SW W)
#define DP_RESEND                       0x08    // Resend (SW Read Only)
#define DP_RDBUFF                       0x0C    // Read Buffer (Read Only)
*/

// DAP Transfer Request			//传输请求
#define DAP_TRANSFER_APnDP              (1<<0)
#define DAP_TRANSFER_RnW                (1<<1)	//读写位：0-写，1-读
#define DAP_TRANSFER_A2                 (1<<2)
#define DAP_TRANSFER_A3                 (1<<3)
#define DAP_TRANSFER_MATCH_VALUE        (1<<4)
#define DAP_TRANSFER_MATCH_MASK         (1<<5)

// SWD register access	//寄存器访问方式及地址
#define SWD_REG_AP        (1)					//1-APACC访问
#define SWD_REG_DP        (0)					//0-DPACC访问
#define SWD_REG_R        	(1<<1)			//读写位：0-写，1-读
#define SWD_REG_W        	(0<<1)			//读写位：0-写，1-读
#define SWD_REG_ADR(a)    (a & 0x0c)	//DP或者AP寄存器的地址区域，低位先发送


//低位先传
typedef enum
{
	SWJAckOK		=	0x01,		//OK
	SWJAckWait	=	0x02,		//Wait
	SWJAckFault	=	0x04		//Fault
}SWJAckDef;
typedef struct _SWJKey
{
	unsigned char Start 	:1;			//起始位：值为1
	unsigned char APnDP 	:1;			//寄存器访问方式：0-DPACC访问，1-APACC访问
	unsigned char RnW 		:1;			//读写位：0-写，1-读
	unsigned char Addr 		:2;			//DP或者AP寄存器的地址区域，低位先发送
	unsigned char Parity 	:1;			//奇偶校验位：0-APnDP到Addr中1的个数为偶数；1--APnDP到Addr中1的个数为奇数
	unsigned char Stop 		:1;			//停止位：值为0
	unsigned char Park	 	:1;			//单一位：传输该位时，主机拉高然后不再驱动该位
}SWJKeyDef;


/*debug_cm.h已经定义
 Debug Select Register definitions
#define CTRLSEL        0x00000001  // CTRLSEL (SW Only)
#define APBANKSEL      0x000000F0  // APBANKSEL Mask
#define APSEL          0xFF000000  // APSEL Mask
*/


typedef enum
{
    RESET_HOLD,              // Hold target in reset
    RESET_PROGRAM,           // Reset target and setup for flash programming.
    RESET_RUN,               // Reset target and run normally
    RESET_RUN_WITH_DEBUG,    // Reset target and run with debug enabled (required for semihost)
    disDEBUG,                // Disable debug on running target
    enDEBUG                  // Enable debug on running target
} TARGET_RESET_STATE;

typedef struct
{
	unsigned long breakpoint;
	unsigned long static_base;
	unsigned long stack_pointer;
}FLASH_SYSCALL;

#ifndef BSWAP_32//将u32 0xAABBCCDD 变为 0xDDCCBBAA   此处未使用
#define BSWAP_32(val)   (unsigned long)((BSWAP_16((unsigned long)(val) & (unsigned long)0xFFFF) << 0x10) |  (BSWAP_16((unsigned long)((val) >> 0x10))))
#endif

#ifndef BSWAP_16//将u16 0xAABB  变为 0xBBAA   此处未使用
#define BSWAP_16(x)     (unsigned short)((((x) & 0xFF00) >> 0x8) | (((x) & 0xFF) << 0x8))
#endif

#ifndef NULL
#define NULL    0
#endif


//!< API
unsigned char SWJ_ReadDP(unsigned char adr, unsigned long *val);
unsigned char SWJ_WriteDP(unsigned char adr, unsigned long val);
unsigned char SWJ_ReadAP(unsigned long adr, unsigned long *val);
unsigned char SWJ_WriteAP(unsigned long adr, unsigned long val);
unsigned char SWJ_InitDebug(void);
unsigned char SWJ_ReadMem(unsigned long addr, unsigned char *buf, unsigned long len);
unsigned char SWJ_WriteMem(unsigned long addr, unsigned char *buf, unsigned long len);
unsigned char SWJ_SetTargetState(TARGET_RESET_STATE state);
unsigned char swd_flash_syscall_exec(const FLASH_SYSCALL *sysCallParam, unsigned long entry,unsigned long arg1,unsigned long arg2, unsigned long arg3, unsigned long arg4);




#endif
