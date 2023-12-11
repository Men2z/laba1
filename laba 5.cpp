#include <iostream>
#include <cmath>

using namespace std;


double func(double x)  //наша функция
{
	return 0.1 * (x * x) / log10(x);
}

void trapec(double a, double b, double j) // метод трапеции
{
	int n = 4;
	double h; //h
	bool stop = true;
	double otvetBuf = 10;
	double otvet;  // то что будем выводить, финальный ответ
	double suma = 0; //для подсчета суммы
	while (stop == true)
	{
		h = (b - a) / n;
		for (int i = 1; i <= n - 1; (i++))  //цикл для подсчета суммы f(Xi)
		{
			suma += func(a + i * h);

		}
		otvet = (h / 2) * (func(a) + 2 * suma + func(b));
		double k = otvetBuf - otvet;
		if ((k) < j)
		{
			stop = false;
			cout << otvet << endl << "pogresh = " << k << endl;
			cout << "iterac = " << n;
		}
		otvetBuf = otvet;

		suma = 0;
		n = n * 2;
	}

}


void sipson(double a, double b, double j) //метод Симпсона
{
	int n = 2;
	double h = (b - a) / n; //h
	double otvet;
	double sum1 = 0;  //сумирование четных
	double sum2 = 0;  //суммировнание нечетных
	bool stop = true;
	double otvetBuf = 0;
	while (stop)
	{
		sum1 = 0;
		sum2 = 0;
		h = (b - a) / n;
		for (int i = 1; i < n / 2; i++)
		{
			sum1 += func(a + h * (2 * i - 1));
			sum2 += func(a + h * (2 * i));
		}
		otvet = (h / 3) * (func(a) + 4 * (sum1)+2 * (sum2)+func(b));
		double k = otvet - otvetBuf;

		if (k < j)
		{
			stop = false;
			cout << otvet << endl << "pogresh = " << k << endl;
			cout << "iterac = " << n;
		}
		otvetBuf = otvet;
		n = n * 2;
	}
}

int main()
{
	trapec(2, 3.104, 0.000001);
	cout << endl << endl;
	sipson(2, 3.104, 0.000001);
	cout << endl;
}
