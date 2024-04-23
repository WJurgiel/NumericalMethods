#pragma once
#include <iostream>
#include <regex>

std::vector<float> find_factors(std::string equation);
std::vector<int> find_exponents(std::string equation);
std::vector<char> find_operators(std::string equation);
void applyVectors(std::vector<float>& f, std::vector<int>& e, std::vector<char>& o);
std::string find_predefined(std::string equation);
double calc(double x);