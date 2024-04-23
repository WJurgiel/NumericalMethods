#include <iostream>
#include <vector>
#include <algorithm>
#include "FunctionHandler.h"
#define SMALL_NUM 1e-05
using Factors = std::vector<float>;
using Exponents = std::vector<int>;
using Operators = std::vector<char>;
using Matrix = std::vector<std::vector<double>>;

/// <summary>
/// [0] -> x_i
/// [1] -> A_i
/// </summary>
const Matrix quadrature_2 = 
{
	{-0.577350269, 0.577350269}, 
	{1.0, 1.0}						
};
/// <summary>
/// [0] -> x_i
/// [1] -> A_i
/// </summary>
const Matrix quadrature_3 =
{
	{-0.774596669, 0.0, 0.774596669},
	{0.555555555, 0.888888888, 0.555555555}
};
/// <summary>
/// [0] -> x_i
/// [1] -> A_i
/// </summary>
const Matrix quadrature_4 =
{
	{-0.861136311,-0.339981043,0.339981043 ,0.861136311},
	{0.347854845,0.652145154,0.652145154,0.347854845}
};
/*
	(b-a)/2 = sum (i -> n) A_i f(t_i) gdzie t_i = (a+b)/2 + (b-a)x_i/2
	*/
void print_matrix(Matrix matrix) {
	for (auto x : matrix) {
		for (auto y : x) {
			std::cout << y << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
double gauss_legrenge(double(*cal)(double x), int n, double left, double right) {
	double factor = (right - left) / 2.0;
	Matrix quadratures;
	int8_t ptr;
	switch (n) {
	case 2: quadratures = quadrature_2; break;
	case 3: quadratures = quadrature_3; break;
	case 4: quadratures = quadrature_4; break;
	default: exit(-20);
	}
	double sum = 0;

	//std::cout << "{\n";
	////print_matrix(quadratures);
	//std::cout << "}\n";
	for (int8_t i = 0; i <= n - 1; i++) {
		double t_i = (left + right) / 2 + (right - left) * quadratures[0][i] / 2.0;
		sum += quadratures[1][i] * cal(t_i);
	}

	return factor * sum;

}
double absolute_err(double actual, double result) {
	double res = abs(actual - result);
	//std::cout << "Result: " << result << "\t small_num: " << SMALL_NUM << "\n";
	return (res < SMALL_NUM) ? 0 : res;
}
int main() {
	std::string _function = "1x^2 + 2x^1 + 5x^0";
	Factors _f = find_factors(_function);
	Exponents _e = find_exponents(_function);
	Operators _o = find_operators(_function);
	applyVectors(_f, _e, _o);
	
	
	const std::vector<double> actual_results = { 1.67873, 88.875,146.764 };
	/// <summary>
	/// Results from the previous laboratories stored in matrix
	/// each row contains appropiately: square, trapeze and simpson results
	/// [0] -> sine 
	/// [1] -> function
	/// [2] -> exp
	/// </summary>
	/// <returns></returns>
	const Matrix prev_results = {
		{1.6795,1.67718, 1.68929},
		{88.854,88.9171,88.875},
		{146.422,147.45, 159.474}
	};
	/// <summary>
	/// Results from the current laboratories stored in matrix
	/// Each row contains appropiately results for: node_count = 2, node_count = 3, node_count = 4
	/// [0] -> sine
	/// [1] -> function
	/// [2] -> exp
	/// </summary>
	/// <returns></returns>
	const Matrix results = {
		{gauss_legrenge(sin, 2, 0.5, 2.5), gauss_legrenge(sin, 3, 0.5, 2.5), gauss_legrenge(sin, 4, 0.5, 2.5)},
		{gauss_legrenge(calc, 2, 0.5, 5.0), gauss_legrenge(calc, 3, 0.5, 5.0), gauss_legrenge(calc, 4, 0.5, 5.0)},
		{gauss_legrenge(exp, 2, 0.5, 5.0),gauss_legrenge(exp, 3, 0.5, 5.0),gauss_legrenge(exp, 4, 0.5, 5.0)}
	};

	/// <summary>
	/// Absolute errors for appropiately Gauss-Legrenge qudrature node_count = 4 and simpson method
	/// [0] -> sine
	/// [1] -> function
	/// [2] -> exp
	/// </summary>
	/// <returns></returns>
	const Matrix errors = {
		{absolute_err(actual_results[0], results[0][2]), absolute_err(actual_results[0], prev_results[0][2])},
		{absolute_err(actual_results[1], results[1][2]), absolute_err(actual_results[1], prev_results[1][2])},
		{absolute_err(actual_results[2], results[2][2]), absolute_err(actual_results[2], prev_results[2][2])}
	};

	std::cout << "sin(x):\n<0.5, 2.5>\n";
	std::cout << "node_count = 2: " << results[0][0];
	std::cout << "\nnode_count = 3: " << results[0][1];
	std::cout << "\nnode_count = 4: " << results[0][2];
	std::cout << "\nSquare|Trapeze|Simpson: " << prev_results[0][0] << "|" << prev_results[0][1] << "|" << prev_results[0][2];
	std::cout << "\nActual: " << actual_results[0];
	std::cout << "\nabs_err for Gauss Legrenge quadrature node_count 4: " << errors[0][0];
	std::cout << "\nabs_err for Simpson method: " << errors[0][1];

	std::cout << "\n----------\n"<<_function << "\n<0.5, 5>\n";
	std::cout << "node_count = 2: " << results[1][0];
	std::cout << "\nnode_count = 3: " << results[1][1];
	std::cout << "\nnode_count = 4: " << results[1][2];
	std::cout << "\nSquare|Trapeze|Simpson: " << prev_results[1][0] << "|" << prev_results[1][1] << "|" << prev_results[1][2];
	std::cout << "\nActual: " << actual_results[1];
	std::cout << "\nabs_err for Gauss Legrenge quadrature node_count 4: " << errors[1][0];
	std::cout << "\nabs_err for Simpson method: " << errors[1][1];

	std::cout << "\n----------\nexp(x):\n<0.5, 5.0>\n";
	std::cout << "node_count = 2: " << results[2][0];
	std::cout << "\nnode_count = 3: " << results[2][1];
	std::cout << "\nnode_count = 4: " << results[2][2];
	std::cout << "\nSquare|Trapeze|Simpson: " << prev_results[2][0] << "|" << prev_results[2][1] << "|" << prev_results[2][2];
	std::cout << "\nActual: " << actual_results[2];
	std::cout << "\nabs_err for Gauss Legrenge quadrature node_count 4: " << errors[2][0];
	std::cout << "\nabs_err for Simpson method: " << errors[2][1];

	return 0;
}