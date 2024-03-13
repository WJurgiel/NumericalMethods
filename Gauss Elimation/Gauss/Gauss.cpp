#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
std::vector<std::vector<float>> matrix;

std::fstream* read_from_file(std::string path) {
    std::fstream* file = new std::fstream;
    file->open(path, std::ios_base::in);
    return file;
}
void printMatrix(std::vector<std::vector<float>> vector) {
    for (auto x : vector) {
        for (auto y : x) std::cout << y << " ";
        std::cout << "\n";
    }
        std::cout << "\n\n";
}
void printSolution(std::vector<float> vec) {
    int count = 0;
    for (auto x : vec) {
        std::cout << "x[" << count++ << "] ";
        std::cout << x << std::endl;
    }
}
bool ZeroOnDiagonal(std::vector<std::vector<float>> vec) {

    for (int i = 0; i < vec.size(); i++) {
        if (vec[i][i] == 0) 
            return true;
    }
    return false;
}
std::vector<float> solvedSystem() {
    int n = matrix.size();
    float m = 0;
    for (int z = 0; z < n; z++) {

        for (int i = z + 1; i < n; i++) {
            m = matrix[i][z] / matrix[z][z];
            for (int j = 0; j < n + 1; j++) {
                matrix[i][j] -= (matrix[z][j] * m);
            }
        }
        //printMatrix(matrix);
    }
    std::cout << "After: \n";
    printMatrix(matrix);
    std::vector<float> results(n);
    for (int i = n - 1; i >= 0; --i) {
        results[i] = matrix[i][n] / matrix[i][i];
        for (int j = i - 1; j >= 0; --j) {
            matrix[j][n] -= matrix[j][i] * results[i];
        }
    }
    return results;
}
int main()
{
    std::fstream* file = read_from_file("Data1.txt");
    unsigned n;
    /*
        AUXILIARY VALUES
    */
    double num = 0; //auxiliary value, write file numbers to num
    std::string line; 

    if (file->bad()) {
        std::cout << "[ERROR]: Can't read the file, exiting";
        return -1;
    }

    while (std::getline(*file, line)) {
        //std::cout << line << "\n";
        std::vector<float> row;
        std::istringstream iss(line);
        while (iss >> num) {
            row.push_back(num);
        }
        matrix.push_back(row);
    }
    std::cout << "Before: \n";
    printMatrix(matrix);

    if (ZeroOnDiagonal(matrix)) {
        std::cout << "[ERROR]: Zero on diagonal detected, can't solve the system\n";
        return -1;
    }
    std::vector<float> x_i = solvedSystem();
    std::cout << "Solution: \n";
    printSolution(x_i);
    file->close();
    delete file;
    return 1;
}
