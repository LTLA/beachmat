#include "logical_matrix.h"

namespace beachmat {
    
/* Csparse logical input methods. */

template<>
int Csparse_matrix<int, Rcpp::LogicalVector>::get_empty() const { return 0; }

/* HDF5Matrix input methods. */

template<>
int HDF5_lin_matrix<int, Rcpp::LogicalVector, LGLSXP>::get(size_t r, size_t c) {
    int out;
    mat.extract_one(r, c, &out, H5::PredType::NATIVE_INT32);
    return out; 
}

/* DelayedMatrix input methods. */

const std::vector<std::string> allowed_seeds={"lgeMatrix", "lgCMatrix", "lgTMatrix", "lspMatrix", "RleMatrix"};

template<>
std::unique_ptr<logical_matrix> delayed_lin_matrix<int, Rcpp::LogicalVector>::generate_seed(Rcpp::RObject incoming) {
    Rcpp::RObject seed=extract_seed(incoming, allowed_seeds);
    if (seed!=R_NilValue) {
        return create_logical_matrix(seed);
    } else {
        return nullptr;
    }
} 

/* Sparse logical output methods. */

template<>
int Csparse_output<int, Rcpp::LogicalVector>::get_empty() const { return 0; }

/* HDF5 logical output methods. */

template<>
int HDF5_output<int, Rcpp::LogicalVector>::get_empty() const { return 0; }

template<>
Rcpp::RObject HDF5_output<int, Rcpp::LogicalVector>::get_firstval() { 
    int first;
    extract_one(0, 0, &first);
    return Rcpp::LogicalVector::create(first);
}

/* Dispatch definition */

std::unique_ptr<logical_matrix> create_logical_matrix(const Rcpp::RObject& incoming) { 
    if (incoming.isS4()) {
        std::string ctype=get_class(incoming);
        if (ctype=="lgeMatrix") { 
            return std::unique_ptr<logical_matrix>(new dense_logical_matrix(incoming));
        } else if (ctype=="lgCMatrix") { 
            return std::unique_ptr<logical_matrix>(new Csparse_logical_matrix(incoming));
        } else if (ctype=="lgTMatrix") {
            throw std::runtime_error("lgTMatrix not supported, convert to lgCMatrix");
        } else if (ctype=="lspMatrix") {
            return std::unique_ptr<logical_matrix>(new Psymm_logical_matrix(incoming));
        } else if (ctype=="HDF5Matrix") {
            return std::unique_ptr<logical_matrix>(new HDF5_logical_matrix(incoming));
        } else if (ctype=="RleMatrix") {
            return std::unique_ptr<logical_matrix>(new Rle_logical_matrix(incoming));
        } else if (ctype=="DelayedMatrix") { 
            return std::unique_ptr<logical_matrix>(new delayed_logical_matrix(incoming));
        }
        throw_custom_error("unsupported class '", ctype, "' for logical_matrix");
    } 
    return std::unique_ptr<logical_matrix>(new simple_logical_matrix(incoming));
}

/* Output dispatch definition */

std::unique_ptr<logical_output> create_logical_output(int nrow, int ncol, const output_param& param) {
    switch (param.get_mode()) {
        case SIMPLE:
            return std::unique_ptr<logical_output>(new simple_logical_output(nrow, ncol));
        case SPARSE:
            return std::unique_ptr<logical_output>(new sparse_logical_output(nrow, ncol));
        case HDF5:
            return std::unique_ptr<logical_output>(new HDF5_logical_output(nrow, ncol,
                        param.get_chunk_nrow(), param.get_chunk_ncol(), param.get_compression()));
        default:
            throw std::runtime_error("unsupported output mode for logical matrices");
    }
}

}
