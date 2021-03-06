#include <stdlib.h>
#include <stdio.h>


double* predict(double *x, double w_0, double *w, double *v, int n, int p, int k, double *y_predict) {
	for (int i = 0; i < n; ++i) {
		y_predict[i] = w_0;
		for (int j = 0; j < p; ++j) {
			y_predict[i] += w[j] * x[i * p + j];
		}
		for (int f = 0; f < k; ++f) {
			double coeff_1 = 0., coeff_2 = 0.;
			for (int j = 0; j < p; ++j) {
				coeff_1 += v[j * k + f] * x[i * p + j];
				coeff_2 += v[j * k + f] * x[i * p + j] * v[j * k + f] * x[i * p + j];
			}
			y_predict[i] += coeff_1 * coeff_1 + coeff_2;
		}
	}

	double *result = (double *)malloc(sizeof(double) * 2);
	result[0] = 0.;
	result[1] = 0.;
	return result;
}

double* get_w_star(double *x, double *e, double *w, double *w_star, double l_w, int n, int p) {
	double coeff_1, coeff_2;

	for (int l = 0; l < p; ++l) {
		coeff_1 = 0.;
		coeff_2 = 0.;
		for (int i = 0; i < n; ++i) {
			coeff_1 += x[i * p + l] * x[i * p + l];
			coeff_2 += x[i * p + l] * e[i];
		}
		w_star[l] = (w[l] * coeff_1 + coeff_2) / (coeff_1 + l_w);
	}

	double *result = (double *)malloc(sizeof(double) * 2);
	result[0] = 0.;
	result[1] = 0.;
	return result;
}

double* get_v_star(double *x, double *e, double *v, double *v_star, double l_v, int n, int p, int k) {
	double coeff_1, coeff_2, h_l_f_i;
	double *q = (double *)malloc(sizeof(double) * k * n);
	for (int f = 0; f < k; ++f) {
		for (int i = 0; i < n; ++i) {
			q[f * n + i] = 0.;
			for (int l = 0; l < p; ++l) {
				q[f * n + i] += v[l * p + f] * x[i * p + l];
			}
		}
		for (int l = 0; l < p; ++l) {
			coeff_1 = 0.;
			coeff_2 = 0.;
			for (int i = 0; i < n; ++i) {
				h_l_f_i = x[i * p + l] * (q[f * n + i] - v[l * p + f] * x[i * p + l]);
				coeff_1 += h_l_f_i * h_l_f_i;
				coeff_2 += h_l_f_i * e[i];
			}
			printf("Here");/*
			printf("%f", coeff_2);
			printf("%f", coeff_1);
			printf("%f", v[l * k + f]);
			v_star[l * k + f] = (v[l * k + f] * coeff_1 + coeff_2) / (coeff_1 + 1.);*/
		}
	}
	free(q);

	double *result = (double *)malloc(sizeof(double) * 2);
	result[0] = 0.;
	result[1] = 0.;
	return result;
}