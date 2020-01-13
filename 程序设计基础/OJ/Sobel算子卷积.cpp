#include<stdio.h>
#include<math.h>

#define Image_Height 150
#define Image_Width 100
#define KerSize 3//卷积核大小

//Sobel算子
int Sobel_kerx[KerSize][KerSize]={
	-1,0,1,
	-2,0,2,
	-1,0,1
};

int Sobel_kery[KerSize][KerSize]={
	1,2,1,
	0,0,0,
	-1,-2,-1
};

unsigned int img[Image_Height][Image_Width]={0};//原图像
unsigned int imgx[Image_Height][Image_Width]={0};//横向边缘化
unsigned int imgy[Image_Height][Image_Width]={0};//纵向边缘化
unsigned int imgxy[Image_Height][Image_Width]={0};//横纵边缘化

void input(){
	int i,j;
	printf("请输入各像素点值:\n");
	for(i=0;i<Image_Height;i++){
		for(j=0;j<Image_Width;j++){
			scanf_s("%d",&img[i][j]);
		}
	}
}

void Convolution(int ker[][KerSize],unsigned newimg[][Image_Width]){
	int i,j,m,n;
	for(i = 0;i < Image_Height;i ++){
		for(j = 0;j < Image_Width;j ++){
			if( i < KerSize-1 || j < KerSize-1 || i > Image_Height-KerSize || j > Image_Width-KerSize ){
				newimg[i][j]=img[i][j];
			}else{
				for(m=i-1;m<=i+1;m++){
					for(n=j-1;n<=j+1;n++){
						newimg[i][j]+=ker[m-i+1][n-j+1]*img[m][n];
					}
				}
			}
		}
	}
}

void Convolution_xy(){
	int i,j;
	for(i=0;i<Image_Height;i++){
		for(j=0;j<Image_Width;j++){
			imgxy[i][j]=(int)sqrt((double)(imgx[i][j]*imgx[i][j]+imgy[i][j]*imgy[i][j]));
		}
	}
}

void print(unsigned newimg[][Image_Width]){
	int i,j;
	putchar(10);
	for(i=0;i<Image_Height;i++,putchar(10)){
		for(j=0;j<Image_Width;j++){
			printf("%d ",newimg[i][j]);
		}
	}
}

int main(){
	input();
	Convolution(Sobel_kerx,imgx);
	print(imgx);
	Convolution(Sobel_kery,imgy);
	print(imgy);
	Convolution_xy();
	print(imgxy);
	return 0;
}