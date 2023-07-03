#include "metodos_iterativos.cpp"

VectorXd gs_mat(MatrixXd A, VectorXd b, int iter, VectorXd real_x, double tol, bool write_errors){
    auto start_time = chrono::high_resolution_clock::now();
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
    VectorXd errors;

    for (int i = 0; i < iter; i++){
        x = (T*x) + c;
        double err = (x - real_x).norm();
        if (write_errors){
            errors.conservativeResize(errors.size()+1);
            errors(errors.size()-1) = err;
        }
        if (tol != 0 && err < tol || not_a_number(x)){
            break;
        }
        cout << "iteración " << i << endl;
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    write_times_to_file(time);
    if (write_errors){
        write_errors_to_file(errors);
    }
    return x;
}

int main(int argc, char** argv) {
    entrada entry = matrix_reader(argc, argv);
    bool write_errors = false;
    if (argv[2]){
        write_errors = true;
    }
    VectorXd x = gs_mat(entry.A, entry.b, atoi(argv[1]), entry.real_x, tolerance, write_errors);
    out_to_python(x);
}