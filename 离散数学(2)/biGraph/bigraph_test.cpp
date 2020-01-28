
#include "bigraph.h"

int main(){
	int n, m, e;
	scanf("%d%d%d", &n, &m, &e);
	
	assert(n == m);//��֤���Խ������ƥ��

	//�����㷨��Ҫ�����ܣ�û��reset();
	biGraph G(n, m);
	//���ƥ�䲿��,m==n,Ӧ��֤������ȫƥ��
	for(int i = 0; i < e; i++){
		int f, t, w;
		scanf("%d%d%d",&f, &t, &w);
		if(f > n || t > m)continue;
		f--, t--;//������1��ʼ��Ҫ-1
		G.addEdge(f, t, w);
	}
	printf("%d\n", G.bestMatchKM());
	//printf("%d\n", G.minMatch());
	
	/*
	//���ƥ�䲿�� m n���Բ��� 
	for(int i = 0; i < e; i++){
		int f, t;
		scanf("%d%d", &f, &t);
		if(f > n || t > m)continue;
		f--, t--;//������1��ʼ��Ҫ-1
		G.addEdge(f, t);
	}
	printf("%d\n", G.maxmatch());
	*/

	//���ƥ�����
	G.printMatch();
	return 0;
}
