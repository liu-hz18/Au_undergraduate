
#pragma once  //�Ⱥ궨�尲ȫ����
#include <list>
//��Ⱥ��
struct Community{
	int sumIn, sumTot;//��Ⱥ�ڲ��ı�Ȩ�͡���Ⱥ������������Ⱥ���ߵı�Ȩ��
	Community(){
		sumIn = sumTot = 0;
	}
};

//�򻯵ı���
struct reducedEdge{
	int weight, to;
	reducedEdge(int t, int w = 0): to(t){
		weight = w;
	}
};

//�򻯵Ľڵ���
struct reducedNode{
	int community;//�����ĸ���Ⱥ
	list<reducedEdge> neighbor; //���ӵı�
};
