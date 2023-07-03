#ifndef METODOS_ITERATIVOS_H
#define METODOS_ITERATIVOS_H

#include "Eigen/Dense"

Eigen::VectorXd jacobi_mat(Eigen::MatrixXd A, Eigen::VectorXd b, int iter, Eigen::VectorXd real_x, double tol, bool write_errors);
Eigen::VectorXd gs_mat(Eigen::MatrixXd A, Eigen::VectorXd b, int iter, Eigen::VectorXd real_x, double tol, bool write_errors);
Eigen::VectorXd jacobi_sum(Eigen::MatrixXd A, Eigen::VectorXd b, int iter, Eigen::VectorXd real_x, double tol, bool write_errors);
Eigen::VectorXd gs_sum(Eigen::MatrixXd A, Eigen::VectorXd b, int iter, Eigen::VectorXd real_x, double tol, bool write_errors);

double sumatoria_jacobi(Eigen::MatrixXd A, Eigen::VectorXd x_anterior, int i, int cols);
double sumatoria_gs_x(Eigen::MatrixXd A, Eigen::VectorXd x, int i);
double sumatoria_gs_x_anterior(Eigen::MatrixXd A, Eigen::VectorXd x_anterior, int i, int cols);

#endif
