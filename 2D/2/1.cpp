#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <stdlib.h> 

using namespace std; 

int main () 
{ 
ofstream fout("file.txt"); 

///Описание данных
int const N = 100;			//Размер пространства
int const M = 1000000000;	//Размер времени

double t0;					//Максимальное время для члена u[m][n][p]
double txp;					//Максимальное время для члена u[m+1][n][p]
double txm;					//Максимальное время для члена u[m-1][n][p]
double typ;					//Максимальное время для члена u[m][n+1][p]
double tym;					//Максимальное время для члена u[m][n-1][p]
double tlmax;				//max(t0,tx+,tx-,ty+, ty-) при данной координате
double tmax;				//sup( max(t0,tx+,tx-,ty+, ty-) ) при любой координате 
double tau;					//Размер временного шага
double T;					//Временной промежуток

int i,j,k;					//Индексы по x,y,t

double l;					//Счётчик проверки нуля Kx[] и Ky[]

double tk = 0.2;			//Временной коэффициент

double n;					//Степень гран.условия
double s = 5;				//Степень u в уравнении, член с x и y

double p = 0.1;

double Ac;					//Гран.условие

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

//Задание массива точек сравнения
double D[3][3][11];			//[Номер кривой][Номер угла][Номер высоты]

//Задание массива среднеквадратичного отклонения разностей от среднего [угол]
double R[3];

//Задание массива средних разностей [угол]
double Sr[3];

double Sum;					//Отклонение суммарное

double A1;					//Максимум первой волны

int m1;						//Счётчики проверки массива 1
int m2;						//Счётчики проверки массива 2

cout << "Start of data generation" << endl;

for (n=0.1; n <= 10; n=n+p) 
{


if (n < 10)
{
	p = 1;
}
if (n < 5)
{
	p = 0.5;
}
if (n < 1)
{
	p = 0.2;
}	
if (n < 0.3)
{
	p = 0.1;
}	
	
	
cout << "n = " << n << ". Start." << endl;

m1 = 0;
m2 = 0;
T = 0;	

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
			Kx[i][j]= pow((0.5*(A[i][j]+A[i+1][j])),s);
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
			Ky[i][j]= pow((0.5*(A[i][j]+A[i][j+1])),s);
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
	

//Поиск значений первого массива
	if (((A[7 * N/10][N/2] != 0) || (A[N/2][7 * N/10] != 0)) && (m1 == 0))
	{
			
		A1 = Ac;
		m1=1;
		
		for (j=0; j<11; j++)
		{
//Угол 0
			for (i=0; i<N/2; i++)
			{
				if (A[N/2 + i][N/2] <= (A1 * 0.1 * j ))
				{
					D[1][0][j] = i;
					break;
				}
			}
//Угол 45
			for (i=0; i<N/2; i++)
			{
				if (A[N/2 + i][N/2 + i] <= (A1 * 0.1 * j ))
				{
					D[1][1][j] = sqrt( 2 * pow(i,2) );
					break;
				}
			}			
//Угол 90
			for (i=0; i<N/2; i++)
			{
				if (A[N/2][N/2 + i] <= (A1 * 0.1 * j ))
				{
					D[1][2][j] = i;
					break;
				}
			}					
			
		}
	}


//Поиск значений второго массива
	if (((A[9 * N/10][N/2] != 0) || (A[N/2][9 * N/10] != 0)) && (m2 == 0))
	{
		
		m2=1;
		
		for (j=0; j<11; j++)
		{
//Угол 0
			for (i=0; i<N/2; i++)
			{
				if (A[N/2 + i][N/2] <= (A1 * 0.1 * j ))
				{
					D[2][0][j] = i;
					break;
				}
			}
//Угол 45
			for (i=0; i<N/2; i++)
			{
				if (A[N/2 + i][N/2 + i] <= (A1 * 0.1 * j ))
				{
					D[2][1][j] = sqrt( 2 * pow(i,2) );
					break;
				}
			}			
//Угол 90
			for (i=0; i<N/2; i++)
			{
				if (A[N/2][N/2 + i] <= (A1 * 0.1 * j ))
				{
					D[2][2][j] = i;
					break;
				}
			}					
			
		}
	}

//Условие выхода из цикла
	if ((m2 == 1) && (m1 == 1))
	{
		break;
	}
}

//Подсчёт средних разностей
for (i=0; i<3; i++)
{
	Sr[i]=0;
	for (j=0; j<11; j++)
	{
		Sr[i] = Sr[i] + abs(D[1][i][j] - D[2][i][j]);
	}
	Sr[i] = Sr[i]/11;
}

//Подсчёт среднеквадратичного отклонения
for (i=0; i<3; i++)
{
	R[i] = 0;
	for (j=0; j<11; j++)
	{
		R[i] = R[i] + pow((abs(D[1][i][j] - D[2][i][j]) - Sr[i]),2);
	}
	R[i] = sqrt(R[i]/11);
}



/*
for (k=1; k<3; k++)
{
	for (j=0; j<11; j++)
	{
		fout << D[k][0][j] << " " << D[k][1][j] << " " << D[k][2][j] << endl; 
	}
	fout << endl << endl<< endl;
}

for (i=0; i<3; i++)
{
	fout << R[i] << " "<< Sr[i] << endl; 
}
*/

//Подсчёт среднего по всем углам
//R[1] = 0;
Sum = sqrt((pow(R[0],2) + pow(R[1],2) + pow(R[2],2))/3);
//Sum = sqrt((pow(R[0],2) + pow(R[1],2) + pow(R[2],2))/2);
fout << n << " " << Sum << endl;

cout << "n = "<< n << ". Exit." << endl;

}
 
cout << "Start of animation creation" << endl;

fout.close();
return 0; 

}
