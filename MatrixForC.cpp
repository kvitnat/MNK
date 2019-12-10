#include "MatrixForC.h"

MatrixForC::MatrixForC():matrix(nullptr), n(0), m(0)
{

}

MatrixForC::MatrixForC(int n1, int m1)
{
	n = n1;
	m = m1;
	matrix = new double* [n];
	for (int i = 0; i < n; ++i)
		matrix[i] = new double[m];
}

MatrixForC::MatrixForC(vector<Point*> points, int degree)
{
	n = degree;
	m = n + 1;
	matrix = new double* [n];
	for (int i = 0; i < n; ++i)
		matrix[i] = new double[m];

	for (int i = 0; i < n + n - 1; ++i)
	{
		double sum = 0;
		for (int l = 0; l < points.size(); ++l)
			sum += pow(points[l]->X, i);

		for (int j = 0; j <= i && i < n; ++j)
			matrix[j][i - j] = sum;

		for (int j = n - 1; j > 0 && i >= n && i - j < n; --j)
			matrix[j][i - j] = sum;
	}

	for (int i = 0; i < n; ++i)
	{
		double sum = 0;
		for (int j = 0; j < points.size(); ++j)
			sum += points[j]->Y * pow(points[j]->X, i);
		matrix[i][n] = sum;
	}
}

MatrixForC MatrixForC::step(int counter)
{
	int indexMax = counter;
	for (int i = counter + 1; i < n; ++i)
		if (abs(matrix[i][counter]) > abs(matrix[indexMax][counter]))
			indexMax = i;

	MatrixForC A = *this;
	A.swapTheLines(counter, indexMax);

	MatrixForC M('e', n);
	M.matrix[counter][counter] = 1 / A.matrix[counter][counter];

	for (int i = counter + 1; i < n; ++i)
		M.matrix[i][counter] = -A.matrix[i][counter] / A.matrix[counter][counter];

	
	*this = M * A;
	return A;
}

void MatrixForC::swapTheLines(int l, int k)
{
	if (l >= n || k >= n)
	{
		cout << "error - swaping the lines\n";
		return;
	}

	double* temp = new double[n + 1];
	for (int i = 0; i < n + 1; ++i)
		temp[i] = matrix[l][i];

	for (int i = 0; i < n + 1; ++i)
		matrix[l][i] = matrix[k][i];

	for (int i = 0; i < n + 1; ++i)
		matrix[k][i] = temp[i];

	delete temp;
}

MatrixForC MatrixForC::operator*(MatrixForC m2)
{
	try
	{
		if (m != m2.n)
			throw;
	}
	catch (...)
	{
		cout << "Error - multiplying matrix\n";
	}

	MatrixForC res(n, m2.m);

	for (int i = 0; i < res.n; ++i)
		for (int j = 0; j < res.m; ++j)
		{
			double r = 0;
			for (int k = 0; k < n; ++k)
				r += matrix[i][k] * m2.matrix[k][j];
			res.matrix[i][j] = r;
		}
	return res;
}

MatrixForC::MatrixForC(char, int n1)
{
	n = n1;
	m = n1;
	matrix = new double* [n];
	for (int i = 0; i < n; ++i)
		matrix[i] = new double[m];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			matrix[i][j] = 0;
	for (int i = 0; i < n; ++i)
		matrix[i][i] = 1;

}

double* MatrixForC::X()
{
	double* x = new double[n];
	for (int i = n - 1; i >= 0; --i)
	{
		double sum = 0;
		x[i] = matrix[i][m - 1];
		for (int j = i + 1; j < n; ++j)
			sum += x[j] * matrix[i][j];
		x[i] -= sum;
	}
	
	return x;
}