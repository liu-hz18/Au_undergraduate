#ifndef _2018010876_RGBQUAD_H_
#define _2018010876_RGBQUAD_H_
extern unsigned short bfType;

typedef struct tagBITMAPFILEHEADER
{
    unsigned long bfSize;//位图文件的大小，以字节为单位（3-6字节，低位在前）
    unsigned short bfReserved1;//位图文件保留字，必须为0(7-8字节）
    unsigned short bfReserved2;//位图文件保留字，必须为0(9-10字节）
    unsigned long bfOffBits;//位图数据的起始位置，以相对于位图（11-14字节，低位在前）
					//文件头的偏移量表示，以字节为单位
}BITMAPFILEHEADER;	

typedef struct tagBITMAPINFOHEADER
{
	unsigned long biSize;//本结构所占用字节数（15-18字节）
	long biWidth;//位图的宽度，以像素为单位（19-22字节）
	long biHeight;//位图的高度，以像素为单位（23-26字节）
	unsigned short biPlanes;//目标设备的级别，必须为1(27-28字节）
	unsigned short biBitCount;//每个像素所需的位数，必须是1（双色），（29-30字节）
	//4(16色），8(256色）16(高彩色)或24（真彩色）之一
	unsigned long biCompression;//位图压缩类型，必须是0（不压缩），（31-34字节）
	//1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
	unsigned long biSizeImage;//位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
	long biXPelsPerMeter;//位图水平分辨率，每米像素数（39-42字节）
	long biYPelsPerMeter;//位图垂直分辨率，每米像素数（43-46字节)
	unsigned long biClrUsed;//位图实际使用的颜色表中的颜色数（47-50字节）
	unsigned long biClrImportant;//位图显示过程中重要的颜色数（51-54字节）
}BITMAPINFOHEADER;

extern BITMAPFILEHEADER fileHeader;	//BMP文件头
extern BITMAPINFOHEADER infoHeader;	//位图信息头
void Adjust_Colors (FILE* fp);
#endif