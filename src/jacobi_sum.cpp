#include "metodos_iterativos.cpp"

VectorXd jacobi_sum(MatrixXd A, VectorXd b, int iter){
    int cols = b.size();
    VectorXd x_anterior = VectorXd::Random(cols);
    VectorXd x = x_anterior;
    
    for (int k = 0; k < iter; k++){
        for (int i = 0; i < cols; i++){
            x[i] = (1/A(i, i)) * (b[i] - sumatoria_jacobi(A, x_anterior, i, cols));
        }
        x_anterior = x;
    }
    
    return x;
}

int main(int argc, char** argv) {
    entrada entry = matrix_reader(argc, argv);
    VectorXd x = jacobi_sum(entry.A, entry.b, atoi(argv[1]));
    cout << argc << endl;
    out_to_python(x);
}