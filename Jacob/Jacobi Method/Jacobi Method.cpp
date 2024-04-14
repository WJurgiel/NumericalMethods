#include "FileHandler.h"
#include "Matrixes.h"
#define EPSILON 1E-03
#define EPSILON2 1E-06
/*
    A = L + D + U
    (L + D + U)X = B
    X^(i+1) = -D^-1(L+U)x^(i) + D^-1B

    1.pobrac z pliku - done
    2. wypisac macierz rozszerzona - done
    3. ? slabo dominujaca wyswietlic komunikat - done
    4. Warunkiem zatrzymania algorytmu jest ilosc iteracji
    5. Wypisac L + U - done
    6. Wypisac D^-1 - done
    7 wypisac zadana liczbe iteracji i rozwiazac uk. równ
    8 oblicz blad bezwzgledny dla kazdego x
*/
using Matrix = std::vector<std::vector<double>>;
bool isWeakDominant(std::vector<std::vector<double>> matrix_AB) {
    //upewnic sie ze dominujaca
    bool additionalCondition = false; // a_ii > sum(a_ij)
    for (int i = 0; i < matrix_AB.size(); i++) {
        double diagonalElement = abs(matrix_AB[i][i]);
        double sum = 0.0;
        for (int j = 0; j < matrix_AB.size(); j++) {
            if (i != j) sum += abs(matrix_AB[i][j]);
        }
        if (diagonalElement > sum) additionalCondition = true;
        if (diagonalElement < sum) return false;
    }
    return (additionalCondition) ? true : false;
}
bool shouldStop(std::vector<double> x, std::vector<double> x_prev, const double epsilon) {
    //bool shouldStop = false;
    for (int elem = 0; elem < x.size(); elem++) {
        double d = std::abs(x[elem] - x_prev[elem]);
        std::cout << d;
        std::cout << ((d < epsilon) ? " True" : " False");
        std::cout << "\n";
        if (std::abs(x[elem] - x_prev[elem]) < epsilon) {
            return true;
        }
    }
    return false;
}
std::vector<double> JacobiMethod(Matrix matrix_AB, Matrix matrix_D_rev, Matrix matrix_L_U, std::vector<double> results, int iterations, const double eps) {
    std::vector<double>x(matrix_AB.size(), 0);
    std::vector<double> x_prev = x;

    Matrix min_D_rev = matrix_D_rev * -1;
    Matrix min_D_rev_L_U = min_D_rev * matrix_L_U;
    //const std::vector<double> vec1 = { 5, -4, 2, 7 };
    std::vector<double> D_rev_B = matrix_D_rev * results;

    for (int it = 0; it < iterations; it++) {
        
        
        std::vector<double>x_new(matrix_AB.size(), 0);
        for (int sol_id = 0; sol_id < x.size(); sol_id++) {
            x_new = (min_D_rev_L_U * x) + D_rev_B;
        }

        //Somehow it doesn't compare values properly, debug it
        
        x_prev = x;
        std::cout << "It: " << it << "\n";
        if (shouldStop(x_new, x_prev, eps)) {
            std::cout << "\nBreaking after " << it << " iterations\nEpsilon = " << eps << "\n";
            break;
        }
        x = x_new;
    }
    return x;
}
std::vector<double> absolute_Error(std::vector<double> sol_acc, std::vector<double> sol_measured) {
    std::vector<double> errors;
    for (int id = 0; id < sol_acc.size(); id++) {
        double res = abs(sol_acc[id] - sol_measured[id]);
        errors.push_back(res);
    }
    return errors;
}
int main()
{
    /*
        FILES AND MATRIXES
    */
    std::fstream* fileA = open_file("A.txt");
    std::fstream* fileB = open_file("B.txt");
    std::fstream* fileSol = open_file("Gauss_solutions.txt");
    std::vector<std::vector<double>> matrix_AB = read_files_content(fileA, fileB);
    
    fileB = open_file("B.txt");
    std::vector<double> matrix_B = read_file_content(fileB);
    std::vector<double> gaussSolutions = read_file_content(fileSol);
    int size = matrix_AB.size();
    std::vector<std::vector<double>> matrix_L(size, std::vector<double>(size, 0));
    std::vector<std::vector<double>> matrix_D(size, std::vector<double>(size, 0));
    std::vector<std::vector<double>> matrix_U(size, std::vector<double>(size, 0));
    /*
        FILLING MATRIXES WITH VALUES
    */
    init_matrix_D(matrix_AB, matrix_D);
    init_matrix_L(matrix_AB, matrix_L);
    init_matrix_U(matrix_AB, matrix_U);
    
    /*
        OPERATIONS ON MATRIXES
    */
    std::vector<std::vector<double>> matrix_L_U = matrix_L + matrix_U;
    std::vector<std::vector<double>> matrix_D_reversed = matrix_D ^ -1;

    /*
        JACOBI'S METHOD
    */
    int iterations = 0;
    std::cout << "Provide number of iterations: "; 
    do {
        std::cin >> iterations;
        if (iterations < 0) {
            std::cout << "Wrong value, iterations number must be greater than 0\nProvide number of iterations: ";
        }
    } while (iterations < 0);

    //Matrix m = matrix_D_reversed * matrix_L_U;
    //std::vector<double> v1 = { 1.0, 2.0, 3.0, 4.0 };
    //std::vector<double> v = v1 + v1;

    //Task 2 - uncomment one of sol and read_vector(sol)
    std::vector<double> sol = JacobiMethod(matrix_AB, matrix_D_reversed, matrix_L_U, matrix_B, iterations, EPSILON);
    //std::vector<double> sol = JacobiMethod(matrix_AB, matrix_D_reversed, matrix_L_U, iterations, EPSILON2);
    read_vector(sol);
    //wrzuciæ matrxi do Gaussa, zanotowaæ wyniki, obliczyc blad bezwzglledny

    /*OUTPUT*/
    std::cout << "AB matrix:\n";
    read_matrix(matrix_AB);
    std::cout << "L+U matrix:\n";
    read_matrix(matrix_L_U);
    std::cout << "D^-1 matrix:\n";
    read_matrix(matrix_D_reversed);
   /* read_matrix(m);
    read_vector(v);*/
    if (isWeakDominant(matrix_AB)) std::cout << "Diagonally weak dominant\n\n";
    else std::cout << "Is not diagonally weak dominant\n\n";

    
    std::cout << "Calculated by Gauss half pivoting method:\n";
    read_vector(gaussSolutions);
    std::vector<double> errors = absolute_Error(gaussSolutions, sol);
    std::cout << "Absolute errors:\n";
    read_vector(errors);

    delete fileA;
    delete fileB;
    delete fileSol;
}

