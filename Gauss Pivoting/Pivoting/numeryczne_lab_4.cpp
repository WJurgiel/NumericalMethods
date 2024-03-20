#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

const double SMALL_NUMBER = 10e-8;

using namespace std;

void displayMatrix(vector<vector<double>>& m)
{
	for (int i = 0; i < m.size(); i++)
	{
		cout << m[i][0] << " x_0";

		for (int j = 1; j < m[i].size() - 1; j++)
		{
			cout << " + " << m[i][j] << " x_" << j;
		}

		if (m[i].size() > 1)
		{
			cout << " = " << m[i][m[i].size() - 1];
		}

		cout << endl;
	}
}

void displayMatrixCrout(vector<vector<double>>& m, vector<int> columns)
{
	for (int i = 0; i < m.size(); i++)
	{
		cout << m[i][columns[0]] << " x_0";

		for (int j = 1; j < m[i].size() - 1; j++)
		{
			cout << " + " << m[i][columns[j]] << " x_" << j;
		}

		if (m[i].size() > 1)
		{
			cout << " = " << m[i][m[i].size() - 1];
		}

		cout << endl;
	}
}

void eliminacja(vector<vector<double>>& m)
{
	double mult;

	for (int k = 0; k < m.size(); k++) // numer diagonalnej
	{
		for (int i = k + 1; i < m.size(); i++) //i to numer rzędu
		{
			mult = m[i][k] / m[k][k];
			//cout << "m" << i + 1 << k << " = " << mult << endl;
			for (int j = k; j < m[i - 1].size(); j++) //j to numer kolumny
			{
				m[i][j] -= mult * m[k][j];

				if (abs(m[i][j]) < SMALL_NUMBER)
				{
					m[i][j] = 0;
				}
			}
			//cout << endl;
			//displayMatrix(m);
		}
	}
}

void eliminacjaCrout(vector<vector<double>>& m, vector<int>& columns)
{
	double mult;

	for (int k = 0; k < m.size(); k++) // numer diagonalnej
	{
		for (int i = k + 1; i < m.size(); i++) //i to numer rzędu
		{
			mult = m[i][columns[k]] / m[k][columns[k]];
			//cout << "m" << i + 1 << k << " = " << mult << endl;
			for (int j = k; j < m[i - 1].size(); j++) //j to numer kolumny
			{
				m[i][columns[j]] -= mult * m[k][columns[j]];

				if (abs(m[i][columns[j]]) < SMALL_NUMBER)
				{
					m[i][columns[j]] = 0;
				}
			}
			//cout << endl;
			//displayMatrixCrout(m, columns);
		}
	}
}


vector<double> solveTriangle(vector<vector<double>>& m)
{
	int n = m.size() - 1;
	vector<double> solution(n + 1);
	solution[n] = m[n][n + 1] / m[n][n]; //b_n przez m_nn
	double sum = 0;
	for (int i = n - 1; i >= 0; i--) // obliczamy rozwiazania od x_n-1 do x_0
	{
		sum = 0;
		for (int k = i + 1; k <= n; k++) // petla dla sumy
		{
			sum += m[i][k] * solution[k];
			//cout << " do sumy " << m[i][k] << " * " << solution[k] << endl;
		}
		solution[i] = (m[i][n + 1] - sum) / m[i][i];
		//cout << m[i][i + 1] << " - " << sum << ") / " << m[i][i] << endl;
		//cout << "x_" << i << " = " << solution[i] << endl;
	}

	for (int i = 0; i < n + 1; i++)
	{
		cout << "x_" << i << " = " << solution[i] << endl;
	}
	return solution;
}

vector<double> solveGaussCrout(vector<vector<double>>& m, vector<int>& columns)
{
	int n = m.size() - 1;
	vector<double> solution(n + 1);
	solution[n] = m[n][columns[n + 1]] / m[n][columns[n]]; //b_n przez m_nn
	double sum = 0;
	for (int i = n - 1; i >= 0; i--) // obliczamy rozwiazania od x_n-1 do x_0
	{
		sum = 0;
		for (int k = i + 1; k <= n; k++) // petla dla sumy
		{
			sum += m[i][columns[k]] * solution[k];
			//cout << " do sumy " << m[i][k] << " * " << solution[k] << endl;
		}
		solution[i] = (m[i][columns[n + 1]] - sum) / m[i][columns[i]];
		//cout << m[i][i + 1] << " - " << sum << ") / " << m[i][i] << endl;
		//cout << "x_" << i << " = " << solution[i] << endl;
	}

	for (int i = 0; i < n + 1; i++)
	{
		cout << "x_" << i << " = " << solution[i] << endl;
	}
	return solution;
}

bool diagonalHasZeroes(vector<vector<double>>& m)
{
	for (int i = 0; i < m.size(); i++)
	{
		if (m[i][i] < SMALL_NUMBER)
		{
			return true;
		}
	}
	return false;
}

void swapRows(vector<vector<double>>& m, int first, int second)
{
	vector<double> temp;
	temp = m[first];
	m[first] = m[second];
	m[second] = temp;
}

void partialPivot(vector<vector<double>>& m)
{
	for (int i = 0; i < m.size(); i++)
	{
		int maxIndex = i;
		for (int j = i + 1; j < m.size(); j++)
		{
			//cout << matrix[j][i] << " > " << matrix[maxIndex][i] << endl;
			if (abs(m[j][i]) > m[maxIndex][i])
			{
				//cout << "Nowy maxindex" << endl;
				maxIndex = j;
			}
		}
		swapRows(m, maxIndex, i);
	}
	cout << "Po wyborze czesciowym:" << endl;
	displayMatrix(m);
}

void croutPivot(vector<vector<double>>& m, vector<int>& columns)
{
	for (int i = 0; i < m.size(); i++)
	{
		int maxIndex = i;
		for (int j = i + 1; j < m.size(); j++)
		{
			//cout << m[i][columns[j]] << " > " << m[i][columns[maxIndex]] << endl;
			if (abs(m[i][columns[j]]) > m[i][columns[maxIndex]])
			{
				//cout << "Nowy maxindex" << endl;
				maxIndex = j;
			}
		}
		int temp = columns[maxIndex];
		columns[maxIndex] = columns[i];
		columns[i] = temp;

		//swapRows(m, maxIndex, i);
	}
	cout << "Po pivocie Gauss-Craut:" << endl;
	for (int i = 0; i < columns.size(); i++)
	{
		cout << columns[i] << " ";
	}
	cout << endl;
	displayMatrixCrout(m, columns);
}



int main()
{
	ifstream myFile;
	myFile.open("A1.txt");

	vector<vector<double>> matrix;
	vector<vector<double>> matrix2;
	vector<int>columnNumbers;

	string line;
	string element;
	int numberOfLines = 0;

	while (getline(myFile, line))
	{
		stringstream ss(line);
		matrix.push_back({});
		while (ss >> element)
		{
			matrix[numberOfLines].push_back(stod(element));
		}
		numberOfLines++;
	}

	myFile.close();
	myFile.open("A2.txt");

	for (int i = 0; i < matrix.size(); i++)
	{
		myFile >> element;
		matrix[i].push_back(stod(element));
	}
	myFile.close();

	for (int i = 0; i < matrix[0].size(); i++)
	{
		columnNumbers.push_back(i);
		//cout << i << endl;
	}

	matrix2 = matrix;

	cout << "Jest macierz:" << endl;
	displayMatrix(matrix);

	partialPivot(matrix);

	if (diagonalHasZeroes(matrix))
	{
		cout << "Na przekatnej sa zera, koniec programu." << endl;
		return -1;
	};

	eliminacja(matrix);
	cout << "Po eliminacji:" << endl;
	displayMatrix(matrix);
	cout << "Rozwiazania:" << endl;
	vector<double> solutions;
	solutions = solveTriangle(matrix);

	cout << "====== Gauss-crout =======" << endl;
	cout << "Jest macierz:" << endl;
	displayMatrix(matrix2);

	croutPivot(matrix2, columnNumbers);

	if (diagonalHasZeroes(matrix2))
	{
		cout << "Na przekatnej sa zera, koniec programu." << endl;
		return -1;
	};



	eliminacjaCrout(matrix2, columnNumbers);
	cout << "Po eliminacji:" << endl;
	displayMatrixCrout(matrix2, columnNumbers);
	cout << "Rozwiazania:" << endl;
	vector<double> solutions2;
	solutions2 = solveGaussCrout(matrix2, columnNumbers);
	return 0;
}