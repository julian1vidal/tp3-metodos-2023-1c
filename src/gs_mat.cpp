#include "metodos_iterativos.cpp"

VectorXd gs_mat(MatrixXd A, VectorXd b, int iter){
    int cols = b.size();
    VectorXd x = VectorXd::Random(cols);

    // A = D-L-U
    MatrixXd D = A.diagonal().asDiagonal();
    MatrixXd L = A.triangularView<Eigen::StrictlyLower>();
    MatrixXd U = A.triangularView<Eigen::StrictlyUpper>();
    L *= -1;
    U *= -1;

    // Creo T y c
    MatrixXd gs_inversa = (D-L).inverse();
    MatrixXd T = gs_inversa * U;
    VectorXd c = gs_inversa * b;

    for (int i = 0; i < iter; i++){
        x = (T*x) + c;
    }

    return x;
}

int main(int argc, char** argv) {
    entrada entry = matrix_reader(argc, argv);
    VectorXd x = gs_mat(entry.A, entry.b, atoi(argv[1]));
    out_to_python(x);
}