#include<stdio.h>
unsigned short bfType;//λͼ�ļ������ͣ�����ΪBM(1-2�ֽڣ�,�����ļ�ͷ����ռ���ֽڣ������ڽṹ���ڻᵼ�´�λ
typedef struct tagBITMAPFILEHEADER
{
    unsigned long bfSize;//λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ��3-6�ֽڣ���λ��ǰ��
    unsigned short bfReserved1;//λͼ�ļ������֣�����Ϊ0(7-8�ֽڣ�
    unsigned short bfReserved2;//λͼ�ļ������֣�����Ϊ0(9-10�ֽڣ�
    unsigned long bfOffBits;//λͼ���ݵ���ʼλ�ã��������λͼ��11-14�ֽڣ���λ��ǰ��
					//�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
}BITMAPFILEHEADER;	

typedef struct tagBITMAPINFOHEADER
{
	unsigned long biSize;//���ṹ��ռ���ֽ�����15-18�ֽڣ�
	long biWidth;//λͼ�Ŀ�ȣ�������Ϊ��λ��19-22�ֽڣ�
	long biHeight;//λͼ�ĸ߶ȣ�������Ϊ��λ��23-26�ֽڣ�
	unsigned short biPlanes;//Ŀ���豸�ļ��𣬱���Ϊ1(27-28�ֽڣ�
	unsigned short biBitCount;//ÿ�����������λ����������1��˫ɫ������29-30�ֽڣ�
	//4(16ɫ����8(256ɫ��16(�߲�ɫ)��24�����ɫ��֮һ
	unsigned long biCompression;//λͼѹ�����ͣ�������0����ѹ��������31-34�ֽڣ�
	//1(BI_RLE8ѹ�����ͣ���2(BI_RLE4ѹ�����ͣ�֮һ
	unsigned long biSizeImage;//λͼ�Ĵ�С(���а�����Ϊ�˲���������4�ı�������ӵĿ��ֽ�)�����ֽ�Ϊ��λ��35-38�ֽڣ�
	long biXPelsPerMeter;//λͼˮƽ�ֱ��ʣ�ÿ����������39-42�ֽڣ�
	long biYPelsPerMeter;//λͼ��ֱ�ֱ��ʣ�ÿ����������43-46�ֽ�)
	unsigned long biClrUsed;//λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ�
	unsigned long biClrImportant;//λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ�
}BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
	unsigned char rgbBlue;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbGreen;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbRed;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	unsigned char rgbReserved;//����������Ϊ0
}RGBQUAD;	//��ɫ��

BITMAPFILEHEADER fileHeader;	//BMP�ļ�ͷ
BITMAPINFOHEADER infoHeader;	//λͼ��Ϣͷ
RGBQUAD Colors[256];			//��ɫ��

/*�������ܣ�������ɫ��
����������ָ����ļ���ָ��
��������ֵ����*/
void Adjust_Colors (FILE* fp){
	int i;
	int temp1;	//���ڽ�����������
	RGBQUAD temp2; //��������
	fread (Colors, sizeof(RGBQUAD), 256, fp);				//������ɫ����256��
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
	rewind (fp);
	fwrite (&bfType, sizeof(unsigned short), 1, fp);
	fwrite (&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite (&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite (Colors, sizeof(RGBQUAD), 256, fp);
}
