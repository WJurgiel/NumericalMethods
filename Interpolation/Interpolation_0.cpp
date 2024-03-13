#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
/*
    N - degree of polynomial
    x_i - interpolation nodes 
    fx_i - values in interpolation nodes 
    x - point of interpolation (passed by user)
    LNx - value of Lagrange polynomial in point x previously received from user
*/ 

std::vector<float> calculate_l_i(int N, float x, std::vector<float>& x_i) {
    std::vector<float> toReturn;
    for (int i = 0; i < x_i.size(); i++) {
    float valToPush=1;
        for (int j = 0; j < N+1; j++) {
            if (i == j) continue;
            valToPush *= (x - x_i[j]) / (x_i[i] - x_i[j]);
        }
        toReturn.push_back(valToPush);
    }
    return toReturn;
}
float calculate_Langrange_poly(int N, int x, std::vector<float>& fx_i, std::vector<float>& l_i) {
    float LN_x = 0;
    for (int i = 0; i < N+1; i++) {
        LN_x += (fx_i[i] * l_i[i]);
    }
    return LN_x;
}
void printResults(float x, float L, std::vector<float>& x_i, std::vector<float>& fx_i, std::vector<float> l_i) {
    cout << "Number of nodes: " << x_i.size() << endl;
    cout << "x_i: ";
    for (auto x : x_i) cout << x << "|";
    cout << "\nfx_i: ";
    for (auto y : fx_i) cout << y << "|";
    cout << "\nl_i: ";
    for (auto z : l_i) cout << z << "|";
    cout << "\nx: " << x << endl;
    cout << "L(x): " << L;
    cout << endl;
}
std::fstream* file(std::string path) {
    std::fstream* f = new std::fstream;
    f->open(path, std::ios_base::in);
    return f;
}
int main()
{
    std::fstream* myFile = file("nodes.txt");
    std::string line;
    std::vector<float> x_i, fx_i; //nodes and values in interpolation nodes
    std::vector<float> l_i;
    float x;
    float  LNx = 0; //Lagrange polynomial
    int N; //degree of polynomial, N = x_i.size() -1;
    
    if (myFile->good()) {
        int val;
        bool isNode = true;

        std::string line;
        std::getline(*myFile, line);

        while (*myFile >> val) {
            isNode ? x_i.push_back(val) : fx_i.push_back(val);
            isNode = !isNode;
        }
    }
    else {
        return -1;
    }


    //Get x:
    cout << "-------TASK 1-------\n";
    cout << "Provide point x: ";
    cin >> x;

    //Calculate degree
    N = x_i.size() - 1; //equivalent to max i

    //Further calculations
    l_i = calculate_l_i(N, x, x_i);
    LNx = calculate_Langrange_poly(N, x, fx_i, l_i);
    
    //Print results
    printResults(x, LNx, x_i, fx_i, l_i);
    myFile->close();
    delete myFile;

    // x = 50^1/3
    // x0 = 27, x1 = 64 x2 = 125 x3 = 216
    //  f(x_i) = x^1/3
    // L(x) = ?
    cout << "\n-------TASK 2-------\n";
    //x = pow(50.0, 1.0 / 3.0);
    x_i.clear();
    fx_i.clear();
    l_i.clear();
    x_i.push_back(27.0);
    x_i.push_back(64.0);
    x_i.push_back(125.0);
    x_i.push_back(216.0);
    N = x_i.size() - 1;
    for (auto x : x_i) {
        float val = pow(x, 1.0 / 3.0);
        fx_i.push_back(val);
    }
    l_i = calculate_l_i(N, 50, x_i);
    LNx = calculate_Langrange_poly(N, 50, fx_i, l_i);
    printResults(x, LNx, x_i, fx_i, l_i);

}
