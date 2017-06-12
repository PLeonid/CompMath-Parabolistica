#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <stdlib.h> 

using namespace std; 

int main () 
{ 
//Задание переменных, считывание
ifstream fin("file.txt"); 

int N = 151;
int M = 10;
double p = 1.01;

int i,j,k;

double ***A = new double** [M];
for (i = 0; i < M; i++)
	{
		A[i] = new double* [N];
		for (j = 0; j < N; j++)
		{
			A[i][j] = new double [3];
		}
	}

double *B = new double [M];


for (i=0; i < M; i++)
{
	for (j=0; j < N; j++)
	{
		for (k=0; k < 3; k++)
		{
			fin >> A[i][j][k];
		}
	}
}

fin.close();

//Тело
for (i=0; i < M; i++)
{	
	B[i] = A[i][0][2];
	for (j=0; j < N; j++)
	{
		B[i] = min(B[i], A[i][j][2]);
	}
}

//Вывод
ofstream fout("file2.txt"); 

for (i=0; i < M; i++)
{
//	fout << B[i]<< endl;
	for (j=0; j < N; j++)
	{
		if (A[i][j][2] <= p * B[i])
		{
			for (k=0; k < 3; k++)
			{
				fout << A[i][j][k] << " ";
			}
			fout << 1/A[i][j][1]<< " ";
			fout << endl;
		}
	}
//	fout << endl;
}

fout.close();

return 0; 
}
