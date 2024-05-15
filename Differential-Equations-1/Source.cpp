#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <fstream>
using Vector = std::vector<double>;
using Function = std::function<double(double, double)>;
//dowolny warunek pocz¹tkowy

/*
	Wypisaæ:
	- warunek pocz¹tkowy
	- punkt koñcowy
	- krok obliczeñ
	- rozwi¹zanie metod¹ Eulera w punkcie koñcowym
	- rozwi¹zanie RK2 
	- rozwi¹zanie RK4

	h = (b - a)/ N
	x_i = a + ih
	y(x_i+1) = y(x_i) + hf(x_i, y_i)
*/
Function func1 = [](double x, double y) {
	return 2 * y * x + 2 * y;
};
Function func2 = [](double x, double y) {
	return x + y;
};
Function funcTest = [](double x, double y) {
	return x * x + y;
};
double calculate_h(double a, double b, int N) {
	return (b - a) / N;
}
Vector calculate_all_x_i(int N,	double h, double a) {
	Vector toReturn;
	toReturn.push_back(a);
	for (int i = 0; i < N; i++) {
		double x_i = a + (i + 1) * h;
		toReturn.push_back(x_i);
	}
	return toReturn;
}
Vector Euler_calculate_all_y_i(Function func, Vector x_i,  double h, double y_a, int N) {
	Vector toReturn;
	toReturn.push_back(y_a);
	for (int i = 1; i <= N; i++) {
		double y_i_1 = toReturn[i - 1] + h * func(x_i[i - 1], toReturn[i - 1]); 
		/*std::cout << "i + 1 = " << i << "\n";
		std::cout << "y_i = " << toReturn[i - 1] << "\n";
		std::cout << "x_i = " << x_i[i - 1] << "\n";
		std::cout << "f(x_i,, y_i) = " << func(x_i[i - 1], toReturn[i - 1]) << "\n";
		std::cout << "--------------\n";*/
		toReturn.push_back(y_i_1);
	}
	return toReturn;
}
Vector RK2_calculate_all_y_i(Function func, Vector x_i, double h, double y_a, int N) {
	Vector toReturn;
	toReturn.push_back(y_a);
	for (int i = 1; i <= N; i++) {
		double k_1 = func(x_i[i - 1], toReturn[i - 1]);
		double k_2 = func(x_i[i - 1] + h, toReturn[i - 1] + h * k_1);
		double phi = 0.5 * (k_1 + k_2);

		double y_i_1 = toReturn[i - 1] + h * phi;
		toReturn.push_back(y_i_1);
	}

	return toReturn;
}
Vector RK4_calculate_all_y_i(Function func, Vector x_i, double h, double y_a, int N) {
	Vector toReturn;
	toReturn.push_back(y_a);

	for (int i = 1; i <= N; i++) {
		double k_1 = func(x_i[i - 1], toReturn[i - 1]);
		double k_2 = func(x_i[i - 1] + 0.5 * h, toReturn[i - 1] + 0.5 * h * k_1);
		double k_3 = func(x_i[i - 1] + 0.5 * h, toReturn[i - 1] + 0.5 * h * k_2);
		double k_4 = func(x_i[i - 1] + h, toReturn[i - 1] + h * k_3);
		double phi = 1.0 / 6.0 * (k_1 + 2* k_2 + 2 * k_3 + k_4);

		double y_i_1 = toReturn[i - 1] + h * phi;
		toReturn.push_back(y_i_1);
	}
	return toReturn;
}
double print_result(Vector vec) {
	return vec[vec.size() - 1];
}
void print_vector(Vector vec) {
	for (auto& x : vec) {
		std::cout << x << "\n";
	}
}
void print_to_file(std::string path, Vector y_i, int N) {
	std::ofstream* file = new std::ofstream;
	file->open(path);
	if (file->bad()) {
		std::cout << "can't read the file";
		return;
	}
	for (int i = 0; i < y_i.size(); i++) {
		*file << i << "\t" << y_i[i] << "\n";
	}
	file->close();
	delete file;
}
void solve(Function& func, Vector& x_i, double& h, double& a, double& y_a, int N, std::string actual, std::string id) {
	Vector y_i_eul, y_i_rk2, y_i_rk4;

	std::cout << "y(" << a << ")" << "=" << y_a << "\n";
	std::cout << "Step: " << h << "\n";
	std::cout << "Final point: " << N << "\n";
	std::cout << "Euler: ";
	y_i_eul = Euler_calculate_all_y_i(func, x_i, h, y_a, N);
	//std::cout << y_i_eul[N];
	std::cout << print_result(y_i_eul);

	std::cout << "\nRK2: ";
	y_i_rk2 = RK2_calculate_all_y_i(func, x_i, h, y_a, N);
	//std::cout << y_i_rk2[N];
	std::cout << print_result(y_i_rk2);

	std::cout << "\nRK4: ";
	y_i_rk4 = RK4_calculate_all_y_i(func, x_i, h, y_a, N);
	//std::cout << y_i_rk4[N];
	std::cout << print_result(y_i_rk4);

	std::cout << "\nActual: " << actual;
	std::cout << "\n--------------------------------\n";

	print_to_file(id + "_euler.txt",y_i_eul, N);
	print_to_file(id + "_RK2.txt",y_i_rk2, N);
	print_to_file(id + "_RK4.txt",y_i_rk4, N);
}

int main() {
	//wyznaczyc rozwiazanie w punkcie x = 1 i dla N = 10
	// y'(x) = 2yx + 2y, y(0) = 1.0
	// y'(x) = x + y, y(0) = 0.1
	double a, y_a, b, h;
	int N = 10;
	int x = 1;
	Vector x_i, y_i_eul, y_i_rk2, y_i_rk4;
	
	a = 0, b = x;
	
	h = calculate_h(a, b, N);
	x_i = calculate_all_x_i(N, h, a);

	/*PRZYK£AD 1*/
	std::cout << "y'(x) = 2yx + 2y:\n";
	y_a = 1.0;
	solve(func1, x_i, h, a, y_a, N, "20.0855", "1");

	///*PRZYK£AD 2*/
	std::cout << "\ny'(x) = x + y:\n";
	y_a = 0.1;
	solve(func2, x_i, h, a, y_a, N, "0.99011", "2");




	///*PRZYK£AD 3*/
	//x = 0.3;
	//N = 3;
	//a = 0; b = x;
	//y_a = 0.1;
	//h = calculate_h(a, b, N);
	//h = calculate_h(a, b, N);
	//x_i = calculate_all_x_i(N, h, a);
	//print_vector(x_i);


	//std::cout << "Euler:\n";
	//y_i_eul = Euler_calculate_all_y_i(funcTest, x_i, h, y_a, N);
	//print_result(y_i_eul);

	//std::cout << "RK2:\n";
	//y_i_rk2 = RK2_calculate_all_y_i(funcTest, x_i, h, y_a, N);
	//print_result(y_i_rk2);

	//std::cout << "RK4:\n";
	//y_i_rk4 = RK4_calculate_all_y_i(funcTest, x_i, h, y_a, N);
	//print_result(y_i_rk4);
	//

	return 0;
}