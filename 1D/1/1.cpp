#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <stdlib.h> 

using namespace std; 

int main () 
{ 
ofstream fout("file.txt"); 


//Описание данных
int const N = 1500;				//Размер пространства
int const M = 1008000;			//Количество временных шагов

double k = 0.3;					//Костыльный коэфф-т подсчёта времени

double t1;
double t2;
double t3;
double tlmax;
double tmax;

double tau;						//Временной шаг
double T = 0;					//Время

int i,j;						//Счётчики

double l;						//Счётчик проверки нуля K[]

double s = 1;					//Степень ур - я
double n = 3;					//Степень гран. условия

double *A = new double [N+1];	//Массив данных
double *B = new double [N+1];	//Массив данных вспомогательный
double *K = new double [N];		//Массив коэфф-тов в разностной схеме


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

 
//Нахождение нужного временного промежутка методом костыля
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

	
//Вывод данных
	if((j%2000) == 0)
	{
	fout << endl << endl<< endl;
	for (i=1; i<N; i=i+1)
	{ 
 		fout << i << " " << A[i] << endl; 
	}
	}
}

fout.close();
return 0; 
}
