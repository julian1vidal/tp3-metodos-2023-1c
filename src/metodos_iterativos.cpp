#include "metodos_iterativos.h"
#include <iostream>
#include <fstream>
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;


// =============================================================
//                     Funciones auxiliares
// =============================================================

double sumatoria_jacobi(MatrixXd A, VectorXd x_anterior, int i, int cols){
    double suma = 0;
    for (int j = 0; j < cols; j++){
        if (j != i){
            suma += (A(i, j) * x_anterior[j]);
        }
    }
    return suma;
}


double sumatoria_gs_x(MatrixXd A, VectorXd x, int i){
    double suma = 0;
    for (int j = 0; j < i; j++){
        suma += (A(i, j) * x[j]);
    }
    return suma;
}

double sumatoria_gs_x_anterior(MatrixXd A, VectorXd x_anterior, int i, int cols){
    double suma = 0;
    for (int j = i+1; j < cols; j++){
        suma += (A(i, j) * x_anterior[j]);
    }
    return suma;
}

struct entrada{
    Eigen::MatrixXd A;
    Eigen::VectorXd b;
    int iter;
};

entrada matrix_reader(int argc, char** argv){
    entrada res;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " iteraciones" << endl;
        return res;
    }

    const char* input_file = "entrada.txt";
    const char* output_file = "salida.txt";

    ifstream fin(input_file);
    if (!fin.is_open()) {
        std::cerr << "Error: could not open input file " << input_file << endl;
        return res;
    }

    // Read matrix and vector from file
    int nrows, ncols;
    fin >> nrows >> ncols;

    MatrixXd A(nrows, ncols);
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            fin >> A(i, j);
        }
    }

    VectorXd b(ncols);
    for (int i = 0; i < ncols; i++) {
        fin >> b(i);
    }

    fin.close();
    
    res.A = A;
    res.b = b;
    return res;    
}

int out_to_python(VectorXd x){
    // Write result to output file
    ofstream fout("salida.txt");
    if (!fout.is_open()) {
        std::cerr << "Error: could not open output file " << endl;
        return 1;
    }

    fout << x.transpose() << endl;

    fout.close();
    return 0;
}