#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define KerSize 3						//卷积核大小
//卷积核
char Sobel_kerx[KerSize][KerSize]={
	-2,-2,-2,
	-2,17,-2,
	-2,-2,-2
};

//BMP文件头结构体（14字节）
typedef struct tagBITMAPFILEHEADER{
    unsigned long bfSize;            //位图文件的大小，以字节为单位（3-6字节，低位在前）
    unsigned short bfReserved1;      //位图文件保留字，必须为0(7-8字节）
    unsigned short bfReserved2;      //位图文件保留字，必须为0(9-10字节）
    unsigned long bfOffBits;         //位图数据的起始位置，以相对于位图（11-14字节，低位在前）
					                 //文件头的偏移量表示，以字节为单位
}BITMAPFILEHEADER;	

//位图信息头结构体（40字节）
typedef struct tagBITMAPINFOHEADER{
	unsigned long biSize;               //本结构所占用字节数（15-18字节）
	long biWidth;                       //位图的宽度，以像素为单位（19-22字节）
	long biHeight;                      //位图的高度，以像素为单位（23-26字节）
	unsigned short biPlanes;            //目标设备的级别，必须为1(27-28字节）
	unsigned short biBitCount;          //每个像素所需的位数，必须是1（双色），（29-30字节）
	                                    //4(16色），8(256色）16(高彩色)或24（真彩色）之一
	unsigned long biCompression;        //位图压缩类型，必须是0（不压缩），（31-34字节）
	                                    //1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
	unsigned long biSizeImage;          //位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
	long biXPelsPerMeter;				//位图水平分辨率，每米像素数（39-42字节）
	long biYPelsPerMeter;				//位图垂直分辨率，每米像素数（43-46字节)
	unsigned long biClrUsed;			//位图实际使用的颜色表中的颜色数（47-50字节）
	unsigned long biClrImportant;		//位图显示过程中重要的颜色数（51-54字节）
}BITMAPINFOHEADER;

//颜色表结构体（4字节）
//24bit没有调色板项！！，位图信息头之后就是像素数据！！转为8bit的时候需要新建调色板
typedef struct tagRGBQUAD{
	unsigned char rgbBlue;				//蓝色的亮度（值范围为0-255)
	unsigned char rgbGreen;				//绿色的亮度（值范围为0-255)
	unsigned char rgbRed;				//红色的亮度（值范围为0-255)
	unsigned char rgbReserved;			//保留，必须为0
}RGBQUAD;								

BITMAPFILEHEADER fileHeader;			//BMP文件头
BITMAPINFOHEADER infoHeader;			//位图信息头
unsigned short bfType;					//位图文件的类型，必须为BM(1-2字节）,属于文件头，但占两字节，放置在结构体内会导致错位
RGBQUAD Colors[256];					//颜色表，8bit 256个，4bit 16个，1bit 2个
unsigned char *ImgData;					//位图数据，8bit一个像素值一个字节，用unsigned char
unsigned char *newimgData;			    //卷积后新图像的像素数据
//unsigned char ImgData[3000][3];		//24bit一个像素三个字节，RGB三色，顺序为BGR
		
void creat(unsigned char **pointer,FILE*fp){
	int i=0;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//读入位图文件类型
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读入BMP文件头
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//读入位图信息头
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	//只能创建一维数组，动态创建二维数组在堆中是一行一行分配的，离散化的，但是fread函数只能memcpy一个连续空间！！！
	*pointer = (unsigned char*)malloc(sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth);
	printf("动态数组创建成功!\n");
	return ;
}

//调整调色板，目前功能：红蓝对调，并逆序调色板
void Adjust_Colors (FILE* fp){
	int i;
	int temp1;							//用于交换红蓝分量
	RGBQUAD temp2;						//用于逆序
	FILE*new_fp;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//读入位图文件类型
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读入BMP文件头
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//读入位图信息头
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("长度=%d 高度=%d\n进行调色板操作！\n",infoHeader.biWidth,infoHeader.biHeight);
	fread (Colors, sizeof(RGBQUAD), 256, fp);		//读入颜色表，共256项
	fread(ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,fp);//读入位图数据
	for (i = 0; i < 256; i++){
		temp1 = Colors[i].rgbBlue;
		Colors[i].rgbBlue = Colors[i].rgbRed;
		Colors[i].rgbRed = temp1;					//红蓝分量对调
	}
	for (i = 0; i < 128; i++){
		temp2 = Colors[i];
		Colors[i] = Colors[255-i];
		Colors[255-i] = temp2;						//将颜色表逆序
	}
	if((new_fp = fopen("D:\\大一上\\程设\\图像处理\\Colored.bmp","w+b"))!=NULL){
		fwrite (&bfType, sizeof(unsigned short), 1, new_fp);
		fwrite (&fileHeader, sizeof(BITMAPFILEHEADER), 1, new_fp);
		fwrite (&infoHeader, sizeof(BITMAPINFOHEADER), 1, new_fp);
		fwrite (Colors, sizeof(RGBQUAD), 256, new_fp);
		fwrite (ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,new_fp);
	}
}

//输出BMP图片的颜色表
void Print_Colors (FILE* fp){
	int i;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//读入位图文件类型
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读入BMP文件头
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//读入位图信息头
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("长度=%d 高度=%d\n",infoHeader.biWidth,infoHeader.biHeight);
	fread (Colors, sizeof(RGBQUAD), 256, fp);				//读入颜色表，共256项
	printf("颜色表信息:\n");
	for (i = 0; i < 256; i++){
		printf("%4d%4d%4d\n",Colors[i].rgbRed,Colors[i].rgbGreen,Colors[i].rgbBlue);	//输出图像的RGB值
	}
}

//输出BMP图片的像素值,数据过多，IO输出速度较慢，小心！
void Print_ImgData(FILE* fp){
	int i,j;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//读入位图文件类型
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读入BMP文件头
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//读入位图信息头
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("长度=%d 高度=%d\n输出像素信息!\n",infoHeader.biWidth,infoHeader.biHeight);
	fread(Colors, sizeof(RGBQUAD), 256, fp);				//读入颜色表，共256项
	fread(ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,fp);
	for(i=0;i<infoHeader.biHeight;i++,putchar(10)){
		for(j=0;j<(infoHeader.biWidth+3)/4*4;j++){
			printf("%4d",*(ImgData+i*infoHeader.biWidth+j));
		}
	}
	return; 
}

//卷积
void Conve_ImgData(FILE* fp,char ker[][KerSize]){
	int i,j,m,n;
	FILE*new_fp;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//读入位图文件类型
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读入BMP文件头
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//读入位图信息头
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("长度=%d 高度=%d\n进行卷积！\n",infoHeader.biWidth,infoHeader.biHeight);
	fread(Colors, sizeof(RGBQUAD), 256, fp);				//读入颜色表，共256项
	fread(ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,fp);
	for(i=0;i<infoHeader.biHeight;i++){
		//windows系统下一个扫描行所占字节数必须是4的整数倍，所以这里采用((x+3)/4)*4的方式
		for(j=0;j<(infoHeader.biWidth+3)/4*4;j++){
			if( i < KerSize-1 || j < KerSize-1 || i > infoHeader.biHeight-KerSize || j > infoHeader.biWidth-KerSize ){
				*(newimgData+i*infoHeader.biWidth+j)=*(ImgData+i*infoHeader.biWidth+j);
			}else{
				for(m=i-1;m<=i+1;m++){
					for(n=j-1;n<=j+1;n++){
						*(newimgData+i*infoHeader.biWidth+j)+=(ker[m-i+1][n-j+1]**(ImgData+i*infoHeader.biWidth+j));
					}
				}
			}
		}
	}
	//传入新图像数据,创建新文件
	if((new_fp = fopen("D:\\大一上\\程设\\图像处理\\Conved.bmp","w+b"))!=NULL){
		fwrite (&bfType, sizeof(unsigned short), 1, new_fp);
		fwrite (&fileHeader, sizeof(BITMAPFILEHEADER), 1, new_fp);
		fwrite (&infoHeader, sizeof(BITMAPINFOHEADER), 1, new_fp);
		fwrite (Colors, sizeof(RGBQUAD), 256, new_fp);
		fwrite (newimgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,new_fp);
	}else{
		printf("创建卷积后的新文件失败！\n");
		exit(0);
	}
	fclose(new_fp);
	return; 
}

//彩色转为灰度图
void Bmp8ToGray(FILE* fp){
	int i;
	int temp1;							//用于交换红蓝分量
	RGBQUAD temp2;						//用于逆序
	FILE*new_fp;
	RGBQUAD gray[256];
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//读入位图文件类型
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//读入BMP文件头
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//读入位图信息头
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("长度=%d 高度=%d\n进行调色板操作！\n",infoHeader.biWidth,infoHeader.biHeight);
	fread (Colors, sizeof(RGBQUAD), 256, fp);		//读入颜色表，共256项
	fread(ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,fp);//读入位图数据
	for (i = 0; i < 256; i++){
		//这里不使用三原色的平均值，应使用心理学灰度公式，因为人眼对绿色的敏感度较高
		gray[i].rgbBlue = gray[i].rgbGreen = gray[i].rgbRed = (Colors[i].rgbBlue*0.114+Colors[i].rgbRed*0.587+Colors[i].rgbRed*0.299);
		gray[i].rgbReserved = 0;
	}
	if((new_fp = fopen("D:\\大一上\\程设\\图像处理\\Grayed.bmp","w+b"))!=NULL){
		fwrite (&bfType, sizeof(unsigned short), 1, new_fp);
		fwrite (&fileHeader, sizeof(BITMAPFILEHEADER), 1, new_fp);
		fwrite (&infoHeader, sizeof(BITMAPINFOHEADER), 1, new_fp);
		fwrite (gray, sizeof(RGBQUAD), 256, new_fp);
		fwrite (ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,new_fp);
	}
}

int main (){
	char FName[50];
	FILE* fp;
	printf("请输入8bitBMP文件的完整路径:\n");
	scanf_s("%s",FName,50);
	fp = fopen(FName,"r+b");	            	//在此处进行文件路径设置
	creat(&newimgData,fp);
	creat(&ImgData,fp);
	Bmp8ToGray(fp);								//转为灰度图像
	Adjust_Colors(fp);						    //红蓝分量对换，调色板逆序
	/*Print_Colors(fp);*/						//输出调色板信息
	//Print_ImgData(fp);						//输出像素值
	Conve_ImgData(fp,Sobel_kerx);				//卷积
	fclose(fp);
	free(newimgData);
	free(ImgData);
	return 0;
}
