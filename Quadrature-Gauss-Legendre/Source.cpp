#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include "FunctionHandler.h"
#define SMALL_NUM 1e-05
using Factors = std::vector<float>;
using Exponents = std::vector<int>;
using Operators = std::vector<char>;
using Matrix = std::vector<std::vector<double>>;

enum functions {
	SINE,
	FUNC,
	EXP
};

double getLastValue(std::string path) {
	std::fstream file(path);
	std::string lastLine;
	double value;
	if (!file.is_open()) {
		return 0.0;
	}
	else {
		std::string line;
		while (std::getline(file, line)) {
			lastLine = line;
		}
	}
	file.close();
	std::stringstream ss(lastLine);
	ss >> value >> value;

	return value;
}

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
void print_results(int func_id, std::string func, std::string range, const Matrix& results, const Matrix& prev_results, const std::vector<double>& actual_results, const Matrix& errors) {
	std::cout << "\n--------------\n" << func << ":\n" << range << "\n";
	std::cout << "node_count = 2: " << results[func_id][0];
	std::cout << "\nnode_count = 3: " << results[func_id][1];
	std::cout << "\nnode_count = 4: " << results[func_id][2];
	std::cout << "\nSquare|Trapeze|Simpson: " << prev_results[func_id][0] << "|" << prev_results[func_id][1] << "|" << prev_results[func_id][2];
	std::cout << "\nActual: " << actual_results[func_id];
	std::cout << "\nabs_err for Gauss Legrenge quadrature node_count 4: " << errors[func_id][0];
	std::cout << "\nabs_err for Square Method: " << errors[func_id][1];
	std::cout << "\nabs_err for Trapeze Method: " << errors[func_id][2];
	std::cout << "\nabs_err for Simpson method: " << errors[func_id][3];
	
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
		{getLastValue("sine_square.txt"),getLastValue("sine_trapeze.txt"), getLastValue("sine_simpson.txt")},
		{getLastValue("fun_square.txt"),getLastValue("fun_trapeze.txt"),getLastValue("fun_simpson.txt")},
		{getLastValue("exp_square.txt"),getLastValue("exp_trapeze.txt"), getLastValue("exp_simpson.txt")}
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
	/// Absolute errors for 
	/// {node_count = 4, square, trapeze, simpson}
	/// [0] -> sine
	/// [1] -> function
	/// [2] -> exp
	/// </summary>
	/// <returns></returns>
	const Matrix errors = {
		{	
			absolute_err(actual_results[SINE], results[SINE][2]),         // node_count = 4
			absolute_err(actual_results[SINE],prev_results[SINE][0]),    //square
			absolute_err(actual_results[SINE],prev_results[SINE][1]),   //trapeze
			absolute_err(actual_results[SINE], prev_results[SINE][2])  //simpson
		},
		{	
			absolute_err(actual_results[FUNC], results[FUNC][2]), 	     // node_count = 4
			absolute_err(actual_results[FUNC], prev_results[FUNC][0]),  //square
			absolute_err(actual_results[FUNC], prev_results[FUNC][1]), //trapeze
			absolute_err(actual_results[FUNC], prev_results[FUNC][2]) //simpson
		},
		{
			absolute_err(actual_results[EXP], results[EXP][2]),		    // node_count = 4
			absolute_err(actual_results[EXP], prev_results[EXP][0]),   //square
			absolute_err(actual_results[EXP], prev_results[EXP][1]),  //trapeze
			absolute_err(actual_results[EXP], prev_results[EXP][2])	 //simpson
		}
	};

	print_results(SINE, "sin(x)", "<0.5,2.5>", results, prev_results, actual_results, errors);
	print_results(FUNC, _function, "<0.5,5>", results, prev_results, actual_results, errors);
	print_results(EXP, "exp(x)", "<0.5, 5>", results, prev_results, actual_results, errors);

	return 0;
}