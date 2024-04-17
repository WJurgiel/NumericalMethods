#include <iostream>
#include <vector>
#include <regex>
#include "FunctionHandler.h"
#include <fstream>
using std::cout;
using std::cin;

std::string func_type;
std::vector<float> facs;
std::vector<int>exs;
std::vector<char>ops;
/*
	Squares method:
	input: n, function, a, b
	x_i obliczane na podstawie a + s * iter
*/
double square_method(double (*cal)(double x), int n, double left, double right) {
	double s = (right - left) / n;
	std::cout << "s: " << s << "\n";
	double result = 0;
	double sum = 0;

	for (int i = 0; i <= n - 1; i++) {
		double x_i = left + s * i;
		std::cout << i << ": " << x_i;
		sum += cal(x_i + 0.5 * s);
		std::cout << ", sum:" << sum << "\n";
	}
	return s * sum;
}
double trapeze_method(double (*calc)(double x), int n, double left, double right) {
	double s = (right - left) / n;
	double sum = 0.0;
	for (int i = 0; i <= n - 1; i++) {
		double x_i = left + s * i;
		double x_ii = left + s * (i + 1);

		sum += ((x_ii - x_i) / 2 * (calc(x_i) + calc(x_ii)));
	}
	return sum;
}
double simpson_method(double (*calc)(double x), int n, double left, double right) {
	double fac1 = (right - left) / 6;
	double fac2 = (left + right) / 2;
	return fac1 * (calc(left) + 4 * calc(fac2) + calc(right));
}
int main() {
	//std::cout << "HINT: provide custom equation (containing ONLY factors, x, and exponents";
	//dopisac przedzialy i N
	std::string equation = "1x^2 + 2x^1 + 5x^0";


	facs = find_factors(equation);
	exs= find_exponents(equation);
	ops= find_operators(equation);
	applyVectors(facs, exs, ops);

	func_type = find_predefined(equation);

	cout << "sin(x):\n";
	cout << "Square method: " << square_method(sin, 4, 0.5, 2.5) << "\n";
	cout << "Trapeze method: " << trapeze_method(sin, 4, 0.5, 2.5) << "\n";
	cout << "Simpson method: " << simpson_method(sin, 4, 0.5, 2.5) << "\n";
	cout << "---------------------------\n\n";
	cout << equation << ":\n";
	cout << "Square method: " << square_method(calc, 4, 0.5, 5) << "\n";
	cout << "Trapeze method: " << trapeze_method(calc, 4, 0.5, 5) << "\n";
	cout << "Simpson method: " << simpson_method(calc, 4, 0.5, 5) << "\n";
	cout << "---------------------------\n\n";


	cout << "exp(x)" << ":\n";
	cout << "Square method: " << square_method(exp, 4, 0.5, 5) << "\n";
	cout << "Trapeze method: " << trapeze_method(exp, 4, 0.5, 5) << "\n";
	cout << "Simpson method: " << simpson_method(exp, 4, 0.5, 5) << "\n";


	
	cout << "---------------------------\n\n";

	
	
	//std::cout << calc(3);
	std::ofstream file("SineIntegral.txt");
	if (file.bad()) {
		return 0;
	}
	for (int n = 1; n < 1000; n++) {
		double result = trapeze_method(sin, n, 0.5, 5);
		file << n << " " << result << "\n";
	}
	file.close();

	std::ofstream file2("ExpIntegral.txt");
	if (file2.bad()) {
		cout << "can't read expintegra";
		return 0;
	}
	for (int n = 1; n < 1000; n++) {
		double result = trapeze_method(exp, n, 0.5, 5);
		file2 << n << " " << result << "\n";
	}
	file.close();

	std::ofstream file3("CustomIntegral.txt");
	if (file3.bad()) {
		return 0;
	}
	for (int n = 1; n < 1000; n++) {
		double result = trapeze_method(calc, n, 0.5, 5);
		file3 << n << " " << result << "\n";
	}
	file3.close();
	std::cout << func_type << "\n";

	return 0;
}
