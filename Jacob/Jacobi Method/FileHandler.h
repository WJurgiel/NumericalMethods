#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::fstream* open_file(std::string path);
std::vector<std::vector<double>> read_files_content(std::fstream* fileA, std::fstream* fileB);