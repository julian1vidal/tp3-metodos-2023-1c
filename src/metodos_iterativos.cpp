#include "metodos_iterativos.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;


VectorXd jacobi_mat(MatrixXd A, VectorXd b){
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

    for (int i = 0; i < 50; i++){
        x = (T*x) + c;
    }

    return x;
}

VectorXd gs_mat(MatrixXd A, VectorXd b){
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

    for (int i = 0; i < 50; i++){
        x = (T*x) + c;
    }

    return x;
}

VectorXd jacobi_sum(MatrixXd A, VectorXd b){
    int cols = b.size();
    VectorXd x_anterior = VectorXd::Random(cols);
    VectorXd x = x_anterior;
    
    for (int k = 0; k < 50; k++){
        for (int i = 0; i < cols; i++){
            x[i] = (1/A(i, i)) * (b[i] - sumatoria_jacobi(A, x_anterior, i, cols));
        }
        x_anterior = x;
    }
    
    return x;
}


VectorXd gs_sum(MatrixXd A, VectorXd b){
    int cols = b.size();
    VectorXd x_anterior = VectorXd::Random(cols);
    VectorXd x = x_anterior;
    
    for (int k = 0; k < 50; k++){
        for (int i = 0; i < cols; i++){
            x[i] = (1/A(i, i)) * (b[i] - sumatoria_gs_x(A, x, i) - 
                                                    sumatoria_gs_x_anterior(A, x_anterior, i, cols));
        }
        x_anterior = x;
    }
    
    return x;
}











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