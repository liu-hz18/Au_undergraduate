#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <ctime>
using namespace std;
//**************************************************************
//     һά�����˶�
//
// ȷ������ʱ��t������ʱ����dt�����ģʽoutput_opt��������С�
// tȡ30���ӣ���1800�룩����
// ��t�ڽ���100�����ڵĲ�������t/dt<=100
double t = 1800.;//s
double dt = 30.;//s
// ���ģʽ 1���۲�ʱ�̣��룩��΢�����꣨΢�ף���
//             �۲�ʱ������΢��λ�ƣ�΢�ף�
// ���ģʽ 2���۲�ʱ��΢�����꣨΢�ף�
// ���ģʽ 3���۲�ʱ������΢��λ�ƣ�΢�ף�
int output_opt = 1;
//**************************************************************

double temp = 293.;//K
double visc = 0.1;//cP=10^-3 Pa*s
double diam = 1.0;//micro meter=10^-6 m

double x0 = 0.;
double v0 = 0.;

int idg;//random seed

int main() {
    srand((unsigned)time(0));
    int np = int(t / dt)+1;
    double *x;
    double tt;

    void brown(double*, const int);

    x = new double[np]; 

    brown(x, np);

    if (output_opt == 1) {
        cout << "ʱ�̡��롿" << "\t" << "���꡾΢�ס�" << "\t" << "λ�ơ�΢�ס�" << endl; 	
        cout << 0 << "\t" << "\t" << "\t" << x[0] << endl;
        tt = dt;
        for (int l = 1;l < np;l++) {
	        printf("%4.1f \t \t %5.6f \t %5.6f \n", tt, x[l], x[l]-x[l-1] );
            tt = tt + dt;
        }
    } else if(output_opt == 2) {
        for (int l = 0;l < np;l++) {
	        cout << x[l] << endl;
        }		
    } else if(output_opt == 3) {
        for (int l = 1;l < np;l++) {
            cout << x[l]-x[l-1] << endl;
        }		
    }
    delete[] x;
    return 0;
}

void brown(double *x, const int np){
    const double kb = 1.380649;
    const double masse = 1.0;//micro gram=10^-9 kg
    double d = 0.1;//s
    double kbT, A, stm, gamma;
    double c1,c2;
    int f,nt;
    double *xx, *vv, *r;
 
    double gaussnoise(int);

    kbT = kb * temp / 100.;
    A = 2.0 * kbT * 3.0 * 3.1415926 * visc * diam;
    stm = sqrt(kbT / masse);
    gamma = A / (2.0 * kbT);
    c1 = 1. / (1. + gamma / masse * d);
    c2 = d * sqrt(2. * gamma / masse / d);

    f = int(dt / d);

    if (f == 0) {
        d = dt;
        f = 1;
        nt = np;
    }
    else {
        d = dt / f;
        nt = np * f;
    }

    xx = new double[nt];
    vv = new double[nt];
    r = new double[nt];

    xx[0] = x0 / stm;
    vv[0] = v0 / stm;

    for (int j = 1;j < nt;j++) {
        r[j] = gaussnoise(idg);
        xx[j] = xx[j - 1] + d * vv[j - 1];
        vv[j] = c1 * (vv[j - 1] + c2 * r[j]);
    }

    for (int j = 0;j < nt;j++) {
        xx[j] = xx[j]*stm;
        vv[j] = vv[j]*stm;
        if (j == j / f * f) {
            x[j/f] = xx[j];
        }
    }

    delete[] xx;
    delete[] vv;
    delete[] r;
}

double gaussnoise(int idum1) {
    int idum = idum1;
    double  gasdev;
    int iset;
    double fac, gset, rsq, v1, v2;
    double U1, U2;
    iset = 0;
    gset = 0.0;
    if (iset == 0) {
        do {
            U1 = (double)rand() / RAND_MAX;
            U2 = (double)rand() / RAND_MAX;
            v1 = 2. * U1 - 1;
            v2 = 2. * U2 - 1;
            rsq = v1 * v1 + v2 * v2;
        } while (rsq >= 1 || rsq == 0);
        fac = sqrt(-2. * log(rsq) / rsq);
        gset = v1 * fac;
        gasdev = v2 * fac;
        iset = 1;
    } else {
        gasdev = gset;
        iset = 0;
    }
    return gasdev;
}