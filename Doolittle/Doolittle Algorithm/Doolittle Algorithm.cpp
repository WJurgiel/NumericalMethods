#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

void print_matrix(std::vector<std::vector<double>>& matrix) {
    for (auto& row : matrix) {
        std::cout << "[";
        for (auto num : row) {
            std::cout << num << "\t";
        }

        std::cout << "]\n";
    }
}
void print_vector(std::vector<double>& vector, bool isSolution) {
    int id = 0;
    for (auto& elem : vector) 
        if(isSolution)
            std::cout << "[" << id++ << "]: " << elem << "\n";
        else
            std::cout << "["<< elem << "\t]\n";
}
std::fstream* open_file(std::string path) {
    std::fstream* file = new std::fstream;
    file->open(path, std::ios_base::in);
    if (file->bad()) {
        std::cout << "Couldn't read " << path << " exiting";
        exit(-1);
    }
    return file;
}
std::vector<std::vector<double>> read_files_content(std::fstream* fileA, std::fstream* fileB) {
    std::string line;
    std::vector<std::vector<double>> matrix;
    while (std::getline((*fileA), line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        double num;
        while (ss >> num) row.push_back(num);
        std::getline((*fileB), line);   
        std::stringstream ss2(line);
        ss2 >> num;
        row.push_back(num);

        matrix.push_back(row);
    }
    return matrix;
}
bool isZeroOnDiagonal(std::vector<std::vector<double>>& matrix_AB) {
    for (int i = 0; i < matrix_AB.size(); i++)
        for (int j = 0; j < matrix_AB.size(); j++)
            if (i == j) if (matrix_AB[i][j] == 0) return true;
    return false;
}
void init_matrix_L(std::vector<std::vector<double>>& matrix_L) {
    for (int i = 0; i < matrix_L.size(); i++)
        for (int j = 0; j < matrix_L.size(); j++)
            if (i == j) matrix_L[i][j] = 1;
}

void calc_LU(
    std::vector<std::vector<double>>& A,
    std::vector<std::vector<double>>& U,
    std::vector<std::vector<double>>& L
) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0f;
            //Calculate U matrix
            if (i <= j) {
                for (int k = 0; k < i; k++) {
                    sum += (L[i][k] * U[k][j]);
                }
                U[i][j] = A[i][j] - sum;

            }
            //Calculate L matrix
            else {
                for (int k = 0; k < j; k++) {
                    sum += (L[i][k] * U[k][j]);
                }
                L[i][j] = (1 / U[j][j]) * (A[i][j] - sum);
            }

        }
    }
}

void calc_vector_Y(
    std::vector<std::vector<double>>& matrix_AB,
    std::vector<std::vector<double>>& matrix_L,
    std::vector<double>& vector_Y
) 
{
    for (int i = 0; i < matrix_AB.size(); ++i) {
        double y_i = 0.0;
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += matrix_L[i][j] * vector_Y[j];
        }
        y_i = matrix_AB[i][matrix_AB.size()] - sum;
        vector_Y[i] = y_i;
    }
}
std::vector<double> calc_solution(std::vector<double> vector_Y, std::vector<std::vector<double>> matrix_U) {
    int n = matrix_U.size() - 1;
    std::vector<double> solution(matrix_U.size());
    solution[n] = vector_Y[n] / matrix_U[n][n];
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j <= n; j++) sum += matrix_U[i][j] * solution[j];
        solution[i] = 1.0 / matrix_U[i][i] * (vector_Y[i] - sum);
    }
    return solution;
}
int main()
{
    /*
        FILE HANDLING 
    */
    std::fstream* fileA = open_file("A.txt");
    std::fstream* fileB = open_file("B.txt");
    std::vector<std::vector<double>> matrix_AB = read_files_content(fileA, fileB);
    fileA->close();
    fileB->close();
    /*
        VARIABLES && MATRIXES
    */
    int size = matrix_AB.size();
    std::vector<std::vector<double>> matrix_L(size, std::vector<double>(size, 0));
    std::vector<std::vector<double>> matrix_U(size, std::vector<double>(size, 0));
    std::vector<double> vector_Y(size, 0);

    /*ALGORITHM*/
    if (isZeroOnDiagonal(matrix_AB)) {
        std::cout << "Zero on diagonal, terminating\n";
        exit(0);
    }
    init_matrix_L(matrix_L);

    calc_LU(matrix_AB, matrix_U, matrix_L);
    vector_Y[0] = matrix_AB[0][size];
    calc_vector_Y(matrix_AB, matrix_L, vector_Y);
    std::vector<double> solution = calc_solution(vector_Y, matrix_U);
    /*OUTPUT*/
    std::cout << "matrix AB:\n";
    print_matrix(matrix_AB);
    std::cout << "matrix L:\n";
    print_matrix(matrix_L);
    std::cout << "matrix U:\n";
    print_matrix(matrix_U);
    std::cout << "vector Y:\n";
    print_vector(vector_Y, false);
    std::cout << "Solution: \n";
    print_vector(solution,true);



    delete fileA;
    delete fileB;
    return 0;
}
