#include "utils.h"

namespace beachmat {

std::string make_to_string(const Rcpp::RObject& str) {
    Rcpp::StringVector as_str(str);
    if (as_str.size()!=1) { 
        throw std::runtime_error("input RObject should contain a single string");
    }
    return Rcpp::as<std::string>(as_str[0]);
}

void throw_custom_error(const std::string& left, const std::string& classname, const std::string& right) {
    std::stringstream err;
    err << left << classname << right;
    throw std::runtime_error(err.str().c_str());
}

/* Class checks. */

std::string get_class(const Rcpp::RObject& incoming) {
    if (!incoming.isObject()) {
        throw std::runtime_error("object has no class attribute");
    }
    return make_to_string(incoming.attr("class"));
}

Rcpp::RObject get_safe_slot(const Rcpp::RObject& incoming, const std::string& slotname) {
    if (!incoming.hasSlot(slotname)) { 
        std::stringstream err;
        err << "no '" << slotname << "' slot in the " << get_class(incoming) << " object";
        throw std::runtime_error(err.str().c_str()); 
    }
    return incoming.slot(slotname);
}

std::string check_Matrix_class (const Rcpp::RObject& mat, const std::string& expected) {
    std::string mattype=get_class(mat);
    if (!mat.isS4() || mattype.empty() || mattype.substr(1)!=expected) {
        throw_custom_error("matrix should be a *", expected, " object");
    }
    return mattype;
}


/* Type checks */

std::string translate_type(int sexp_type) {
    std::string should_be;
    switch(sexp_type) {
        case REALSXP:
            should_be="double";
            break;
        case INTSXP:
            should_be="integer";
            break;
        case LGLSXP:
            should_be="logical";
            break;
        case STRSXP:
            should_be="character";
            break;
        default:
            std::stringstream err;
            err << "unsupported sexptype '" << sexp_type << "'";
            throw std::runtime_error(err.str().c_str());
    }
    return should_be;
}

int reverse_translate_type (const std::string& curtype) {
    if (curtype=="logical") {
        return LGLSXP;
    } else if (curtype=="character") {
        return STRSXP;
    } else if (curtype=="integer") {
        return INTSXP;
    } else if (curtype=="double") {
        return REALSXP;
    }
    std::stringstream err;
    err << "unsupported type'" << curtype << "'";
    throw std::runtime_error(err.str().c_str());
}

int find_sexp_type (const Rcpp::RObject& incoming) {
    if (incoming.isObject()) {
        const std::string classname=get_class(incoming);
        if (classname=="DelayedMatrix") {
            Rcpp::Environment delayenv("package:DelayedArray");
            Rcpp::Function typefun=delayenv["type"];
            std::string curtype=Rcpp::as<std::string>(typefun(incoming));
            return reverse_translate_type(curtype);
            
        } else if (classname=="HDF5Matrix") {
            Rcpp::RObject h5seed=get_safe_slot(incoming, "seed");
            Rcpp::RObject first_val=get_safe_slot(h5seed, "first_val");
            return first_val.sexp_type();

        } else if (classname=="RleMatrix") {
            Rcpp::RObject rleseed=get_safe_slot(incoming, "seed");
            std::string rclass=get_class(rleseed);
            if (rclass=="SolidRleArraySeed") {
                Rcpp::RObject rle=get_safe_slot(rleseed, "rle");
                return get_safe_slot(rle, "values").sexp_type();
            } else if (rclass=="ChunkedRleArraySeed") {
                std::string curtype=Rcpp::as<std::string>(get_safe_slot(rleseed, "type"));
                return reverse_translate_type(curtype);               
            }

        } else if (classname.length()==9 && classname.substr(3)=="Matrix") {
            if (classname[0]=='d') {
                return REALSXP;
            } else if (classname[0]=='l') {
                return LGLSXP;
            }

        }
        throw_custom_error("unknown SEXP type for ", classname, " object");
    }
    return incoming.sexp_type();
}

}
