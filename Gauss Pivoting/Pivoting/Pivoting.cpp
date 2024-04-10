#define SMALL_NUMBER 1e-05
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
std::vector<std::vector<double>> matrix;

std::fstream* read_from_file(std::string path) {
    std::fstream* file = new std::fstream;
    file->open(path, std::ios_base::in);
    return file;
}
std::vector<int> init_craut_columns(std::vector<std::vector<double>>& matrix) {
    std::vector<int> toReturn;
    int n = matrix.size() - 1;
    for (int col = 0; col <= n; col++) {
        toReturn.push_back(col);
    }
    return toReturn;
}
void print_matrix(std::vector<std::vector<double>>& matrix) {
    for (auto x : matrix) {
        std::cout << "[ ";
        for (auto y : x) std::cout << y << " ";
        std::cout << "]\n";
    }
    std::cout << "\n\n";
}
void print_solution(std::vector<double> sol) {
    int counter = 0;
    for (auto x : sol) {
        std::cout << "x[" << counter++ << "] = " << x << "\n";
    }
}
void print_solution(std::vector<double>& sol, const std::vector<int>& craut_columns) {
    for (size_t i = 0; i < sol.size(); ++i) {
        std::cout << "x[" << craut_columns[i] << "]:" << sol[craut_columns[i]] << "\n";
    }
}

std::vector<double> solve_system(std::vector<std::vector<double>>& matrix, const std::vector<int>& craut_columns) {
    int n = matrix.size();
    std::vector<double> results(n);
    for (int i = n - 1; i >= 0; --i) {
        results[i] = matrix[i][n] / matrix[i][i];
        for (int j = i - 1; j >= 0; --j) {
            matrix[j][n] -= matrix[j][i] * results[i];
        }
    }
    std::vector<double> rearranged_results(n);
    for (size_t i = 0; i < craut_columns.size(); ++i) {
        rearranged_results[craut_columns[i]] = results[i];
    }

    return rearranged_results;
}
std::vector<double> solve_system(std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    std::vector<double> results(n);
    for (int i = n - 1; i >= 0; --i) {
        results[i] = matrix[i][n] / matrix[i][i];
        for (int j = i - 1; j >= 0; --j) {
            matrix[j][n] -= matrix[j][i] * results[i];
        }
    }
    return results;
}
void GaussColumn(std::vector<std::vector<double>>& matrix, int col) {
    int n = matrix.size();
    double m = 0.0;
    for (int i = col + 1; i < n; i++) {
        m = matrix[i][col] / matrix[col][col];
        for (int z = 0; z < n + 1; z++) {
            matrix[i][z] -= (matrix[col][z] * m);
            if (abs(matrix[i][z]) < SMALL_NUMBER) {
                matrix[i][z] = 0;
            }
        }
    }
}
void GaussColumn(std::vector<std::vector<double>>& matrix, int col, int row) {
    double m = matrix[row][col] / matrix[col][col];
    int n = matrix.size();
    for (int j = col; j < n + 1; j++) {
        matrix[row][j] -= (matrix[col][j] * m);
        if (std::abs(matrix[row][j]) < SMALL_NUMBER) {
            matrix[row][j] = 0;
        }
    }
}
void FindPivot(std::vector<std::vector<double>>& matrix, int col) {
    //for all rows in one column
    std::vector<double> column;
    for (int row = col; row < matrix.size(); row++) {
        column.push_back(matrix[row][col]);
    }
    /*
        It's index of maximum value in COLUMN not the MATRIX, be aware that you have to add col in swapping to make this work
    */
    int indexOfMax = std::distance(column.begin(), std::max_element(column.begin(), column.end()));
    std::cout << "Index: " << indexOfMax;
    std::cout << "Value in " << indexOfMax << ": " << column[indexOfMax] << std::endl;

    print_matrix(matrix);
    //matrix[indexofMax] <-> matrix[col]
    matrix[indexOfMax + col].swap(matrix[col]);
    std::cout << col << ":\n";
    GaussColumn(matrix, col);
}
void CrautFindPivot(std::vector<std::vector<double>>& matrix, std::vector<int>& rows, int diag) {
   
    auto max_element_it = std::max_element(matrix[diag].begin() + diag, matrix[diag].end() -1);

    int indexOfMaxInCol = std::distance(matrix[diag].begin(), max_element_it);

   
   /* std::cout << "Matrix before pivoting:\n";
    print_matrix(matrix);*/

   
    for (size_t i = 0; i < matrix.size(); ++i) {
        std::swap(matrix[i][diag], matrix[i][indexOfMaxInCol]);
    }
    std::swap(rows[diag], rows[indexOfMaxInCol]);

    
   /* std::cout << "Matrix after column swaps:\n";
    print_matrix(matrix);*/

    int n = rows.size();
    for (int i = diag + 1; i < n; i++)
        GaussColumn(matrix, diag, i);
}


bool ZeroOnDiagonal(std::vector<std::vector<double>> vec) {

    for (int i = 0; i < vec.size(); i++) {
        if (vec[i][i] == 0)
            return true;
    }
    return false;
}

int main()
{
    std::string line;
    double num;
    std::fstream* file = read_from_file("Data3.txt");
    std::fstream* file2 = read_from_file("Data4.txt");
    if (file->bad() || file2->bad()) {
        std::cout << "ERROR: can't read from file\n";
        return -1;
    }
    while (std::getline(*file, line)) {
        //std::cout << line << "\n";
        std::vector<double> row;
        std::istringstream iss(line);
        while (iss >> num) {
            row.push_back(num);
        }
        std::getline(*file2, line);
        std::istringstream iss2(line);
        iss2 >> num;
        row.push_back(num);

        matrix.push_back(row);
    }
    file->close();
    file2->close();

    std::cout << "Before:\n";
    print_matrix(matrix);

    /*if (ZeroOnDiagonal(matrix)) {
        std::cout << "Zero on diagonal, can't solve\n";
        return -1;
    }*/

    /*SOLUTION TASK 1:*/
    /*for (int col = 0; col < matrix[0].size() - 1; col++) {
        std::cout << "Column: " << col;
        FindPivot(matrix, col);
        
    }*/

    /*SOLUTION TASK 2:*/
    std::vector<int> craut_columns = init_craut_columns(matrix);
    for (int diag = 0; diag < matrix[0].size()-1; diag++) {
        //std::cout << "Column: " << diag;
        CrautFindPivot(matrix,craut_columns, diag);
    }

    std::cout << "After:\n";
    print_matrix(matrix);
    //TO TASK 2:
    std::cout << "\nColumns After:";
    for (auto x : craut_columns) std::cout << x << " ";

    //SOLUTION TASK 1:
    /*std::vector<double> x_i = solve_system(matrix);
    print_solution(x_i);*/

    /*
        SOLUTION TASK 2:
    */
    std::vector<double> x_i = solve_system(matrix,craut_columns);
    print_solution(x_i,craut_columns);


    
        //TO TASK 2
    std::cout << "Columns: ";
     for (auto x : craut_columns) std::cout << x << " ";
    std::cout << "\n";
    delete file;
    delete file2;
    return 0;
}
