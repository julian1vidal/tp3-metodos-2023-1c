#include "metodos_iterativos.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;
#define tolerance 1e-14

// =============================================================
//                     Funciones auxiliares
// =============================================================

double sumatoria_jacobi(const MatrixXd& A, const VectorXd& x_anterior, int i, int cols){
    double suma = 0;
    for (int j = 0; j < cols; j++){
        if (j != i){
            suma += (A(i, j) * x_anterior[j]);
        }
    }
    return suma;
}


double sumatoria_gs_x(const MatrixXd& A, const VectorXd& x, int i){
    double suma = 0;
    for (int j = 0; j < i; j++){
        suma += (A(i, j) * x[j]);
    }
    return suma;
}

double sumatoria_gs_x_anterior(const MatrixXd& A, const VectorXd& x_anterior, int i, int cols){
    double suma = 0;
    for (int j = i+1; j < cols; j++){
        suma += (A(i, j) * x_anterior[j]);
    }
    return suma;
}

struct entrada{
    Eigen::MatrixXd A;
    Eigen::VectorXd b;
    Eigen::VectorXd real_x;
    int iter;
};

entrada matrix_reader(int argc, char** argv){
    entrada res;

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

    VectorXd real_x(ncols);
    for (int i = 0; i < ncols; i++) {
        fin >> real_x(i);
    }

    fin.close();
    
    res.A = A;
    res.b = b;
    res.real_x = real_x;
    return res;    
}

int out_to_python(const VectorXd& x){
    // Write result to output file
    ofstream fout("salida.txt");
    if (!fout.is_open()) {
        std::cerr << "Error: could not open output file " << endl;
        return 1;
    }
    // write with more precision
    fout.precision(16);
    fout << x.transpose() << endl;

    fout.close();
    return 0;
}

void write_errors_to_file(const VectorXd& errors){
    ofstream fout("errores.txt");
    if (!fout.is_open()) {
        std::cerr << "Error: could not open output file " << endl;
        return;
    }

    fout << errors.transpose();

    fout.close();
}

void write_times_to_file(double time){
    ofstream fout("tiempos.txt");
    if (!fout.is_open()) {
        std::cerr << "Error: could not open output file " << endl;
        return;
    }

    fout << time;

    fout.close();
}

void write_iters_to_file(int iters){
    ofstream fout("iters.txt");
    if (!fout.is_open()) {
        std::cerr << "Error: could not open output file " << endl;
        return;
    }

    fout << iters;

    fout.close();
}


bool not_a_number(const VectorXd& x){
    for (int i = 0; i < x.size(); i++){
        if (isnan(x[i]) || isinf(x[i])){
            return true;
        }
    }
    return false;
}