#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

enum point_id {
	X,
	Y
};
/*
	F_k = sum from j = 0 to n (g_kj * a_j)
	F_k = sum from i = 0 to m (phi_k(x_i) * f(x_i) * w(x_i)
	g_kj = sum from i = 0 to m (phi_k(x_i) * phi_j(x_i) * w(x_i)
	phi_k(x) = x^k for k = 0, 1, 2....n
	phi_j(x) = x^j for j = 0,1,2....n
	F(x) = sum from j = 0 to n (a_j * phi_j(x) )
	m = nodes - 1 I guess
	n = degree of polynomial

*/
int set_n() {
	int toReturn;
	std::cout << "degree of polynomial (n): ";
	do {
		std::cin >> toReturn;
	} while (toReturn < 0);
	return toReturn;
}

Vector set_w(double(*f)(double val), Matrix points) {
	Vector w_xi;
	int size = points.size();
	for (int index = 0; index < size; index++) {
		w_xi.push_back(f(points[index][X]));
	}
	return w_xi;
}
Vector set_w(double wage, Matrix points) {
	Vector w_xi;
	int size = points.size();
	for (int index = 0; index < size; index++) {
		w_xi.push_back(wage);
	}
	return w_xi;
}
Matrix set_phi(Matrix points, int n) {
	Matrix phi;
	/// <summary>
	/// return matrix of phi of each node (x_i) for each column/row 
	/// example: 4 nodes x_i for j = 0 {1,2,3,4} etc.
	/// </summary>
	
	for (int j = 0; j <= n; j++) {
		Vector row;
		for (int point = 0; point < points.size(); point++) {
			row.push_back(pow(points[point][X], j));
		}
		phi.push_back(row);
	}
	return phi;
}

Matrix set_points(std::fstream* file) {
	Matrix points;
	if (!file->good()) return Matrix{};
	std::string line; 
	while (std::getline(*file, line)) {
		Vector row;
		double num;
		std::stringstream s(line);
		while (s >> num) row.push_back(num);

		points.push_back(row);
	}
	file->close();
	return points;
}
Matrix set_g(Matrix phi_k, Matrix phi_j, Vector w, int m, int n) {
	Matrix g;
	for (int k = 0; k <= n; k++) {
		Vector row;
		for (int j = 0; j <= n; j++) {
			double g_kj = 0;
			for (int i = 0; i <= m; i++) {
				g_kj += phi_k[k][i] * phi_j[j][i] * w[i];
			}
			row.push_back(g_kj);
		}
		g.push_back(row);
	}
	return g;
}
Vector set_F(Matrix phi_k, Matrix points, Vector w, int m, int n) {
	Vector F;
	for (int k = 0; k <= n; k++) {
		double F_k = 0;
		for (int i = 0; i <= m; i++) {
			F_k += phi_k[k][i] * points[i][Y] * w[i];
		}
		F.push_back(F_k);
	}
	return F;
}
Vector calculate_Fx(Matrix points, Vector a_j, Matrix phi_j, int m, int n) {
	Vector F_x;
	for (int i = 0; i <= m; i++) {
		double F_xi = 0;
		for (int j = 0; j <= n; j++) {
			F_xi = a_j[j] * phi_j[j][i];
		}
		F_x.push_back(F_xi);
	}
	return F_x;
}
std::fstream* read_from_file(std::string path) {
	std::fstream* file = new std::fstream;
	file->open(path, std::ios_base::in);
	return file;
}
void print_matrix(Matrix mat) {
	for (auto& x : mat) {
		for (auto y : x) std::cout << y << "\t";
		std::cout << "\n";
	} 
	std::cout << "\n";
}
Matrix merge_system(Matrix g, Vector F, int n) {
	Matrix toReturn = g;
	for (int k = 0; k <= n; k++) {
		toReturn[k].push_back(F[k]); 
	}
	return toReturn;
}
Vector solve_system(Matrix& system) {
	int n = system.size();
	float m = 0;
	for (int z = 0; z < n; z++) {

		for (int i = z + 1; i < n; i++) {
			m = system[i][z] / system[z][z];
			for (int j = 0; j < n + 1; j++) {
				system[i][j] -= (system[z][j] * m);
			}
		}
	}
	std::cout << "After: \n";
	print_matrix(system);
	Vector results(n);
	for (int i = n - 1; i >= 0; --i) {
		results[i] = system[i][n] / system[i][i];
		for (int j = i - 1; j >= 0; --j) {
			system[j][n] -= system[j][i] * results[i];
		}
	}
	return results;
}
int main() {
	Vector w_i, a_j, F_k, F_x;
	Matrix g_kj, phi_j, phi_k, system;
	const Matrix points = set_points(read_from_file("points.txt"));
	int n, m, i, j, k;

	n = set_n();
	m = points.size() - 1;
	w_i = set_w(1, points);

	print_matrix(points);
	phi_j = set_phi(points, n);
	phi_k = phi_j;

	g_kj = set_g(phi_k, phi_j, w_i, m, n);
	F_k = set_F(phi_k, points, w_i, m, n);
	std::cout << "g:\n";
	print_matrix(g_kj);
	std::cout << "F:\n";
	print_matrix(Matrix{{F_k}});

	std::cout << "System:\n";
	system = merge_system(g_kj, F_k, n);
	print_matrix(system);

	a_j = solve_system(system);
	F_x = calculate_Fx(points, a_j, phi_j, m, n);
	/*Final results*/
	std::cout << "Liczba wezlow: " << points.size() << "\n";
	std::cout << "wspolczynniki a_i:\n";
	print_matrix(Matrix{ {a_j} });
	std::cout << "F_x:\n";
	print_matrix(Matrix{ {F_x} });


	return 0;

}