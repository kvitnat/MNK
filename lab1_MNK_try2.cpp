// lab1_MNK_try2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "headers.h"

int main()
{
	FILE* pipe = _popen("C:/gnuplot/bin/gnuplot.exe", "w");
	if (pipe != NULL)
	{
		fprintf(pipe, "set term win\n");
		fprintf(pipe, "plot x * x\n"); //a simple example function
		fprintf(pipe, "set term pngcairo\n");
		fprintf(pipe, "set output \"myFile.png\"\n");
		fprintf(pipe, "replot\n");
		fprintf(pipe, "set term win\n");
		fflush(pipe);
		int a;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		cin >> a;
		_pclose(pipe);
	}
	else
		cout << "Could not open the pipe" << endl;

	return 0;
}
