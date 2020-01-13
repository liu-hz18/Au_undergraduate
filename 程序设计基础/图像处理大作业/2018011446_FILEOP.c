#include<stdio.h>
#include"2018010876_RGBQUAD.h"
int main (int argc, char* argv[])
{
	FILE* fp = fopen (argv[1], "r+b");
	fread (&bfType, sizeof(unsigned short), 1, fp);			//读入位图文件类型
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读入BMP文件头
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//读入位图信息头
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8)
	{
		printf ("This file is not an 8-bit BMP file");
		return -1;
	}
	Adjust_Colors(fp);
	return 0;
	fclose (fp);
}
