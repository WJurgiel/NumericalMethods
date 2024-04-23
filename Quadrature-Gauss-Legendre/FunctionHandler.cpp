#include "FunctionHandler.h"


std::vector<float> factors;
std::vector<int> exponents;
std::vector<char> operators;
void applyVectors(std::vector<float>& f, std::vector<int>& e, std::vector<char>& o) {
	factors = f;
	exponents = e;
	operators = o;
}
std::vector<float> find_factors(std::string equation) {
	std::vector<float> factors;
	std::regex factor_pattern("(\\d+)x");
	auto fac_begin = std::sregex_iterator(equation.begin(), equation.end(), factor_pattern);
	auto fac_end = std::sregex_iterator();
	
	for (auto& i = fac_begin; i != fac_end; i++) {
		std::smatch match = *i;
		float factor = 1.0;
		if (match.size() > 1) {
			factor = std::stof(match[0].str());
		}
		factors.push_back(factor);
	}
	return factors;
}
std::vector<int> find_exponents(std::string equation) {
	std::vector<int> exponents;
	std::regex exponent_pattern("\\^(\\d+)");
	auto exp_begin = std::sregex_iterator(equation.begin(), equation.end(), exponent_pattern);
	auto exp_end = std::sregex_iterator();

	for (auto& i = exp_begin; i != exp_end; i++) {
		std::smatch match = *i;
		int exponent = 1;
		if (match.size() > 1) {
			exponent = std::stoi(match[1].str());
		}
		exponents.push_back(exponent);
	}
	return exponents;
}
std::vector<char> find_operators(std::string equation) {
	std::vector<char> operators;
	std::regex operator_pattern("[+\\-*\\/]");
	auto op_begin = std::sregex_iterator(equation.begin(), equation.end(), operator_pattern);
	auto op_end = std::sregex_iterator();

	for (auto& i = op_begin; i != op_end; i++) {
		std::smatch match = *i;
		char op = match.str()[0];
		operators.push_back(op);
	}
	return operators;
}
std::string find_predefined(std::string equation) {
	std::regex func_pattern("(sin|cos|tan|exp)");
	
	std::smatch matches;
	if (std::regex_search(equation, matches, func_pattern)) {

		if (matches.str() == "sin") return "sin";
		else if (matches.str() == "cos") return "cos";
		else if (matches.str() == "tan") return "tan";
		else if (matches.str() == "exp") return "exp";
		else if (matches.str() == "log") return "log";
	}
	return "no predefined";
}
double calc(double x) {
	//odczytaj stopien funkcji 
	auto degree = std::max_element(exponents.begin(), exponents.end());
	double value = factors[0] * pow(x, exponents[0]);

	//char current_op = operators[0];

	for (int i = 0; i < *degree; i++) {
		char current_op = operators[i];
		switch (current_op) {
		case '+':
			value += factors[i+1] * pow(x, exponents[i+1]);
			break;
		case '-':
			value -= factors[i + 1] * pow(x, exponents[i + 1]);
			break;
		case '*':
			value += factors[i + 1] * pow(x, exponents[i + 1]);
			break;
		case '/':
			value += factors[i + 1] * pow(x, exponents[i + 1]);
			break;
		}
	}
	return value;
}