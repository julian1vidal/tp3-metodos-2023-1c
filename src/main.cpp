#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Dense>
#include "metodos_iterativos.cpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file" << endl;
        return 1;
    }

    const char* input_file = argv[1];
    const char* output_file = argv[2];

    ifstream fin(input_file);
    if (!fin.is_open()) {
        cerr << "Error: could not open input file " << input_file << endl;
        return 1;
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

    cout << "==========================" << endl;
    cout << "A: " << A << endl;
    cout << "--------------------------" << endl;
    cout << "b: " << b << endl;
    cout << "==========================" << endl;

    // Soluciones de cada metodo
    VectorXd sol_jacobi_mat = jacobi_mat(A, b);
    VectorXd sol_jacobi_sum = jacobi_sum(A, b);
    VectorXd sol_gs_mat = gs_mat(A, b);
    VectorXd sol_gs_sum = gs_sum(A, b);
    VectorXd sol_eigen_lu = A.lu().solve(b);

    cout << "==========================" << endl;
    cout << "Jacobi matricial: " << sol_jacobi_mat << endl;
    cout << "==========================" << endl;
    cout << "Jacobi sumatoria: " << sol_jacobi_sum << endl;
    cout << "==========================" << endl;
    cout << "GS matricial: " << sol_gs_mat << endl;
    cout << "==========================" << endl;
    cout << "GS sumatoria: " << sol_gs_sum << endl;
    cout << "==========================" << endl;
    cout << "Eigen LU: " << sol_eigen_lu << endl;
    cout << "==========================" << endl;

    // // A donde los mandamos?

    // // Write result to output file
    // ofstream fout(output_file);
    // if (!fout.is_open()) {
    //     cerr << "Error: could not open output file " << output_file << endl;
    //     return 1;
    // }

    // fout << c.transpose() << endl;

    // fout.close();



    return 0;
}
