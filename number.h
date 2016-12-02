struct TmpSol
{
	int num[4];
	int a,b;
};

int Correct4Number(int num[4]);

void urand(int num[4]);

void compare(int num1[4],int num2[4],int *a,int *b);

//int conflicit(int Num[4], TmpSol Hist[8], int Count);

void AddTemp(TmpSol Hist[8], int Count, int num[4]);

int GenTemp(int Num[4], struct TmpSol Hist[8], int Count);

