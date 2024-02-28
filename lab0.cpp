#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::stringstream;

int main()
{
    //węzły interpolacji + wartości funkcji w węzłach (x1 x2, f(x1), f(x2) itd) zmienne z pliku tekstowego 
    //punkt w ktorym obliczany jest wartosc wielomianu (x) parametr podawany z klawaitury 
    //output: liczba węzłów, dane: x1,x2 f(x1), f(x2), x, wartość wielomainu lagrange'a w punkcie x => L(x)
    std::fstream myFile;
    std::string line;
    std::vector<float> x_i, fx_i; //nodes and values in interpolation nodes
    std::vector<float> l_i;
    float x;
    int N; //stopien wielomianu, N = x_i.size() -1;
    int node_count;
    myFile.open("C:/Numerical Methods/28.02_Interpolation/lab0/nodes.txt", std::ios_base::in);
    int counter = 0;
    float  LNx = 0;
    if (myFile.good()) {
        int val;
        bool isNode = true;
        while (myFile >> val) {
            isNode ? x_i.push_back(val) : fx_i.push_back(val);
            isNode = !isNode;
        }
    }
    cout << "Provide point X: ";
    cin >> x;

    node_count = x_i.size();
    N = node_count - 1; //equivalent to max i

    for (int i = 0, j = 0; i < N, j < N; i++, j++) {
        if (i == j) continue;
        float l_val = (x - x_i[j]) / (x_i[i] - x_i[j]); //modify this later, i'm sure it's wrong

        l_i.push_back(l_val);
    }

    for (int i = 0; i < N; i++) {
        LNx += fx_i[i] * l_i[x];
    }

    cout << "x: " << x << endl;
    cout << "L(x)" << LNx << endl;
    cout << "x_i: " << endl;
    for (auto x : x_i) cout << x << endl;
    cout << "fx_i: " << endl;
    for (auto y : fx_i) cout << y << endl;
    myFile.close();

    
}
