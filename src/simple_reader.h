#ifndef BEACHMAT_SIMPLE_READER_H
#define BEACHMAT_SIMPLE_READER_H

#include "beachmat.h"
#include "utils.h"
#include "dim_checker.h"

namespace beachmat {

/*** Class definition ***/

template<typename T, class V>
class simple_reader : public dim_checker {
public:    
    simple_reader(const Rcpp::RObject&);
    ~simple_reader();

    T get(size_t, size_t);

    template <class Iter>
    void get_row(size_t, Iter, size_t, size_t);

    template <class Iter>
    void get_col(size_t, Iter, size_t, size_t);

    typename V::iterator get_const_col(size_t, size_t, size_t);

    Rcpp::RObject yield() const;
    matrix_type get_matrix_type () const;
private:
    Rcpp::RObject original;
    V mat;
};

/*** Constructor definitions ***/

template<typename T, class V>
simple_reader<T, V>::simple_reader(const Rcpp::RObject& incoming) : original(incoming) { 
    if (!incoming.hasAttribute("dim")) { 
        throw std::runtime_error("matrix object should have 'dim' attribute"); 
    }
    this->fill_dims(incoming.attr("dim"));
    const size_t& NC=this->ncol; 

    if (incoming.sexp_type()!=mat.sexp_type()) { 
        throw_custom_error("matrix should be ", translate_type(mat.sexp_type()), "");
    }
    mat=incoming;
    if (mat.size()!=(this->nrow)*NC) {
        throw std::runtime_error("length of matrix is inconsistent with its dimensions"); 
    }
    return;
}

template<typename T, class V>
simple_reader<T, V>::~simple_reader () {}

/*** Getter methods ***/

template<typename T, class V>
T simple_reader<T, V>::get(size_t r, size_t c) { 
    check_oneargs(r, c);
    return mat[r + c*(this->nrow)]; 
}

template<typename T, class V>
template<class Iter>
void simple_reader<T, V>::get_row(size_t r, Iter out, size_t first, size_t last) {
    check_rowargs(r, first, last);
    const size_t& NR=this->nrow;
    auto src=mat.begin()+first*NR+r;
    for (size_t col=first; col<last; ++col, src+=NR, ++out) { (*out)=(*src); }
    return;
}

template<typename T, class V>
template<class Iter>
void simple_reader<T, V>::get_col(size_t c, Iter out, size_t first, size_t last) {
    check_colargs(c, first, last);
    auto src=mat.begin() + c*(this->nrow);
    std::copy(src+first, src+last, out);
    return;
}

template<typename T, class V>
typename V::iterator simple_reader<T, V>::get_const_col(size_t c, size_t first, size_t last) {
    return mat.begin() + first + c*(this->nrow);
}

template<typename T, class V>
Rcpp::RObject simple_reader<T, V>::yield() const {
    return original;
}

template<typename T, class V>
matrix_type simple_reader<T, V>::get_matrix_type() const {
    return SIMPLE;
}

}

#endif
