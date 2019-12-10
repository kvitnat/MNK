#pragma once
#include "headers.h"
class MatrixForC
{
	double** matrix;
	int n, m;
public:
	MatrixForC();
	MatrixForC(int n1, int m1);
	MatrixForC(vector<Point*> points, int degree);
	MatrixForC step(int counter);
	void swapTheLines(int l, int k);

	MatrixForC operator*(MatrixForC m2);
	MatrixForC(char, int n1);
	double* X();

};

