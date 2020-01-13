#include<stdio.h>
#include<malloc.h>

//BMP�ļ�ͷ�ṹ��
typedef struct tagBITMAPFILEHEADER{
    unsigned long bfSize;            //λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ��3-6�ֽڣ���λ��ǰ��
    unsigned short bfReserved1;      //λͼ�ļ������֣�����Ϊ0(7-8�ֽڣ�
    unsigned short bfReserved2;      //λͼ�ļ������֣�����Ϊ0(9-10�ֽڣ�
    unsigned long bfOffBits;         //λͼ���ݵ���ʼλ�ã��������λͼ��11-14�ֽڣ���λ��ǰ��
					                 //�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
}BITMAPFILEHEADER;	

//λͼ��Ϣͷ�ṹ��
typedef struct tagBITMAPINFOHEADER{
	unsigned long biSize;               //���ṹ��ռ���ֽ�����15-18�ֽڣ�
	long biWidth;                       //λͼ�Ŀ�ȣ�������Ϊ��λ��19-22�ֽڣ�
	long biHeight;                      //λͼ�ĸ߶ȣ�������Ϊ��λ��23-26�ֽڣ�
	unsigned short biPlanes;            //Ŀ���豸�ļ��𣬱���Ϊ1(27-28�ֽڣ�
	unsigned short biBitCount;          //ÿ�����������λ����������1��˫ɫ������29-30�ֽڣ�
	                                    //4(16ɫ����8(256ɫ��16(�߲�ɫ)��24�����ɫ��֮һ
	unsigned long biCompression;        //λͼѹ�����ͣ�������0����ѹ��������31-34�ֽڣ�
	                                    //1(BI_RLE8ѹ�����ͣ���2(BI_RLE4ѹ�����ͣ�֮һ
	unsigned long biSizeImage;          //λͼ�Ĵ�С(���а�����Ϊ�˲���������4�ı�������ӵĿ��ֽ�)�����ֽ�Ϊ��λ��35-38�ֽڣ�
	long biXPelsPerMeter;				//λͼˮƽ�ֱ��ʣ�ÿ����������39-42�ֽڣ�
	long biYPelsPerMeter;				//λͼ��ֱ�ֱ��ʣ�ÿ����������43-46�ֽ�)
	unsigned long biClrUsed;			//λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ�
	unsigned long biClrImportant;		//λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ�
}BITMAPINFOHEADER;

BITMAPFILEHEADER fileHeader;			//BMP�ļ�ͷ
BITMAPINFOHEADER infoHeader;			//λͼ��Ϣͷ
void Adjust_Colors (FILE* fp);

unsigned short bfType;					//λͼ�ļ������ͣ�����ΪBM(1-2�ֽڣ�,�����ļ�ͷ����ռ���ֽڣ������ڽṹ���ڻᵼ�´�λ

//��ɫ��ṹ��
typedef struct tagRGBQUAD{
	unsigned char rgbBlue;				//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbGreen;				//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbRed;				//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbReserved;			//����������Ϊ0
}RGBQUAD;								//��ɫ��

#define KerSize 3						//����˴�С
#define ImgHeight infoHeader.biHeight
#define ImgWidth infoHeader.biWidth

//�����
char Sobel_kerx[KerSize][KerSize]={
	-1,-1,-1,
	-1,9,-1,
	-1,-1,-1
};

BITMAPFILEHEADER fileHeader;			//BMP�ļ�ͷ
BITMAPINFOHEADER infoHeader;			//λͼ��Ϣͷ
RGBQUAD Colors[256];					//��ɫ��
unsigned char *ImgData;					//λͼ���ݣ�һ������ֵһ���ֽڣ���unsigned char
unsigned char *newimgData;			    //�������ͼ�����������		

void creat(unsigned char **pointer,FILE*fp){
	int i=0;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//����λͼ�ļ�����
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//����BMP�ļ�ͷ
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//����λͼ��Ϣͷ
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	//ֻ�ܴ���һά���飬��̬������ά�����ڶ�����һ��һ�з���ģ���ɢ���ģ�����fread����ֻ��memcpyһ�������ռ䣡����
	*pointer = (unsigned char*)malloc(sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth);
	printf("��̬���鴴���ɹ�!\n");
	return ;
}

//������ɫ�壬Ŀǰ���ܣ������Ե����������ɫ��
void Adjust_Colors (FILE* fp){
	int i;
	int temp1;							//���ڽ�����������
	RGBQUAD temp2;						//��������
	FILE*new_fp;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//����λͼ�ļ�����
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//����BMP�ļ�ͷ
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//����λͼ��Ϣͷ
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("����=%d �߶�=%d\n���е�ɫ�������\n",infoHeader.biWidth,infoHeader.biHeight);
	fread (Colors, sizeof(RGBQUAD), 256, fp);		//������ɫ����256��
	fread(ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,fp);//����λͼ����
	for (i = 0; i < 256; i++){
		temp1 = Colors[i].rgbBlue;
		Colors[i].rgbBlue = Colors[i].rgbRed;
		Colors[i].rgbRed = temp1;					//���������Ե�
	}
	for (i = 0; i < 128; i++){
		temp2 = Colors[i];
		Colors[i] = Colors[255-i];
		Colors[255-i] = temp2;						//����ɫ������
	}
	if((new_fp = fopen("D:\\��һ��\\����\\��ҵ\\ͼ����\\Colored.bmp","w+b"))!=NULL){
		fwrite (&bfType, sizeof(unsigned short), 1, new_fp);
		fwrite (&fileHeader, sizeof(BITMAPFILEHEADER), 1, new_fp);
		fwrite (&infoHeader, sizeof(BITMAPINFOHEADER), 1, new_fp);
		fwrite (Colors, sizeof(RGBQUAD), 256, new_fp);
		fwrite (ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,new_fp);
	}
}

//���BMPͼƬ����ɫ��
void Print_Colors (FILE* fp){
	int i;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//����λͼ�ļ�����
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//����BMP�ļ�ͷ
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//����λͼ��Ϣͷ
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("����=%d �߶�=%d\n",infoHeader.biWidth,infoHeader.biHeight);
	fread (Colors, sizeof(RGBQUAD), 256, fp);				//������ɫ����256��
	printf("��ɫ����Ϣ:\n");
	for (i = 0; i < 256; i++){
		printf("%4d%4d%4d\n",Colors[i].rgbRed,Colors[i].rgbGreen,Colors[i].rgbBlue);	//���ͼ���RGBֵ
	}
}

//���BMPͼƬ������ֵ,���ݹ���IO����ٶȽ�����С�ģ�
void Print_ImgData(FILE* fp){
	int i,j;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//����λͼ�ļ�����
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//����BMP�ļ�ͷ
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//����λͼ��Ϣͷ
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("����=%d �߶�=%d\n���������Ϣ!\n",infoHeader.biWidth,infoHeader.biHeight);
	fread(Colors, sizeof(RGBQUAD), 256, fp);				//������ɫ����256��
	fread(ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,fp);
	for(i=0;i<infoHeader.biHeight;i++,putchar(10)){
		for(j=0;j<infoHeader.biWidth;j++){
			printf("%4d",*(ImgData+i*infoHeader.biWidth+j));
		}
	}
	return; 
}

//���
void Conve_ImgData(FILE* fp,char ker[][KerSize]){
	int i,j,m,n;
	FILE*new_fp;
	rewind(fp);
	fread (&bfType, sizeof(unsigned short), 1, fp);			//����λͼ�ļ�����
	fread (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);	//����BMP�ļ�ͷ
	fread (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);	//����λͼ��Ϣͷ
	if (bfType != 0x4D42 || infoHeader.biBitCount != 8){
		printf ("This file is not an 8-bit BMP file\n");
		return ;
	}
	printf("����=%d �߶�=%d\n���о����\n",infoHeader.biWidth,infoHeader.biHeight);
	fread(Colors, sizeof(RGBQUAD), 256, fp);				//������ɫ����256��
	fread(ImgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,fp);
	for(i=0;i<infoHeader.biHeight;i++){
		for(j=0;j<infoHeader.biWidth;j++){
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
	//������ͼ������,�������ļ�
	if((new_fp = fopen("D:\\��һ��\\����\\��ҵ\\ͼ����\\Conved.bmp","w+b"))!=NULL){
		fwrite (&bfType, sizeof(unsigned short), 1, new_fp);
		fwrite (&fileHeader, sizeof(BITMAPFILEHEADER), 1, new_fp);
		fwrite (&infoHeader, sizeof(BITMAPINFOHEADER), 1, new_fp);
		fwrite (Colors, sizeof(RGBQUAD), 256, new_fp);
		fwrite (newimgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,new_fp);
	}
	fclose(new_fp);
	return; 
}


int main (){
	FILE* fp = fopen ("D:\\��һ��\\����\\��ҵ\\ͼ����\\test.bmp","r+b");
	creat(&newimgData,fp);
	creat(&ImgData,fp);
	Adjust_Colors(fp);							//���������Ի�
	/*Print_Colors(fp);*/						//�����ļ���ָ��λ�ã���������������ͬʱʹ�ã�ÿ����֮ǰrewind()�ɣ���
	//Print_ImgData(fp);
	Conve_ImgData(fp,Sobel_kerx);				//���
	fclose (fp);
	free(newimgData);
	free(ImgData);
	return 0;
}
