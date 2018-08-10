#ifndef BEACHMAT_LOGICAL_MATRIX_H
#define BEACHMAT_LOGICAL_MATRIX_H

#include "LIN_matrix.h"
#include "LIN_output.h"

namespace beachmat {

/********************************************
 * Virtual base class for logical matrices. *
 ********************************************/

typedef lin_matrix<int, Rcpp::LogicalVector> logical_matrix;

/* Simple logical matrix */

typedef simple_lin_matrix<int, Rcpp::LogicalVector> simple_logical_matrix;

/* lgeMatrix */

typedef dense_lin_matrix<int, Rcpp::LogicalVector> dense_logical_matrix;

/* lgCMatrix */

typedef Csparse_lin_matrix<int, Rcpp::LogicalVector> Csparse_logical_matrix;

/* HDF5Matrix */

typedef HDF5_lin_matrix<int, Rcpp::LogicalVector, LGLSXP> HDF5_logical_matrix;

/* DelayedMatrix */

typedef delayed_lin_matrix<int, Rcpp::LogicalVector> delayed_logical_matrix;

/* Unknown matrix */

typedef unknown_lin_matrix<int, Rcpp::LogicalVector> unknown_logical_matrix;

/* Dispatcher */

std::unique_ptr<logical_matrix> create_logical_matrix(const Rcpp::RObject&);

/***************************************************
 * Virtual base class for output logical matrices. *
 ***************************************************/

typedef lin_output<int, Rcpp::LogicalVector> logical_output;

/* Simple output logical matrix */

typedef simple_lin_output<int, Rcpp::LogicalVector> simple_logical_output;

/* Sparse output logical matrix */

typedef sparse_lin_output<int, Rcpp::LogicalVector> sparse_logical_output;

/* HDF5 output logical matrix */

typedef HDF5_lin_output<int, Rcpp::LogicalVector, LGLSXP> HDF5_logical_output;

/* Output dispatchers */

std::unique_ptr<logical_output> create_logical_output(int, int, const output_param&);

}

#endif
