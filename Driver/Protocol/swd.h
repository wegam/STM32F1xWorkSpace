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

*/
#define ERROR                           1
#define SUCCESS                         0
#define MAX_SWD_RETRY   								5				//最大重试次数

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
typedef enum	_AddrInc
{
	AddrIncOff		=	0x00,		//地址自增关闭，在任何数据读/写寄存器访问之后，在TAR中的值不变。
	AddrIncSingle	=	0x01,		//在成功的数据读/写寄存器访问之后，在TAR中的地址按访问的大小递增。
	AddrIncPacked	=	0x02		//打包传输，暂未理解
}AddrIncDef;

typedef enum	_CswSize	//访问地址宽度
{
	SizeByte		=	0x00,		//Byte (8-bits)
	Halfword		=	0x01,		//(16-bits)
	SizeWord		=	0x02,		//(32-bits)
	Doubleword	=	0x03,		//(64-bits)
	Size128Bit	=	0x04,		//(128-bits)
	Size256Bit	=	0x05		//(256-bits)
}CswSizeDef;
typedef enum	_TrnMode	//Transfer mode（传输模式)
{
	TrnNormal		=	0x00,		//Normal operation.(普通)
	Trnverify		=	0x01,		//Pushed-verify operation.（...验证）
	Trncompare	=	0x02,		//Pushed-compare operation.（...比较）
	TrnReserved	=	0x03		//Reserved.
}TrnModeDef;

typedef struct _MEMAPCSW		//Control/Status Word register(MEM-AP)
{
	unsigned long	Size					:3;			//Bit[2:0]地址访问字段大小，暂理解为数据位宽，查看 _CswSize
	unsigned long	Reserved0			:1;			//Bit[3]Reserved0
	unsigned long	AddrInc				:2;			//Bit[5:4]地址自增控制，查看 _AddrInc
	unsigned long DeviceEn 			:1;			//Bit[6]Device enabled.
	unsigned long TrInProg 			:1;			//Bit[7]Transfer in progress:传输状态，只读位，0-空闲，可以传输；1-忙，正在传输数据
	unsigned long Mode 					:4;			//Bit[11:8]Mode of operation:操作模式，0-基本模式，常规使用方式；1-Barrier support enabled，不了解，没找到使用
	unsigned long Type 					:4;			//Bit[15:12]See the entry for {Prot}.bits[30:24]
	unsigned long Bits					:7;			//Bit[22:16]Reserved1
	unsigned long SPIDEN				:1;			//Bit[23]0-禁止安全访问；1-使能安全访问
	unsigned long Prot					:7;			//Bit[30:24]Debug software access enable
	unsigned long DbgSwEnable		:1;			//Bit[31]Debug software access enable	
}MEMAPCSWDef;

typedef struct _MEMAPDRW		//Data Read/Write register(MEM-AP)
{
	unsigned long	Size					:3;			//Bit[2:0]地址访问字段大小，暂理解为数据位宽，查看 _CswSize
	unsigned long	Reserved0			:1;			//Bit[3]Reserved0
	unsigned long	AddrInc				:2;			//Bit[5:4]地址自增控制，查看 _AddrInc
	unsigned long DeviceEn 			:1;			//Bit[6]Device enabled.
	unsigned long TrInProg 			:1;			//Bit[7]Transfer in progress:传输状态，只读位，0-空闲，可以传输；1-忙，正在传输数据
	unsigned long Mode 					:4;			//Bit[11:8]Mode of operation:操作模式，0-基本模式，常规使用方式；1-Barrier support enabled，不了解，没找到使用
	unsigned long Type 					:4;			//Bit[15:12]See the entry for {Prot}.bits[30:24]
	unsigned long Bits					:7;			//Bit[22:16]Reserved1
	unsigned long SPIDEN				:1;			//Bit[23]0-禁止安全访问；1-使能安全访问
	unsigned long Prot					:7;			//Bit[30:24]Debug software access enable
	unsigned long DbgSwEnable		:1;			//Bit[31]Debug software access enable	
}MEMAPDRWDef;

//=============================================DP register descriptions（DP寄存器描述)
//typedef struct _ABORT		//AP Abort register（AP中止寄存器）：中止寄存器强制AP事务中止
//{
//	unsigned long	DAPABORT			:1;			//Bit[0]Debug Port address bank select, see DPBANKSEL on page 2-59.
//	unsigned long	STKCMPCLR			:1;			//Bit[1]Write 1 to this bit to clear the CTRL/STAT.STICKYCMP sticky compare bit to 0.
//	unsigned long	STKERRCLR			:1;			//Bit[2]Write 1 to this bit to clear the CTRL/STAT.STICKYERR sticky error bit to 0.
//	unsigned long WDERRCLR 			:1;			//Bit[3]Write 1 to this bit to clear the CTRL/STAT.WDATAERR write data error bit to 0.
//	unsigned long ORUNERRCLR		:1;			//Bit[4]Write 1 to this bit to clear the CTRL/STAT.STICKYORUN overrun error bit to 0.
//	unsigned long Reserved 			:27;		//Bit[31:5]Write 1 to this bit to clear the CTRL/STAT.WDATAERR write data error bit to 0.
//}ABORTDef;
//typedef struct _CSR		//CTRL/STAT, Control/Status register（控制/状态寄存器）
//{
//	unsigned long	ORUNDETECT		:1;			//Bit[0]overrun detection:此位设置为1以启用溢出检测。
//	unsigned long	STICKYORUN		:1;			//Bit[1]溢出标志：0-未溢出，1-溢出
//	unsigned long	TRNMODE				:2;			//Bit[3:2]Transfer mode：传输模式查看 _TrnMode
//	unsigned long STICKYCMP 		:1;			//Bit[4]This bit is set to 1 when a match occurs on a pushed-compare or a pushed-verify operation
//	unsigned long STICKYERR			:1;			//Bit[5]This bit is set to 1 if an error is returned by an AP transaction
//	unsigned long READOK 				:1;			//Bit[6]DPv1 or higher 读数据链路的定义
//	unsigned long WDATAERR			:1;			//Bit[7]DPv1 or higher 写数据链路的定义
//	unsigned long MASKLANE			:4;			//Bit[11:8]指示在推送比较和推送验证操作中要屏蔽的字节。
//	unsigned long TRNCNT				:12;		//Bit[23:12]Transaction counter（传输计数器）.
//	unsigned long	Reserved			:2;			//Bit[25:24]Reserved
//	unsigned long	CDBGRSTREQ		:1;			//Bit[26]Debug reset request（调试复位请求）
//	unsigned long	CDBGRSTACK		:1;			//Bit[27]Debug reset acknowledge（调试复位应答/状态位）
//	unsigned long	CDBGPRWUPREQ	:1;			//Bit[28]Debug powerup request（调试上电请求）
//	unsigned long	CDBGPWRUPACK	:1;			//Bit[29]Debug powerup acknowledge（调试上电应答/状态位）
//	unsigned long	CSYSPWRUPREQ	:1;			//Bit[30]System powerup request（系统上电请求）
//	unsigned long	CSYSPWRUPACK	:1;			//Bit[31]System powerup acknowledge（系统上电应答/状态标志位）
//}CSRDef;
typedef struct _DLCR		//Data Link Control Register（数据链路控制寄存器）
{
	unsigned long	Reserved0			:6;			//Bit[5:0]Event status flag:0-有事件需要处理；1-无需要处理事件
	unsigned long	Reserved1			:1;			//Bit[6]为0
	unsigned long	Reserved2			:1;			//Bit[7]为0
	unsigned long	TURNROUND			:2;			//Bit[9:8]为0
	unsigned long	Reserved3			:22;		//Bit[31:10]为0
}DLCRDef;
typedef struct _DLPIDR		//Data Link Protocol Identification Register（数据链路协议识别寄存器）
{
	unsigned long	PROTVSN				:4;			//Bit[3:0]定义实现的串行线调试协议版本，01-V2
	unsigned long	Reserved			:24;		//Bit[27:4]UNKNOWN
	unsigned long	TINSTANCE			:4;			//Bit[31:28]实现定义。定义此设备的实例号。	
}DLPIDRDef;
typedef struct _EVENTSTAT		//Event Status register（状态寄存器）
{
	unsigned long	EA						:1;			//Bit[0]事件标识；0--有事件，1--无事件
	unsigned long	Reserved			:31;		//Bit[31:1]RES0.
}EVENTSTATDef;
typedef struct _RDBUFF		//Event Status register（状态寄存器）
{
	unsigned long	EA						:1;			//Bit[0]事件标识；0--有事件，1--无事件
	unsigned long	Reserved			:31;		//Bit[31:1]RES0.
}RDBUFFDef;

//typedef struct _SELECT		//AP Select register(AP选择寄存器）
//{
//	unsigned long	DPBANKSEL			:4;			//Bit[3:0]Debug Port address bank select, see DPBANKSEL on page 2-59.调试寄存器地址选择
//	unsigned long	APBANKSEL			:4;			//Bit[7:4]Selects the active four-word register bank on the current AP 选择当前AP上的活动四字寄存器
//	unsigned long	Reserved			:16;		//Bit[23:8]地址自增控制，查看 _AddrInc
//	unsigned long APSEL 				:8;			//Bit[31:24]Selects an AP. AP端口选择
//}SELECTDef;

typedef struct _TARGETSEL		//Target Selection register（目标选择寄存器）
{
	unsigned long	SBO						:1;			//Bit[0]Read-As-One调试寄存器地址选择
	unsigned long	TDESIGNER			:11;		//Bit[11:1]ID identifies the designer 由JEDEC JEP106延续代码和身份代码组成的11位代码。
	unsigned long	TPARTNO				:16;		//Bit[27:12]designer of the part 端口编号
	unsigned long TREVISION 		:4;			//Bit[31:28]Target revision. 目标版本
}TARGETSELDef;

typedef struct _TARGETID		//Target Identification register（目标识别寄存器）
{
	unsigned long	RAO						:1;			//Bit[0]Read-As-One调试寄存器地址选择
	unsigned long	TDESIGNER			:11;		//Bit[11:1]ID identifies the designer 由JEDEC JEP106延续代码和身份代码组成的11位代码。
	unsigned long	TPARTNO				:16;		//Bit[27:12]designer of the part 端口编号
	unsigned long TREVISION 		:4;			//Bit[31:28]Target revision. 目标版本
}TARGETIDDef;


//低位先传
typedef enum
{
	SWJAckOK		=	0x01,		//OK
	SWJAckWait	=	0x02,		//Wait
	SWJAckFault	=	0x04		//Fault
}SWJAckDef;
typedef struct _SWJRequest
{
	unsigned char Start 	:1;			//起始位：值为1
	unsigned char APnDP 	:1;			//寄存器访问方式：0-DPACC访问，1-APACC访问
	unsigned char RnW 		:1;			//读写位：0-写，1-读
	unsigned char Addr0   :1;			//DP或者AP寄存器的地址区域，低位先发送
  unsigned char Addr1   :1;			//DP或者AP寄存器的地址区域，低位先发送
	unsigned char Parity 	:1;			//奇偶校验位：0-APnDP到Addr中1的个数为偶数；1--APnDP到Addr中1的个数为奇数
	unsigned char Stop 		:1;			//停止位：值为0
	unsigned char Park	 	:1;			//单一位：传输该位时，主机拉高然后不再驱动该位
}SWJRequestDef;


/*debug_cm.h已经定义
 Debug Select Register definitions
#define CTRLSEL        0x00000001  // CTRLSEL (SW Only)
#define APBANKSEL      0x000000F0  // APBANKSEL Mask
#define APSEL          0xFF000000  // APSEL Mask
*/

typedef struct
{
    unsigned long r[16];
    unsigned long xpsr;
} DEBUG_STATE;
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
static unsigned char SWJ_ReadDP(unsigned char adr, unsigned long *val);
unsigned char SWJ_WriteDP(unsigned char adr, unsigned long val);
unsigned char SWJ_ReadAP(unsigned long adr, unsigned long *val);
unsigned char SWJ_WriteAP(unsigned long adr, unsigned long val);
unsigned char SWJ_InitDebug(void);
unsigned char SWJ_ReadMem(unsigned long addr, unsigned char *buf, unsigned long len);
unsigned char SWJ_WriteMem(unsigned long addr, unsigned char *buf, unsigned long len);
unsigned char SWJ_SetTargetState(TARGET_RESET_STATE state);
unsigned char swd_flash_syscall_exec(const FLASH_SYSCALL *sysCallParam, unsigned long entry,unsigned long arg1,unsigned long arg2, unsigned long arg3, unsigned long arg4);

//Driver
unsigned char SWD_TransRequest(unsigned char request);			//发送起始请求
unsigned char SWD_TransferOnce(unsigned long request, unsigned long *data);		//单次传输：读/写传输
unsigned char SWD_Transfer(unsigned long request, unsigned long *data);				//数据传输-读写，失败时在最大重试范围内重试
static void SWJ_SendData(uint16_t data);			//发送16字节数据
void Line_Rest(void);			//线路复位--发送至少50个时钟的DIO-1,这里发56个
static unsigned char SWJ_JTAG2SWD(void);		//从JTAG切换到SWD模式
static unsigned char SWJ_ReadDP(unsigned char adr, unsigned long *val);		//读DPACC
unsigned char SWJ_WriteDP(unsigned char adr, unsigned long val);		//写DPACC
unsigned char SWJ_ReadAP(unsigned long adr, unsigned long *val);		//读APACC
unsigned char SWJ_WriteAP(unsigned long adr, unsigned long val);		//写APACC

static unsigned char SWJ_WriteData(unsigned long addr, unsigned long data);	//写数据

static unsigned char SWJ_WriteMem8(unsigned long addr, unsigned char val);	//往内存写一个8位数据
unsigned char SWJ_WriteMem32(unsigned long addr, unsigned long val);				//往内存写一个32位数据
static unsigned char SWJ_WriteBlock(unsigned long addr, unsigned char *buf, unsigned long len);		//块写入
static unsigned char SWJ_ReadData(unsigned long addr, unsigned long *val);	//读数据
static unsigned char SWJ_ReadMem32(unsigned long addr, unsigned long *val);	//从内存读一个32位数据
static unsigned char SWJ_ReadMem8(unsigned long addr, unsigned char *val);	//从内存读一个8位数据
static unsigned char SWJ_ReadBlock(unsigned long addr, unsigned char *buf, unsigned long len);		//块读取
unsigned char swd_write_memory(unsigned long address, unsigned char *data, unsigned long size);		//写寄存器
unsigned char swd_read_memory(unsigned long address, unsigned char *data, unsigned long size);		//读寄存器
unsigned char SWJ_ReadMem(unsigned long addr, unsigned char *buf, unsigned long len);							//从目标内存读数据
unsigned char SWJ_WriteMem(unsigned long addr, unsigned char *buf, unsigned long len);						//往目标内存写数据
static unsigned char SWJ_WaitUntilHalted(void);			//等目标Halt
unsigned char SWJ_SetTargetState(TARGET_RESET_STATE state);			//设置目标状态
static unsigned char SWJ_WriteCoreReg(unsigned long n, unsigned long val);		//写目标内核寄存器
static unsigned char SWJ_ReadCoreReg(unsigned long n, unsigned long *val);		//读目标内核寄存器
unsigned char swd_write_debug_state(DEBUG_STATE *state);		//写debug状态
unsigned char swd_flash_syscall_exec(const FLASH_SYSCALL *sysCallParam, unsigned long entry, unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4);	//flash状态回读
unsigned char SWJ_InitDebug(void);		//将设备JTAG/SWD状态初始化
void softdelay(unsigned long us);			//软件延时

#endif
