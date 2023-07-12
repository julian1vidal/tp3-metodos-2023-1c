#include "metodos_iterativos.cpp"

VectorXd jacobi_sum(const MatrixXd& A, const VectorXd& b, int iter, const VectorXd& real_x, double tol, bool write_errors){
    auto start_time = chrono::high_resolution_clock::now();
    int cols = b.size();
    
    VectorXd x_anterior = VectorXd::Random(cols);
    //VectorXd x_anterior = VectorXd::Zero(cols);
    int iters_convergencia = iter;

    VectorXd x = x_anterior;


    VectorXd errors;
    for (int k = 0; k < iter; k++){
        for (int i = 0; i < cols; i++){
            x[i] = (1/A(i, i)) * (b[i] - sumatoria_jacobi(A, x_anterior, i, cols));
        }
        x_anterior = x;
        double err = (x - real_x).norm();
        if (write_errors){
            errors.conservativeResize(errors.size()+1);
            errors(errors.size()-1) = err;
        }
        if (tol != 0 && err < tol || not_a_number(x)){
            iters_convergencia = k;
            break;
        }
        cout << "iteración " << k << endl;
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
    VectorXd x = jacobi_sum(entry.A, entry.b, atoi(argv[1]), entry.real_x, tolerance, write_errors);
    out_to_python(x);
}