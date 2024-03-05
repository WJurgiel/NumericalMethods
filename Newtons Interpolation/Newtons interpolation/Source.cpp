#include <iostream>
#include <vector>
#include <fstream>
#include <string>
/*
* @made by: WJurgiel
	NEWTON'S INTERPOLATION
	- nodes + function values in nodes + number of nodes -> read from data.txt
	- x -> read from input
	- Output:
		- number of nodes
		- nodes + function value in nodes
		- x
		- value of Newton's polynomial
		- b_k
	DATA.txt MUST look like that:
	Node count:\n
	<node count>\n
	x_i\tfx_i\n
	<x_i>\t<fx_i>\n
	...
	Otherwise, code won't work as it should (or even worse, it won't work at all)
*/
void printOutput(std::vector<double>& x_i, std::vector<double>& fx_i, unsigned& node_count, double x, double w_x) {
	std::cout << "node count: " << node_count;
	std::cout << "\nx_i: ";
	for (auto x : x_i) std::cout << x << " ";
	std::cout << "\nfx_i: ";
	for (auto f : fx_i) std::cout << f << " ";
	std::cout << "\n";
	std::cout << "For value x == " << x << " w_x = " << w_x << "\n";
}
std::fstream* readFromFile(std::string filePath) {
	std::fstream* file = new std::fstream;
	file->open(filePath, std::ios_base::in);
	return file;
}
double calculate_p_k(unsigned k, double x, std::vector<double>& x_i) {
	// simple multiplication, it looks just like in the instructions
	double p_k = 1;
	for (unsigned i = 0; i <= k-1; i++) {
		p_k *= (x - x_i[i]);
	}
	return p_k;
}
double calculate_b_k(unsigned k, double x, std::vector<double>& x_i, std::vector<double>& fx_i) {
	// simple addition, with multiplication inside (denominator)
	double b_k = 0;
	double den = 1; //denominator, calculated in inner for loop
	for (unsigned i = 0; i <= k; i++)
	{
		den = 1;
		for (unsigned j = 0; j <= k; j++) {
			if (j == i) continue;
			den *= (x_i[i] - x_i[j]);
		}
		b_k += (fx_i[i] / den);
	}
	return b_k;
}
int main() {
	/*
		KEY VALUES
	*/
	std::vector<double> x_i, fx_i;
	unsigned node_count, k;
	std::fstream* file = readFromFile("data.txt");
	double x, b_k, p_k, w_x, p_0, b_0; //w_x is Newton's polynomial value
	double bkpk = 0.0;
	/*
		AUXILIARY VALUES
	*/
	double aux_val = 0; // store value from file in it
	bool isNode = true; 
	std::string aux_line;

	if(file->bad()){
		//exit when can't find/read file, why would we continue?
		std::cout << "[ERROR]: Can't read the file\n";
		return -1;
	}


	std::getline((*file), aux_line); //skip the "Node count:\n"
	(*file) >> node_count; 
	std::getline((*file), aux_line); // skip the <node count>
	std::getline((*file), aux_line); // skip the x_i\tfx_i\n
	
	while (*file >> aux_val) {
		
		isNode ? x_i.push_back(aux_val) : fx_i.push_back(aux_val);
		isNode = !isNode;
	}

	std::cout << "Input x: "; std::cin >> x;
	p_0 = 1.0; 
	b_0 = fx_i[0];
	k = 1;
	
	//bkpk is the sum of the multiplications for k <1, degree of polynomial (node_count -1)>
	while (k < node_count) {
		p_k = calculate_p_k(k,x, x_i);
		b_k = calculate_b_k(k, x, x_i, fx_i);
		bkpk += (p_k * b_k);
		//std::cout << "p_k: [" << k << "]: " << p_k << "\n"; //this doesn't have to printed, but b_k does
		std::cout << "b_k: [" << k << "]: " << b_k << "\n";
		k += 1;
	}
	w_x = (b_0 * p_0) + bkpk;
	printOutput(x_i, fx_i, node_count, x, w_x);
	/*
		Results: w_x for x == 5.0 = 25
				w_x for x == 10.0 = 100
	*/

	/*
		CLEAN UP 
	*/
	file->close();
	delete file;
	return 0;
}