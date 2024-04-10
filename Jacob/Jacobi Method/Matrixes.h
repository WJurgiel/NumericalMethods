#pragma once
#include <vector>
#include <iostream>
void read_matrix(std::vector<std::vector<double>>& matrix);
void read_vector(std::vector<double>& vec);
void init_matrix_L(std::vector<std::vector<double>> matrix_AB, std::vector<std::vector<double>>& matrix_L);
void init_matrix_D(std::vector<std::vector<double>> matrix_AB, std::vector<std::vector<double>>& matrix_D);
void init_matrix_U(std::vector<std::vector<double>> matrix_AB, std::vector<std::vector<double>>& matrix_U);
std::vector<std::vector<double>> operator +(const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2);
std::vector<double> operator +(const std::vector<double> vec1, const std::vector<double> vec2);
std::vector<std::vector<double>> operator ^(const std::vector <std::vector<double>> matrix_D, const int a);
std::vector<std::vector<double>> operator *(const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2);
std::vector<double> operator *(const std::vector<std::vector<double>> matrix1, const std::vector<double> vec1);
std::vector<std::vector<double>> operator* (const std::vector<std::vector<double>> matrix, int num);