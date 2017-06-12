#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <stdlib.h> 

using namespace std; 

int main () 
{ 
ofstream fout("file.txt"); 

///Описание данных
int const N = 50;			//Размер пространства
int const M = 100100;		//Количество временных шагов
int const w = 100;			//Частота вывода

double t0;					//Максимальное время для члена u[m][n][p]
double txp;					//Максимальное время для члена u[m+1][n][p]
double txm;					//Максимальное время для члена u[m-1][n][p]
double typ;					//Максимальное время для члена u[m][n+1][p]
double tym;					//Максимальное время для члена u[m][n-1][p]
double tlmax;				//max(t0,tx+,tx-,ty+, ty-) при данной координате
double tmax;				//sup( max(t0,tx+,tx-,ty+, ty-) ) при любой координате 
double tau;					//Размер временного шага
double T = 0;				//Временной промежуток

int i,j,k;					//Индексы по x,y,t

double l;					//Счётчик проверки нуля Kx[] и Ky[]

double tk = 0.2;			//Временной коэффициент
double n =  0.5;			//Степень гран.условия
double sx = 2;				//Степень u в уравнении, член с x
double sy = 2;				//Степень u в уравнении, член с y

double Ac;					//Гран.условие

int o = 0;
int f = M/w;

//Задание массива данных
double **A = new double* [N+1];
for (i = 0; i < N+1; i++)
	A[i] = new double [N+1];

//Задание вспомогательного массива данных
double **B = new double* [N+1];
for (i = 0; i < N+1; i++)
	B[i] = new double [N+1];

//Задание массива коэфф-тов по x
double **Kx = new double* [N+1];
for (i = 0; i < N+1; i++)
	Kx[i] = new double [N+1];

//Задание массива коэфф-тов по y
double **Ky = new double* [N+1];
for (i = 0; i < N+1; i++)
	Ky[i] = new double [N+1];


cout << "Start of data generation" << endl;


///Ввод начальных данный
for (i=0; i<N+1; i=i+1)
{
	for (j=0; j<N+1; j=j+1)
	{
		B[i][j] = 0;
		A[i][j] = 0;
	}
}

//Края массивов коэфф-тов
for (i=0; i<N+1; i++)
{
	Kx[N][i] = 0;
	Ky[i][N] = 0;
}



///Временной цикл
for (k=1; k<=M; k++)
{

//Граничные условия
	A[N/2][N/2] = pow(k,n);
	Ac = A[N/2][N/2]; 
	for (i=0; i<N+1; i++)
	{
		A[0][i] = 0;
		A[i][0] = 0;
		A[N][i] = 0;
		A[i][N] = 0;
	}
        
    l=0;
//Нахождение членов массивов Kx[] и Ky[]
	for (i=0; i<N; i++)
	{
		for (j=0; j<N+1; j++)
		{
			Kx[i][j]= pow((0.5*(A[i][j]+A[i+1][j])),sx);
			if (Kx[i][j] != 0)
			{ 
				l++;
			}
		}
	}

	for (i=0; i<N+1; i++)
	{
		for (j=0; j<N; j++)
		{
			Ky[i][j]= pow((0.5*(A[i][j]+A[i][j+1])),sy);
			if (Ky[i][j] != 0)
			{ 
				l++;
			}
		}
	}
 
//Нахождение нужного временного промежутка
	for (i=1; i<N; i++)
	{
		for (j=1; j<N; j++)
		{
			t0  = 2/(Kx[i][j]+Kx[i-1][j]+Ky[i][j]+Ky[i][j-1]);
			txp = 1/Kx[i][j];
			txm = 1/Kx[i-1][j];
			typ = 1/Ky[i][j];
			tym = 1/Ky[i][j-1];

			tlmax = min(t0,txp);		
			tlmax = min(tlmax,txm);	
			tlmax = min(tlmax,typ);
			tlmax = min(tlmax,tym);

			if ((i==1) && (j==1))
			{ 
				tmax = tlmax;
			}
		
			tmax = min(tmax, tlmax);
		}
	}
	
	tau = tk * tmax;
	if (l == 0)
		{ 
			tau = 1;
		}
	T = T+tau;

 
//Переход к следующему шагу
	for (i=1; i<N; i=i+1)
	{
		for (j=1; j<N; j++)
		{  	
			B[i][j]= A[i][j] * (1 - tau * (Kx[i][j]+Kx[i-1][j]+Ky[i][j]+Ky[i][j-1])) + A[i+1][j] * (tau * Kx[i][j]) + A[i-1][j] * (tau * Kx[i-1][j]) + A[i][j+1] * (tau * Ky[i][j]) + A[i][j-1] * (tau * Ky[i][j-1]);
		}
	}

//Переход от вспомогательного массива
	for (i=0; i<N+1; i++)
	{
		for (j=0; j<N+1; j++)
		{
			A[i][j] = B[i][j];
		}
	}
	A[N/2][N/2] = Ac;
	
	
///Вывод данных
	if((k % w) == 0)
	{
		o++;
		if ((o % 100) == 0)
		{
			cout << o << "/" << f << endl;
			cout << "T=" << T << endl;
		}
		fout << endl << endl<< endl;
		for (i=0; i<N+1; i=i+1)
		{
			for (j=0; j<N+1; j=j+1)
			{  
				fout << i << " " << j << " " << A[i][j] << endl; 
			}
			fout << endl;
		}
	}


}

cout << "End of data generation" << endl;
cout << "Start of animation creation" << endl;

fout.close();
return 0; 

}
