#ifndef __BMP_H
#define __BMP_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_type.h"
typedef struct _BMPInf
{
  //=========================图像文件头
  //-------------------------0~1"BM"标识：
  unsigned char B;     //byte0 'B'0x42
  unsigned char M;     //byte1 'M'0x4D
  //-------------------------byte2-5 size整个文件大小
  unsigned long bfSize; //byte2-5该BMP位图文件大小(单位Byte)
  //-------------------------6~9保留，必须设置为0
  unsigned long bfRev0;       //byte6-9保留
  unsigned long bfOffset; //byte10-13从文件开始到位图数据之间的偏移量(14+40+4*（2^biBitCount）)(在有颜色板的情况下)。4600 0000，为00000046h=70，上面的文件头就是35字=70字节。
  //=========================位图信息头
  unsigned long   biSize;         //byte14-17 位图图信息头长度
  unsigned long   biWidth;        //byte18-21 位图宽度，以像素为单位。8000 0000，为00000080h=128。
  unsigned long   biHeight;       //byte22-25 位图高度，以像素为单位。9000 0000，为00000090h=144。
  unsigned short  biPlanes;       //byte26-27 位图的位面数，该值总是1。0100，为0001h=1。
  unsigned short  biBitCount;     //byte28-29 每个像素的位数。有1（单色），4（16色），8（256色），16（64K色RGB565，高彩色），24（16M色RGB888，真彩色），32（4096M色，增强型真彩色）。1000为0010h=16。
  unsigned long   biCompression;  //byte30-33 压缩说明,取值范围：
                                  //          0 BI_RGB 不压缩(最常用)
                                  //          1 BI_RGB8 8bit游程编码(BLE)，只用于8位图
                                  //          2 BI_RGB4 4bit游程编码(BLE)，只用于4位图
                                  //          3 BI_BITFIELDS比特域，用于16/32位图
                                  //          4 BI_JPEG 位图含JPEG图像(仅用于打印机)
                                  //          5 BI_PNG  位图含PGN图像(仅用于打印机)
                                  //RLE简单地说是采用像素数+像素值的方式进行压缩。
                                  //T408采用的是位域存放方式，用两个字节表示一个像素，位域分配为r5b6g5。图中0300 0000为00000003h=3(这张图片不存在颜色板)。
  unsigned long   biSizeImage;    //byte34-37 说明图像的大小(图像数据大小)，以字节为单位，当使用BI_RGB格式时，其值可设置为0
  unsigned long   biXPelsPerMater;    //byte38-41 水平分辨率，以像素/米为单位
  unsigned long   biYPelsPerMater;    //byte42-45 垂直分辨率，以像素/米为单位
  unsigned long   biClrUsed;          //byte46-49 位图使用的颜色索引数。设为0的话，则说明使用所有调色板项
  unsigned long   biClrImportant;     //byte50-53 对图象显示有重要影响的颜色索引的数目。如果是0，表示都重要
}BMPInftDef;


#endif


