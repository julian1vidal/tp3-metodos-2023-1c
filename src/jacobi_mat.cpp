#include "metodos_iterativos.cpp"

VectorXd jacobi_mat(const MatrixXd& A, const VectorXd& b, int iter, const VectorXd& real_x, double tol, bool write_errors){
    auto start_time = chrono::high_resolution_clock::now();
    int cols = b.size();

    // vector random (por defecto)
    VectorXd x = VectorXd::Random(cols);

    // para crear vector cercano
    // VectorXd x = real_x;
    // Eigen::VectorXd random_values = Eigen::VectorXd::Random(x.size());
    // double epsilon = 0.001;
    // x += epsilon * random_values;
    // cout << "Norma 2 (x0 - real_x): " << (x0 - real_x).norm() << endl;

    // para crear vector ortog
    // Eigen::JacobiSVD<Eigen::MatrixXd> svd(real_x.transpose(), Eigen::ComputeFullV);
    // Eigen::MatrixXd V = svd.matrixV();
    // Eigen::VectorXd x = V.col(V.cols() - 1);
    // cout << "Producto escalar: " << x.dot(real_x) << endl;


    int iters_convergencia = iter;

    // A = D-L-U
    MatrixXd D = A.diagonal().asDiagonal();
    MatrixXd L = A.triangularView<Eigen::StrictlyLower>();
    MatrixXd U = A.triangularView<Eigen::StrictlyUpper>();
    L *= -1;
    U *= -1;

    // Creo T y c
    MatrixXd gs_inversa = D.inverse();
    MatrixXd T = gs_inversa * (L+U);
    VectorXd c = gs_inversa * b;
    VectorXd errors;
    for (int i = 0; i < iter; i++){
        x = (T*x) + c;
        double err = (x - real_x).norm();
        if (write_errors){
            errors.conservativeResize(errors.size()+1);
            errors(errors.size()-1) = err;
        }
        if ((tol != 0 && err < tol) || not_a_number(x)){
            iters_convergencia = i;
            break;
        }
        cout << "iteración " << i << endl;
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    write_times_to_file(time);
    write_iters_to_file(iters_convergencia);
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
    VectorXd x = jacobi_mat(entry.A, entry.b, atoi(argv[1]), entry.real_x, tolerance, write_errors);
    out_to_python(x);
}