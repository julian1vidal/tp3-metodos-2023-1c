#ifndef METODOS_ITERATIVOS_H
#define METODOS_ITERATIVOS_H

#include <iostream>
#include <eigen3/Eigen/Dense>

Eigen::VectorXd jacobi_mat(Eigen::MatrixXd A, Eigen::VectorXd b);
Eigen::VectorXd gs_mat(Eigen::MatrixXd A, Eigen::VectorXd b);
Eigen::VectorXd jacobi_sum(Eigen::MatrixXd A, Eigen::VectorXd b);
Eigen::VectorXd gs_sum(Eigen::MatrixXd A, Eigen::VectorXd b);

double sumatoria_jacobi(Eigen::MatrixXd A, Eigen::VectorXd x_anterior, int i, int cols);
double sumatoria_gs_x(Eigen::MatrixXd A, Eigen::VectorXd x, int i);
double sumatoria_gs_x_anterior(Eigen::MatrixXd A, Eigen::VectorXd x_anterior, int i, int cols);

#endif
