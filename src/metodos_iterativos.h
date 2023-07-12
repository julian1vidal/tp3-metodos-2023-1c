#ifndef METODOS_ITERATIVOS_H
#define METODOS_ITERATIVOS_H

#include "Eigen/Dense"

Eigen::VectorXd jacobi_mat(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, int iter, const Eigen::VectorXd& real_x, double tol, bool write_errors);
Eigen::VectorXd gs_mat(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, int iter, const Eigen::VectorXd& real_x, double tol, bool write_errors);
Eigen::VectorXd jacobi_sum(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, int iter, const Eigen::VectorXd& real_x, double tol, bool write_errors);
Eigen::VectorXd gs_sum(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, int iter, const Eigen::VectorXd& real_x, double tol, bool write_errors);

double sumatoria_jacobi(const Eigen::MatrixXd& A, const Eigen::VectorXd& x_anterior, int i, int cols);
double sumatoria_gs_x(const Eigen::MatrixXd& A, const Eigen::VectorXd& x, int i);
double sumatoria_gs_x_anterior(const Eigen::MatrixXd& A, const Eigen::VectorXd& x_anterior, int i, int cols);

#endif
