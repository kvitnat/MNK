#include "headers.h"

ostream& operator<< (ostream& s, const Point* p)
{
	s.precision(5);
	s << "(" << p->X << "; " << p->Y << ") ";
	return s;
}

ofstream& operator<< (ofstream& s, const Point* p)
{
	s << p->X << " " << p->Y << "\n";
	return s;
}

double function(double x);
double error(double x);
string polinom(double* C, int n);

int main()
{
	setlocale(LC_ALL, "rus");
	int n = 20; //points
	int m = 4; //polynomial degree

	vector<Point*> points;
	double a = -2.5, b = 2; 
	double h = (b - a) / (n - 1.);
	srand(time(NULL));
	for (double l = a; l <= b; l += h)
	{
		Point* p = new Point(l, function(l) + error(l));
		points.push_back(p);
	}

	for (int i = 0; i < points.size(); ++i)
		cout << points[i] << '\n';

	ofstream fout;
	fout.open("C:/Users/admin/Documents/study/3rd_year/NumMethods/points.txt");
	for (int i = 0; i < points.size(); ++i)
		fout << points[i];
	fout.close();

	MatrixForC* matrix = new MatrixForC(points, m);
	for (int i = 0; i < m; ++i)
		matrix->step(i);
	double* C = matrix->X();
	
	string thePolinom = polinom(C, m);
	cout << '\n' << thePolinom;
	string command = "plot \'C:/Users/admin/Documents/study/3rd_year/NumMethods/points.txt\', " + thePolinom + ", " +"x * x * x + 3.5 * x * x - 2 * x + 1\n";
	ostringstream aS, bS;
	aS << a; bS << b;
	string rangeCommand = "set xrange [" + aS.str() + ":" + bS.str() + "]\n";

		
	FILE* pipe = _popen("C:/gnuplot/bin/gnuplot.exe", "w");
	if (pipe != NULL)
	{
		fprintf(pipe, "set term win\n");
		fprintf(pipe, rangeCommand.c_str());
		fprintf(pipe, command.c_str()); 
		fflush(pipe);
		cin.clear();
		cin.get();
		_pclose(pipe);
	}
	else
		cout << "Could not open the pipe" << endl;

	return 0;
}

double function(double x)
{
	return x * x * x + 3.5 * x * x - 2 * x + 1;
}

double error(double x)
{
	
	double percents = rand() % 100 + 1.;
	if (rand() % 2 == 0)
		percents *= -1;
	return 0.05 * function(x) * percents / 100;
}

string polinom(double* C, int n)
{
	string polinom = "";
	for (int i = 0; i < n; ++i)
	{
		ostringstream strs;
		if (C[i] > 0)
			polinom += "+ ";
		else
			polinom += "- ";
		strs << abs(C[i]);
		polinom += strs.str() + " ";
		for (int j = 0; j < i; ++j)
			polinom += "* x ";

	}
	//polinom += '\n';
	return polinom;
}