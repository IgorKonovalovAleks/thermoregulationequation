#pragma once
#define _USE_MATH_DEFINES
#include<vector>
#include<math.h>
#include<iostream>

class Solver {

private:
	const double T = 10.0;
	const double X = 1.0;
	const double t0 = 0.0;
	const double x0 = 0.0;
	bool valid;
	

	inline double vi0(int i) {
		return 1.0 - (double)i * (double)i * h * h;
	}

	inline double v0j(int j) {
		return cos(tau * (double)j);
	}

	inline double vnj(int j) {
		return sin(4 * tau * (double)j);
	}

	inline double solve_ij(int i, int j) {
		return 3.0 * tau * (v[j - 1][i - 1] - 2.0 * v[j - 1][i] + v[j - 1][i + 1]) / (h * h)
			+ pow(tau, 2.0) * ((double)j - 1) / (1.0 + tau * ((double)j - 1)) * cos((double)i * M_PI * h)
			+ v[j - 1][i];
	}


public:
	bool stepRequirement() {
		if (tau < (h * h) / (2 * sqrt(3)))
			return true;
		else
			return false;
	}

	std::vector<std::vector<double>> v;
	int N;
	int M;
	double tau;
	double h;

	void solve(int n, int m) {
		N = n;
		M = m;
		tau = (T - t0) / M;
		h = (X - x0) / N;
		v = std::vector<std::vector<double>>(M + 1);
		for (int j = 0; j <= M; j++) {
			v[j] = std::vector<double>(N + 1);
			v[j][0] = v0j(j);
			v[j][N] = vnj(j);
		}
		for (int i = 1; i < N; i++) {
			v[0][i] = vi0(i);
		}
		for (int j = 1; j <= M; j++) {
			for (int i = 1; i < N; i++) {
				v[j][i] = solve_ij(i, j);
			}
		}
		valid = true;
	}

	Solver() { 
		valid = false;
		N = 0;
		M = 0;
	}

};
