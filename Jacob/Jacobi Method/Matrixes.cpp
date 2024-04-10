#include "Matrixes.h"
void read_matrix(std::vector<std::vector<double>>& matrix) {
    for (auto& x : matrix) {
        for (auto& y : x) {
            std::cout << y << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
void read_vector(std::vector<double>& vec) {
    int id = 0;
    for (auto& x : vec) {
        std::cout << "[" << id++ << "]: " << x << "\n";
    }
    std::cout << "\n";
}
void init_matrix_L(std::vector<std::vector<double>> matrix_AB, std::vector<std::vector<double>>& matrix_L) {
    for (int i = 0; i < matrix_AB.size(); i++) {
        for (int j = 0; j < matrix_AB.size(); j++) {
            if (i > j) matrix_L[i][j] = matrix_AB[i][j];
        }
    }
}
void init_matrix_D(std::vector<std::vector<double>> matrix_AB, std::vector<std::vector<double>>& matrix_D) {
    for (int i = 0; i < matrix_AB.size(); i++) {
        for (int j = 0; j < matrix_AB.size(); j++) {
            if (i == j) matrix_D[i][j] = matrix_AB[i][j];
        }
    }
}
void init_matrix_U(std::vector<std::vector<double>> matrix_AB, std::vector<std::vector<double>>& matrix_U) {
    for (int i = 0; i < matrix_AB.size(); i++) {
        for (int j = 0; j < matrix_AB.size(); j++) {
            if (i < j) matrix_U[i][j] = matrix_AB[i][j];
        }
    }
}
std::vector<std::vector<double>> operator +(const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2) {
    //In this example we add two matrixes with the same sizes but it's nice to check it in case adding other matrixes
    if (matrix1.size() != matrix2.size() || ((matrix1.size() > 0 && matrix1[0].size() != matrix2[0].size()))) {
        std::cout << "Warning: Vectors are not the same size\n";
        return std::vector<std::vector<double>>();
    }
    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1.size(), 0));
    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1.size(); j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}
std::vector<double> operator +(const std::vector<double> vec1, const std::vector<double> vec2) {
    std::vector<double> result(vec1.size(), 0);
    for (int i = 0; i < vec1.size(); i++) { 
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}
std::vector<std::vector<double>> operator ^(const std::vector <std::vector<double>> matrix_D, const int a) {
    if (a != -1) return std::vector < std::vector<double>>();

    std::vector<std::vector<double>> result(matrix_D.size(), std::vector<double>(matrix_D.size(), 0));
    //Diagonal matrix will always have det != 0 so A^-1 exists. This case is also 100 times easier since values on diagonal are just x^-1
    for (int i = 0; i < matrix_D.size(); i++) {
        result[i][i] = 1.0 / matrix_D[i][i];
    }
    return result;
}
std::vector<std::vector<double>> operator *(const std::vector<std::vector<double>> matrix1, const std::vector<std::vector<double>> matrix2) {
    std::vector<std::vector<double>> result;
    for (int i = 0; i < matrix1.size(); i++) {
        result.push_back({});
        for (int j = 0; j < matrix2[0].size(); j++) {
            result[i].push_back(0);
        }
    }
    for (int i = 0; i < matrix1.size(); i++) { //dla wszystkich rzêdów matrix1
        for (int j = 0; j < matrix2[0].size(); j++) { 
            for (int k = 0; k < matrix1[0].size(); k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}
std::vector<double> operator *(const std::vector<std::vector<double>> matrix1, const std::vector<double> vec1) {
    //std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(1, 0));
    std::vector<double> result(matrix1.size(), 0);

    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < vec1.size(); ++j) {
            result[i] += matrix1[i][j] * vec1[j];
        }
    }
    return result;
}
std::vector<std::vector<double>> operator* (const std::vector<std::vector<double>> matrix, int num) {
    std::vector<std::vector<double>> result = matrix;
    for (auto& x : result) {
        for (auto& y : x) {
            y *= num;
        }
    }
    return result;
}