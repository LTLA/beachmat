#include "beachmat3/beachmat.h"

template <class V, typename T = typename V::stored_type>
Rcpp::RObject get_sparse_column_slice0(Rcpp::RObject mat, Rcpp::IntegerVector order, 
    Rcpp::IntegerVector starts, Rcpp::IntegerVector ends) 
{
    auto ptr = beachmat::read_lin_sparse_block(mat);
    std::vector<int> work_i(ptr->get_nrow());
    std::vector<T> work_x(ptr->get_nrow());
    std::map<std::pair<int, int>, T> store;

    for (auto o : order) {
        int curstart = starts[o];
        int curend = ends[o];

        auto stuff = ptr->get_col(o, work_x.data(), work_i.data(), curstart, curend);
        for (size_t j = 0; j < stuff.n; ++j) {
            store[std::make_pair(o, stuff.i[j])] = stuff.x[j];
        }
    }

    return beachmat::as_gCMatrix<V>(ptr->get_nrow(), ptr->get_ncol(), store); 
}

// [[Rcpp::export(rng=false)]]
Rcpp::RObject get_sparse_column_slice(Rcpp::RObject mat, Rcpp::IntegerVector order, 
    Rcpp::IntegerVector starts, Rcpp::IntegerVector ends, int mode) 
{
    if (mode == 0) {
        return get_sparse_column_slice0<Rcpp::LogicalVector>(mat, order, starts, ends);
    } else {
        return get_sparse_column_slice0<Rcpp::NumericVector>(mat, order, starts, ends);
    }
}

template <class V, typename T = typename V::stored_type>
Rcpp::RObject get_sparse_column0(Rcpp::RObject mat, Rcpp::IntegerVector order) {
    auto ptr = beachmat::read_lin_sparse_block(mat);
    std::map<std::pair<int, int>, T> store;
    std::vector<int> work_i(ptr->get_nrow());
    std::vector<T> work_x(ptr->get_nrow());

    for (auto o : order) {
        auto stuff = ptr->get_col(o, work_x.data(), work_i.data());
        for (size_t j = 0; j < stuff.n; ++j) {
            store[std::make_pair(o, stuff.i[j])] = stuff.x[j];
        }
    }

    return beachmat::as_gCMatrix<V>(ptr->get_nrow(), ptr->get_ncol(), store); 
}

// [[Rcpp::export(rng=false)]]
Rcpp::RObject get_sparse_column(Rcpp::RObject mat, Rcpp::IntegerVector order, int mode) {
    if (mode == 0) {
        return get_sparse_column0<Rcpp::LogicalVector>(mat, order);
    } else {
        return get_sparse_column0<Rcpp::NumericVector>(mat, order);
    }
}
