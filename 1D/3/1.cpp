#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <stdlib.h> 

using namespace std; 

int main () 
{ 
ofstream fout("file.txt"); 


//Описание данных
int const N = 300;
int const M = 50000001;

double k = 0.3;

double t1;
double t2;
double t3;
double tlmax;
double tmax;
double tau;
double T;

int i,j;

int m1;
int m2;

double l;

double s;
double n;

double *A = new double [N+1];
double *B = new double [N+1];
double *K = new double [N];

double R[4][2];
double Z;

//Цикл по степени в ур-е
//for (s= 0.5; s < 5.1; s = s + 0.5)
for (s= 0.5; s < 5.1; s = s + 0.1)
{

//Цикл по стерени гран.условия
//for (n= 0.1; n < 2.10; n = n + 0.1)
for (n= 0.1; n < 2.01; n = n + 0.01)
{

T=0;
m1=0;
m2=0;
	
//Ввод начальных данный
for (i=1; i<N; i=i+1)
{
	B[i] = 0;
	A[i] = 0;
}

//Временной цикл
for (j=1; j<=M; j++)
{

//Граничные условия
	A[N]= 0;
	A[0]= pow(T,n); 

    
    l=0;
//Нахождение членов массива K[]
	for (i=0; i<N; i=i+1)
	{
		K[i]= pow((0.5*(A[i]+A[i+1])),s);
	    if (K[i] != 0)
		{ 
			l++;
		}
	}

 
//Нахождение нужного временного промежутка
	for (i=1; i<N; i++)
	{
		t1 = 2/(K[i]+K[i-1]);
		t2 = 1/K[i];
		t3 = 1/K[i-1];

		tlmax = t1;		
		
		if (tlmax > t2)
		{ 
			tlmax = t2;
		}

		if (tlmax > t3)
		{ 
			tlmax = t3;
		}

		if (i==1)
		{ 
			tmax = tlmax;
		}
		
		if (tmax > tlmax)
		{ 
			tmax = tlmax;
		}
	}
	tau = k * tmax;
	if (l == 0)
		{ 
			tau = 1;
		}
	T = T+tau;

 
//Переход к следующему шагу
	for (i=1; i<N; i=i+1)
	{    	
		B[i]= A[i] * (1 - tau * (K[i]+K[i-1])) + A[i+1] * (tau * K[i]) + A[i-1] * (tau * K[i-1]);
	}


//Переход от вспомогательного массива
	for (i=1; i<N; i=i+1)
	{
		A[i] = B[i];
	}

	
//Нахождение разностей
//	if (j == 25000)
	if ((A[4 * N/6] != 0) && (m1 == 0))
	{
		m1 = 1;
		Z = A[1];
		R[0][0] = 1;
		for (i=1; i<N; i=i+1)
		{
			if (A[i] <= 2 * Z/3)
			{
				R[1][0]=i;
				i=N;
			}
		}
		for (i=1; i<N; i=i+1)
		{
			if (A[i] <= Z/2)
			{
				R[2][0]=i;
				i=N;
			}
		}
		for (i=1; i<N; i=i+1)
		{
			if (A[i] <= Z/3)
			{
				R[3][0]=i;
				i=N;
			}
		}
	}
	
//	if (j == 50000)	
	if ((A[5 * N/6] != 0) && (m2 == 0))
	{
		m2 = 1;
		for (i=1; i<N; i=i+1)
		{
			if (A[i] <= Z)
			{
				R[0][1]=i;
				i=N;
			}
		}
		for (i=1; i<N; i=i+1)
		{
			if (A[i] <= 2 * Z/3)
			{
				R[1][1]=i;
				i=N;
			}
		}
		for (i=1; i<N; i=i+1)
		{
			if (A[i] <= Z/2)
			{
				R[2][1]=i;
				i=N;
			}
		}
		for (i=1; i<N; i=i+1)
		{
			if (A[i] <= Z/3)
			{
				R[3][1]=i;
				i=N;
			}
		}
	}
	
	//Условие выхода из цикла
	if ((m2 == 1) && (m1 == 1))
	{
		break;
	}

}

//Расчёт результатов
R[0][0]=R[0][1]-R[0][0];
R[1][0]=R[1][1]-R[1][0];
R[2][0]=R[2][1]-R[2][0];
R[3][0]=R[3][1]-R[3][0];


R[1][1] = 	(R[0][0] + R[1][0] + R[2][0] + R[3][0])/4;	
R[0][0]= sqrt( pow((R[0][0] - R[1][1]),2) + pow((R[1][0] - R[1][1]),2) + pow((R[2][0] - R[1][1]),2) + pow((R[3][0] - R[1][1]),2));


//Вывод данных
fout << s << " " << n << " " << R[0][0] <<  endl;

cout << "s = " << s << " n = " << n << " " <<  endl;

}
fout << endl;
}

fout.close();
return 0; 
}
