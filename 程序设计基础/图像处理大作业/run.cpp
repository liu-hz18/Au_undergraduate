#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define KerSize 3						//����˴�С
//�����
char Sobel_kerx[KerSize][KerSize]={
	-2,-2,-2,
	-2,17,-2,
	-2,-2,-2
};

//BMP�ļ�ͷ�ṹ�壨14�ֽڣ�
typedef struct tagBITMAPFILEHEADER{
    unsigned long bfSize;            //λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ��3-6�ֽڣ���λ��ǰ��
    unsigned short bfReserved1;      //λͼ�ļ������֣�����Ϊ0(7-8�ֽڣ�
    unsigned short bfReserved2;      //λͼ�ļ������֣�����Ϊ0(9-10�ֽڣ�
    unsigned long bfOffBits;         //λͼ���ݵ���ʼλ�ã��������λͼ��11-14�ֽڣ���λ��ǰ��
					                 //�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
}BITMAPFILEHEADER;	

//λͼ��Ϣͷ�ṹ�壨40�ֽڣ�
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

//��ɫ��ṹ�壨4�ֽڣ�
//24bitû�е�ɫ�������λͼ��Ϣͷ֮������������ݣ���תΪ8bit��ʱ����Ҫ�½���ɫ��
typedef struct tagRGBQUAD{
	unsigned char rgbBlue;				//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbGreen;				//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbRed;				//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbReserved;			//����������Ϊ0
}RGBQUAD;								

BITMAPFILEHEADER fileHeader;			//BMP�ļ�ͷ
BITMAPINFOHEADER infoHeader;			//λͼ��Ϣͷ
unsigned short bfType;					//λͼ�ļ������ͣ�����ΪBM(1-2�ֽڣ�,�����ļ�ͷ����ռ���ֽڣ������ڽṹ���ڻᵼ�´�λ
RGBQUAD Colors[256];					//��ɫ��8bit 256����4bit 16����1bit 2��
unsigned char *ImgData;					//λͼ���ݣ�8bitһ������ֵһ���ֽڣ���unsigned char
unsigned char *newimgData;			    //�������ͼ�����������
//unsigned char ImgData[3000][3];		//24bitһ�����������ֽڣ�RGB��ɫ��˳��ΪBGR
		
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
	if((new_fp = fopen("D:\\��һ��\\����\\ͼ����\\Colored.bmp","w+b"))!=NULL){
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

//���BMPͼƬ������ֵ,���ݹ��࣬IO����ٶȽ�����С�ģ�
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
		for(j=0;j<(infoHeader.biWidth+3)/4*4;j++){
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
		//windowsϵͳ��һ��ɨ������ռ�ֽ���������4���������������������((x+3)/4)*4�ķ�ʽ
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
	//������ͼ������,�������ļ�
	if((new_fp = fopen("D:\\��һ��\\����\\ͼ����\\Conved.bmp","w+b"))!=NULL){
		fwrite (&bfType, sizeof(unsigned short), 1, new_fp);
		fwrite (&fileHeader, sizeof(BITMAPFILEHEADER), 1, new_fp);
		fwrite (&infoHeader, sizeof(BITMAPINFOHEADER), 1, new_fp);
		fwrite (Colors, sizeof(RGBQUAD), 256, new_fp);
		fwrite (newimgData,sizeof(unsigned char)*infoHeader.biHeight*infoHeader.biWidth,1,new_fp);
	}else{
		printf("�������������ļ�ʧ�ܣ�\n");
		exit(0);
	}
	fclose(new_fp);
	return; 
}

//��ɫתΪ�Ҷ�ͼ
void Bmp8ToGray(FILE* fp){
	int i;
	int temp1;							//���ڽ�����������
	RGBQUAD temp2;						//��������
	FILE*new_fp;
	RGBQUAD gray[256];
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
		//���ﲻʹ����ԭɫ��ƽ��ֵ��Ӧʹ������ѧ�Ҷȹ�ʽ����Ϊ���۶���ɫ�����жȽϸ�
		gray[i].rgbBlue = gray[i].rgbGreen = gray[i].rgbRed = (Colors[i].rgbBlue*0.114+Colors[i].rgbRed*0.587+Colors[i].rgbRed*0.299);
		gray[i].rgbReserved = 0;
	}
	if((new_fp = fopen("D:\\��һ��\\����\\ͼ����\\Grayed.bmp","w+b"))!=NULL){
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
	printf("������8bitBMP�ļ�������·��:\n");
	scanf_s("%s",FName,50);
	fp = fopen(FName,"r+b");	            	//�ڴ˴������ļ�·������
	creat(&newimgData,fp);
	creat(&ImgData,fp);
	Bmp8ToGray(fp);								//תΪ�Ҷ�ͼ��
	Adjust_Colors(fp);						    //���������Ի�����ɫ������
	/*Print_Colors(fp);*/						//�����ɫ����Ϣ
	//Print_ImgData(fp);						//�������ֵ
	Conve_ImgData(fp,Sobel_kerx);				//���
	fclose(fp);
	free(newimgData);
	free(ImgData);
	return 0;
}
