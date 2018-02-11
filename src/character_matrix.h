#ifndef BEACHMAT_CHARACTER_MATRIX_H
#define BEACHMAT_CHARACTER_MATRIX_H

#include "Input_matrix.h"

namespace beachmat { 

/* Virtual base class for character matrices. */

class character_matrix {
public:    
    character_matrix();
    virtual ~character_matrix();
    
    virtual size_t get_nrow() const=0;
    virtual size_t get_ncol() const=0;
    
    void get_row(size_t, Rcpp::StringVector::iterator); 
    virtual void get_row(size_t, Rcpp::StringVector::iterator, size_t, size_t)=0;

    void get_col(size_t, Rcpp::StringVector::iterator);
    virtual void get_col(size_t, Rcpp::StringVector::iterator, size_t, size_t)=0;

    virtual Rcpp::String get(size_t, size_t)=0;

    Rcpp::StringVector::iterator get_const_col(size_t, Rcpp::StringVector::iterator);
    virtual Rcpp::StringVector::iterator get_const_col(size_t, Rcpp::StringVector::iterator, size_t, size_t);

    typedef std::tuple<size_t, Rcpp::IntegerVector::iterator, Rcpp::StringVector::iterator> const_col_indexed_info;
    const_col_indexed_info get_const_col_indexed(size_t, Rcpp::StringVector::iterator);
    virtual const_col_indexed_info get_const_col_indexed(size_t, Rcpp::StringVector::iterator, size_t, size_t);

    virtual std::unique_ptr<character_matrix> clone() const=0;

    virtual Rcpp::RObject yield () const=0;
    virtual matrix_type get_matrix_type() const=0;

private:
    Rcpp::IntegerVector indices; // needed for get_const_col_indexed for non-sparse matrices.
};

/* Simple character matrix */

class simple_character_matrix : public character_matrix {
public:
    simple_character_matrix(const Rcpp::RObject& incoming);
    ~simple_character_matrix();
  
    size_t get_nrow() const;
    size_t get_ncol() const;
 
    void get_row(size_t, Rcpp::StringVector::iterator, size_t, size_t);
    void get_col(size_t, Rcpp::StringVector::iterator, size_t, size_t);

    Rcpp::String get(size_t, size_t);

    Rcpp::StringVector::iterator get_const_col(size_t, Rcpp::StringVector::iterator, size_t, size_t);

    std::unique_ptr<character_matrix> clone() const;
   
    Rcpp::RObject yield () const;
    matrix_type get_matrix_type() const;
private:
    simple_matrix<Rcpp::String, Rcpp::StringVector> mat;
};

/* RLE character matrix */

class Rle_character_matrix : public character_matrix {
public:
    Rle_character_matrix(const Rcpp::RObject& incoming);
    ~Rle_character_matrix();
  
    size_t get_nrow() const;
    size_t get_ncol() const;
 
    void get_row(size_t, Rcpp::StringVector::iterator, size_t, size_t);
    void get_col(size_t, Rcpp::StringVector::iterator, size_t, size_t);

    Rcpp::String get(size_t, size_t);

    std::unique_ptr<character_matrix> clone() const;

    Rcpp::RObject yield () const;
    matrix_type get_matrix_type() const;
private:
    Rle_matrix<Rcpp::String, Rcpp::StringVector> mat;
};

/* HDF5Matrix */

class HDF5_character_matrix : public character_matrix {
public:    
    HDF5_character_matrix(const Rcpp::RObject&);
    ~HDF5_character_matrix();

    size_t get_nrow() const;
    size_t get_ncol() const;
 
    void get_row(size_t, Rcpp::StringVector::iterator, size_t, size_t);
    void get_col(size_t, Rcpp::StringVector::iterator, size_t, size_t);

    Rcpp::String get(size_t, size_t);

    std::unique_ptr<character_matrix> clone() const;

    Rcpp::RObject yield () const;
    matrix_type get_matrix_type() const;
protected:
    HDF5_matrix<char, STRSXP> mat; 
    H5::DataType str_type;

    size_t bufsize;
    std::vector<char> row_buf, col_buf, one_buf;
};

/* DelayedMatrix */

class delayed_character_matrix : public character_matrix {
public:
    delayed_character_matrix(const Rcpp::RObject&);
    ~delayed_character_matrix();
    delayed_character_matrix(const delayed_character_matrix&);
    delayed_character_matrix& operator=(const delayed_character_matrix&);
    delayed_character_matrix(delayed_character_matrix&&)=default;
    delayed_character_matrix& operator=(delayed_character_matrix&&)=default;

    size_t get_nrow() const;
    size_t get_ncol() const;
 
    void get_row(size_t, Rcpp::StringVector::iterator, size_t, size_t);
    void get_col(size_t, Rcpp::StringVector::iterator, size_t, size_t);

    Rcpp::String get(size_t, size_t);

    std::unique_ptr<character_matrix> clone() const;

    Rcpp::RObject yield () const;
    matrix_type get_matrix_type() const;
private:
    Rcpp::RObject original;
    std::unique_ptr<character_matrix> seed_ptr;
    delayed_coord_transformer<Rcpp::String, Rcpp::StringVector> transformer;
    static std::unique_ptr<character_matrix> generate_seed(Rcpp::RObject);
};

/* Dispatcher */

std::unique_ptr<character_matrix> create_character_matrix(const Rcpp::RObject&);

}

/* Collected output definitions, so people only have to do #include "character_matrix.h" */

#include "character_output.h"

#endif
