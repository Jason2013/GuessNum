#include "StdAfx.h"
#include "number.h"

int Correct4Number(int num[4])
{
	int i,j;
	for (i=0;i<=3;i++) //num[i] Must >=0 And <=9
		if (num[i]>9||num<0) return 0;
	for (i=0;i<=2;i++)
		for(j=i+1;j<=3;j++)
			if (num[i]==num[j]) return 0;
	return 1;
}

void compare(int num1[4],int num2[4],int *a,int *b)
{
	int i,j,ra=0,rb=0;
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			if (num1[i]==num2[j])
				if (i==j) ra++;
				else rb++;
	*a=ra;
	*b=rb;
}

void urand(int num[4])
{
	int n[10], i, sel;
	int mod=10;
	for (i=0; i<10; i++)
		n[i]=i;

	for (i=0; i<4; i++)
	{
		sel = rand()%mod;
		num[i] = n[sel];
		mod--;
		n[sel]=n[mod];
	}

}



int conflicit(int Num[4], TmpSol Hist[8], int Count)
{
	int i,a,b;
	for (i=0;i<Count;i++)
	{
		compare(Num,Hist[i].num,&a,&b);
		if (a!=Hist[i].a||b!=Hist[i].b)
			return 1;
	}
	return 0;
}
void AddTemp(TmpSol Hist[8], int Count, int num[4])//;//const TempSol& ts)
{
	Hist[Count].num[0]=num[0];
	Hist[Count].num[1]=num[1];
	Hist[Count].num[2]=num[2];
	Hist[Count].num[3]=num[3];
//
//	solutions[nSoluCount]=ts;
//	nSoluCount++;
}

int GenTemp(int Num[4], TmpSol Hist[8], int Count)
{
	for (Num[0]=0;Num[0]<=9;Num[0]++)
		for (Num[1]=0;Num[1]<=9;Num[1]++)
		{
			if (Num[1]==Num[0]) continue;
			for (Num[2]=0;Num[2]<=9;Num[2]++)
			{
				if (Num[2]==Num[1]||Num[2]==Num[0]) continue;
				for (Num[3]=0;Num[3]<=9;Num[3]++)
				{
					if (Num[3]==Num[2]||Num[3]==Num[1]||Num[3]==Num[0]) continue;
					if (!conflicit(Num, Hist, Count)) return 1;
				}
			}
		}
	return 0;
}





/*
class UniqueRnd
{
private:
	int bottom,mod;
	int num[32];
public:
	UniqueRnd();
	void reset(int b,int t);
	int grnd();
};
UniqueRnd::UniqueRnd(){	randomize();}

void UniqueRnd::reset(int b,int t)
{
	int i;
	bottom=b;
	mod=t-b+1;
	for (i=0;i<mod;i++) num[i]=i;
}
int UniqueRnd::grnd()
{
	int select,rcode;
	if (!mod) return -1; //Maybe Duplication
	select=rand()%mod;
	rcode=num[select]+bottom;
	mod--;
	num[select]=num[mod];
	return rcode;
}
*/