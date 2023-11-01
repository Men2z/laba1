#include<iostream>
#include<algorithm>

using namespace std;

double* Gauss(double** Array_A, double* Array_B, int n);
double* Vector_F(double** Array_A, double* Array_B, double* X, int n);
double norma(double* F, int n);
double* Vector_B2(double** Array_A, double* X, int n);
double* difference(double* X1, double* X2, int n);

int main()
{
	setlocale(LC_ALL, "RUS");
	int n;
	cout << "Введите порядок матрицы: ";
	do
	{
		cin >> n;
	} while (n < 0);
	double** Array_A = new double* [n];
	double* Array_B = new double[n];
	double** Copy_A = new double* [n];
	double* Copy_B = new double[n];
	cout << "\nВведите матрицу коэффициентов А: \n";
	for (int i = 0; i < n; i++)
	{
		Array_A[i] = new double[n];
		Copy_A[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			cin >> Array_A[i][j];
			Copy_A[i][j] = Array_A[i][j];
		}
	}
	cout << "\nВведите вектор свободных членов В: \n";
	for (int i = 0; i < n; i++)
	{
		cin >> Array_B[i];
		Copy_B[i] = Array_B[i];
	}
	double* X = Gauss(Array_A, Array_B, n);
	cout << "\nРешение СЛАУ: ";
	for (int i = 0; i < n; i++)
	{
		cout << X[i] << " ";
	}
	cout << endl;
	double* F = Vector_F(Copy_A, Copy_B, X, n);
	cout << "\nВектор невязки F: ";
	for (int i = 0; i < n; i++)
	{
		cout << F[i] << " ";
	}
	cout << endl;
	cout << "Норма вектора невязки F: ";
	double Norma = norma(F, n);
	cout << Norma;
	double* B2 = Vector_B2(Copy_A, X, n);
	double* X2 = Gauss(Copy_A, B2, n);
	cout << "\nРешение вспомогательной системы: ";
	for (int i = 0; i < n; i++)
	{
		cout << X2[i] << " ";
	}
	cout << endl;
	cout << "Относительная погрешность: " << norma(difference(X, X2, n), n) / norma(X, n);
	cout << endl;
	system("pause");
	return 0;
}

double* Gauss(double** Array_A, double* Array_B, int n)
{
	double* X = new double[n];  //массив ответов
	for (int k = 0; k < n; k++) // прямой ход
	{
		for (int i = k + 1; i < n; i++)
		{
			if (abs(Array_A[i][k]) > abs(Array_A[k][k]))
			{
				swap(Array_A[i], Array_A[k]);  //меняются адреса т.к. двумерный массив
				swap(Array_B[i], Array_B[k]);   //меняются значения
			}
		}
		double A_Main = Array_A[k][k];
		if (A_Main == 0)
		{
			cout << "error\n";
			system("pause");
			exit(0);
		}
		for (int i = k; i < n; i++)
		{
			Array_A[k][i] /= A_Main;
		}
		Array_B[k] /= A_Main;
		for (int i = k + 1; i < n; i++)
		{
			double s = Array_A[i][k];
			for (int j = k; j < n; j++)
			{
				Array_A[i][j] -= s * Array_A[k][j];
			}
			Array_B[i] -= s * Array_B[k];
		}
	}
	for (int k = n - 1; k >= 0; k--)  //обратный ход
	{
		X[k] = Array_B[k];
		for (int i = n - 1; i > k; i--)
		{
			X[k] -= Array_A[k][i] * X[i];
		}
	}
	return X;
}

double* Vector_F(double** Array_A, double* Array_B, double* X, int n)
{
	double* result = new double[n];
	for (int i = 0; i < n; i++)
	{
		result[i] = -Array_B[i];
		for (int j = 0; j < n; j++)
		{
			result[i] += Array_A[i][j] * X[j];
		}
	}
	return result;
}

double norma(double* F, int n)
{
	double Norma = abs(F[0]);
	for (int i = 0; i < n; i++)
	{
		Norma = max(F[i], Norma);
	}
	return Norma;
}

double* Vector_B2(double** Array_A, double* X, int n)
{
	double* B2 = new double[n];
	for (int i = 0; i < n; i++)
	{
		B2[i] = 0;
		for (int j = 0; j < n; j++)
		{
			B2[i] += Array_A[i][j] * X[j];
		}
	}
	return B2;
}

double* difference(double* X1, double* X2, int n)
{
	double* x = new double[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = X2[i] - X1[i];
	}
	return x;
}