#include "FileHandler.h"
std::fstream* open_file(std::string path) {
     std::fstream* file = new std::fstream;
     file->open(path, std::ios_base::in);
     if (file->bad()) {
         std::cout << "can't read file, exiting\n";
         exit(0);
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
    fileA->close();
    fileB->close();
    return matrix;
}
std::vector<double> read_file_content(std::fstream* file) {
    std::string line;
    std::vector<double> toReturn;
    while (std::getline((*file), line)) {
        std::stringstream ss(line);
        double num;
        ss >> num;
        toReturn.push_back(num);
    }
    file->close();
    return toReturn;
}