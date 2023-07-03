#include "metodos_iterativos.cpp"

VectorXd LUSOLVER(MatrixXd A, VectorXd b, int iter, VectorXd real_x, double tol, bool write_errors){
    auto start_time = chrono::high_resolution_clock::now();
    VectorXd x = A.lu().solve(b);
    auto end_time = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    write_times_to_file(time);
    double err = (x - real_x).norm();
    VectorXd errors = VectorXd::Zero(1);
    errors(0) = err;
    write_errors_to_file(errors);
    return x;
}

int main(int argc, char** argv) {
    entrada entry = matrix_reader(argc, argv);
    bool write_errors = false;
    if (argv[2]){
        write_errors = true;
    }
    VectorXd x = LUSOLVER(entry.A, entry.b, atoi(argv[1]), entry.real_x, tolerance, write_errors);
    out_to_python(x);
}