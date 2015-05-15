#pragma once
#include "opencv2\core.hpp"

using namespace cv;

//return number of roots
inline int seven_point(const Point2f* m1, const Point2f* m2, Mat& F)
{
	//m1*F*m2=0
	F.create(9, 3, CV_64F);
	double* f = F.ptr<double>();


	Mat A(7, 9, CV_64F);
	double* a = A.ptr<double>();
	//Af=0 f=F.resize(9,1)
	for (int i = 0; i < 7; i++)
	{
		double x0 = m1[i].x, y0 = m1[i].y;
		double x1 = m2[i].x, y1 = m2[i].y;

		a[i * 9 + 0] = x1*x0;
		a[i * 9 + 1] = x1*y0;
		a[i * 9 + 2] = x1;
		a[i * 9 + 3] = y1*x0;
		a[i * 9 + 4] = y1*y0;
		a[i * 9 + 5] = y1;
		a[i * 9 + 6] = x0;
		a[i * 9 + 7] = y0;
		a[i * 9 + 8] = 1;
	}

	//use svd, get the last 2 rows of V(null space)
	Mat U(7, 9, CV_64F);
	Mat V(9, 9, CV_64F);
	Mat W(7, 1, CV_64F);
	SVDecomp(A, W, U, V, SVD::MODIFY_A + SVD::FULL_UV);
	double* f1 = V.row(7).ptr<double>;
	double* f2 = V.row(8).ptr<double>;

	// use det(f) = det(lambda*f1 + (1-lambda)*f2) = 0
	// to find roots
	for (int i = 0; i < 9; i++)
		f1[i] -= f2[i];

	double t0 = f2[4] * f2[8] - f2[5] * f2[7];
	double t1 = f2[3] * f2[8] - f2[5] * f2[6];
	double t2 = f2[3] * f2[7] - f2[4] * f2[6];

	double c[4];

	c[3] = f2[0] * t0 - f2[1] * t1 + f2[2] * t2;

	c[2] = f1[0] * t0 - f1[1] * t1 + f1[2] * t2 -
		f1[3] * (f2[1] * f2[8] - f2[2] * f2[7]) +
		f1[4] * (f2[0] * f2[8] - f2[2] * f2[6]) -
		f1[5] * (f2[0] * f2[7] - f2[1] * f2[6]) +
		f1[6] * (f2[1] * f2[5] - f2[2] * f2[4]) -
		f1[7] * (f2[0] * f2[5] - f2[2] * f2[3]) +
		f1[8] * (f2[0] * f2[4] - f2[1] * f2[3]);

	t0 = f1[4] * f1[8] - f1[5] * f1[7];
	t1 = f1[3] * f1[8] - f1[5] * f1[6];
	t2 = f1[3] * f1[7] - f1[4] * f1[6];

	c[1] = f2[0] * t0 - f2[1] * t1 + f2[2] * t2 -
		f2[3] * (f1[1] * f1[8] - f1[2] * f1[7]) +
		f2[4] * (f1[0] * f1[8] - f1[2] * f1[6]) -
		f2[5] * (f1[0] * f1[7] - f1[1] * f1[6]) +
		f2[6] * (f1[1] * f1[5] - f1[2] * f1[4]) -
		f2[7] * (f1[0] * f1[5] - f1[2] * f1[3]) +
		f2[8] * (f1[0] * f1[4] - f1[1] * f1[3]);

	c[0] = f1[0] * t0 - f1[1] * t1 + f1[2] * t2;
	Mat coeffs(1, 4, CV_64F, c);

	// find 1 to 3 roots 
	Mat roots(1, 3, CV_64F);
	int n = solveCubic(coeffs, roots);
	if (n < 1 || n > 3) return n;

	double* r = roots.ptr<double>();
	for (int k = 0; k < n; k++)
	{
		double lambda = r[k], mu = 1.;
		double s = f1[8] * r[k] + f2[8];

		// normalize that F(3,3) == 1
		if (fabs(s) > DBL_EPSILON)
		{
			mu = 1. / s;
			lambda *= mu;
			f[k*9+8] = 1.;
		}
		else
			f[k * 9 + 8] = 0.;

		for (int i = 0; i < 8; i++)
			f[k * 9 + i] = f1[i] * lambda + f2[i] * mu;
	}

	return n;
}