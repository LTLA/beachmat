# This tests the ability of the API to properly access numeric matrices of different types.
# library(testthat); library(beachtest); source("setup-fun.R"); source("test-numeric-input.R")

sFUN <- numeric_sFUN
dFUN <- numeric_dFUN
csFUN <- numeric_csFUN
tsFUN <- numeric_tsFUN
hFUN <- numeric_hFUN

#######################################################

set.seed(12345)
test_that("Simple numeric matrix input is okay", {
    check_read_all(sFUN, mode="numeric")
    check_read_all(sFUN, nr=5, nc=30, mode="numeric")
    check_read_all(sFUN, nr=30, nc=5, mode="numeric")

    check_read_slice(sFUN, mode="numeric")
    check_read_slice(sFUN, nr=5, nc=30, mode="numeric")
    check_read_slice(sFUN, nr=30, nc=5, mode="numeric")

    check_read_varslice(sFUN, mode="numeric")
    check_read_varslice(sFUN, nr=5, nc=30, mode="numeric")
    check_read_varslice(sFUN, nr=30, nc=5, mode="numeric")

    check_read_const(sFUN, mode="numeric")
    check_read_const(sFUN, nr=5, nc=30, mode="numeric")
    check_read_const(sFUN, nr=30, nc=5, mode="numeric")

    check_read_indexed(sFUN, mode="numeric")
    check_read_indexed(sFUN, nr=5, nc=30, mode="numeric")
    check_read_indexed(sFUN, nr=30, nc=5, mode="numeric")

    check_read_multi(sFUN, mode="numeric")
    check_read_multi(sFUN, nr=5, nc=30, mode="numeric")
    check_read_multi(sFUN, nr=30, nc=5, mode="numeric")

    check_read_type(sFUN, mode="numeric")
    check_read_class(sFUN(), mode="numeric", "simple")
    
    check_read_errors(sFUN, mode="numeric")
    check_read_all(sFUN, nr=0, nc=0, mode="numeric")
    check_read_all(sFUN, nr=10, nc=0, mode="numeric")
    check_read_all(sFUN, nr=0, nc=10, mode="numeric")
})

#######################################################

set.seed(13579)
test_that("Dense numeric matrix input is okay", {
    expect_s4_class(dFUN(), "dgeMatrix")

    check_read_all(dFUN, mode="numeric")
    check_read_all(dFUN, nr=5, nc=30, mode="numeric")
    check_read_all(dFUN, nr=30, nc=5, mode="numeric")

    check_read_slice(dFUN, mode="numeric")
    check_read_slice(dFUN, nr=5, nc=30, mode="numeric")
    check_read_slice(dFUN, nr=30, nc=5, mode="numeric")

    check_read_varslice(dFUN, mode="numeric")
    check_read_varslice(dFUN, nr=5, nc=30, mode="numeric")
    check_read_varslice(dFUN, nr=30, nc=5, mode="numeric")

    check_read_const(dFUN, mode="numeric")
    check_read_const(dFUN, nr=5, nc=30, mode="numeric")
    check_read_const(dFUN, nr=30, nc=5, mode="numeric")

    check_read_indexed(dFUN, mode="numeric")
    check_read_indexed(dFUN, nr=5, nc=30, mode="numeric")
    check_read_indexed(dFUN, nr=30, nc=5, mode="numeric")

    check_read_multi(dFUN, mode="numeric")
    check_read_multi(dFUN, nr=5, nc=30, mode="numeric")
    check_read_multi(dFUN, nr=30, nc=5, mode="numeric")

    check_read_type(dFUN, mode="numeric")
    check_read_class(dFUN(), mode="numeric", "dense")

    check_read_errors(dFUN, mode="numeric")
    check_read_all(dFUN, nr=0, nc=0, mode="numeric")
    check_read_all(dFUN, nr=10, nc=0, mode="numeric")
    check_read_all(dFUN, nr=0, nc=10, mode="numeric")
})  

#######################################################

set.seed(23456)
test_that("Sparse numeric matrix input is okay", {
    expect_s4_class(csFUN(), "dgCMatrix")

    check_read_all(csFUN, mode="numeric")
    check_read_all(csFUN, nr=5, nc=30, mode="numeric")
    check_read_all(csFUN, nr=30, nc=5, mode="numeric")

    check_read_slice(csFUN, mode="numeric")
    check_read_slice(csFUN, nr=5, nc=30, mode="numeric")
    check_read_slice(csFUN, nr=30, nc=5, mode="numeric")

    check_read_varslice(csFUN, mode="numeric")
    check_read_varslice(csFUN, nr=5, nc=30, mode="numeric")
    check_read_varslice(csFUN, nr=30, nc=5, mode="numeric")

    check_read_const(csFUN, mode="numeric")
    check_read_const(csFUN, nr=5, nc=30, mode="numeric")
    check_read_const(csFUN, nr=30, nc=5, mode="numeric")

    check_read_indexed(csFUN, mode="numeric")
    check_read_indexed(csFUN, nr=5, nc=30, mode="numeric")
    check_read_indexed(csFUN, nr=30, nc=5, mode="numeric")

    check_read_multi(csFUN, mode="numeric")
    check_read_multi(csFUN, nr=5, nc=30, mode="numeric")
    check_read_multi(csFUN, nr=30, nc=5, mode="numeric")

    check_read_type(csFUN, mode="numeric")
    check_read_class(csFUN(), mode="numeric", "sparse")

    check_read_errors(csFUN, mode="numeric")
    check_read_all(csFUN, nr=0, nc=0, mode="numeric")
    check_read_all(csFUN, nr=10, nc=0, mode="numeric")
    check_read_all(csFUN, nr=0, nc=10, mode="numeric")
})

#######################################################

set.seed(23456)
test_that("dgTMatrix (i.e., unknown) input is okay", {
    expect_s4_class(tsFUN(), "dgTMatrix")

    check_read_all(tsFUN, mode="numeric")
    check_read_all(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_all(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_slice(tsFUN, mode="numeric")
    check_read_slice(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_slice(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_varslice(tsFUN, mode="numeric")
    check_read_varslice(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_varslice(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_const(tsFUN, mode="numeric")
    check_read_const(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_const(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_indexed(tsFUN, mode="numeric")
    check_read_indexed(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_indexed(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_multi(tsFUN, mode="numeric")
    check_read_multi(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_multi(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_type(tsFUN, mode="numeric")
    check_read_class(tsFUN(), mode="numeric", "unknown")

    check_read_errors(tsFUN, mode="numeric")
    check_read_all(tsFUN, nr=0, nc=0, mode="numeric")
    check_read_all(tsFUN, nr=10, nc=0, mode="numeric")
    check_read_all(tsFUN, nr=0, nc=10, mode="numeric")
})

test_that("dgTMatrix input is okay with reduced block size", {
    old <- getDefaultBlockSize()
    setDefaultBlockSize(6*8)

    check_read_all(tsFUN, mode="numeric")
    check_read_all(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_all(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_slice(tsFUN, mode="numeric")
    check_read_slice(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_slice(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_varslice(tsFUN, mode="numeric")
    check_read_varslice(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_varslice(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_const(tsFUN, mode="numeric")
    check_read_const(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_const(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_indexed(tsFUN, mode="numeric")
    check_read_indexed(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_indexed(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_multi(tsFUN, mode="numeric")
    check_read_multi(tsFUN, nr=5, nc=30, mode="numeric")
    check_read_multi(tsFUN, nr=30, nc=5, mode="numeric")

    check_read_type(tsFUN, mode="numeric")
    check_read_class(tsFUN(), mode="numeric", "unknown")

    check_read_errors(tsFUN, mode="numeric")
    check_read_all(tsFUN, nr=0, nc=0, mode="numeric")
    check_read_all(tsFUN, nr=10, nc=0, mode="numeric")
    check_read_all(tsFUN, nr=0, nc=10, mode="numeric")
             
    setDefaultBlockSize(old)
})

#######################################################

set.seed(34567)
test_that("HDF5 numeric matrix input is okay", {
    expect_s4_class(hFUN(), "HDF5Matrix")

    check_read_all(hFUN, mode="numeric")
    check_read_all(hFUN, nr=5, nc=30, mode="numeric")
    check_read_all(hFUN, nr=30, nc=5, mode="numeric")

    check_read_slice(hFUN, mode="numeric")
    check_read_slice(hFUN, nr=5, nc=30, mode="numeric")
    check_read_slice(hFUN, nr=30, nc=5, mode="numeric")

    check_read_varslice(hFUN, mode="numeric")
    check_read_varslice(hFUN, nr=5, nc=30, mode="numeric")
    check_read_varslice(hFUN, nr=30, nc=5, mode="numeric")

    check_read_const(hFUN, mode="numeric")
    check_read_const(hFUN, nr=5, nc=30, mode="numeric")
    check_read_const(hFUN, nr=30, nc=5, mode="numeric")

    check_read_indexed(hFUN, mode="numeric")
    check_read_indexed(hFUN, nr=5, nc=30, mode="numeric")
    check_read_indexed(hFUN, nr=30, nc=5, mode="numeric")

    check_read_multi(hFUN, mode="numeric")
    check_read_multi(hFUN, nr=5, nc=30, mode="numeric")
    check_read_multi(hFUN, nr=30, nc=5, mode="numeric")

    check_read_type(hFUN, mode="numeric")
    check_read_class(hFUN(), mode="numeric", "HDF5")

    check_read_errors(hFUN, mode="numeric")
    check_read_all(hFUN, nr=0, nc=0, mode="numeric")
    check_read_all(hFUN, nr=10, nc=0, mode="numeric")
    check_read_all(hFUN, nr=0, nc=10, mode="numeric")
})

#######################################################

set.seed(981347)
test_that("Delayed numeric matrix input is okay", {
    delfuns <- delayed_funs(sFUN, DELAYED_FUN=function(x) { x + runif(nrow(x)) })

    for (FUN in delfuns) {
        NR <- 10 + sample(10, 1)
        NC <- 10 + sample(10, 1)
        expect_s4_class(FUN(NR, NC), "DelayedMatrix")

        check_read_all(FUN, NR, NC, mode="numeric")

        check_read_slice(FUN, NR, NC, mode="numeric")

        check_read_varslice(FUN, NR, NC, mode="numeric")

        check_read_const(FUN, NR, NC, mode="numeric")

        check_read_indexed(FUN, NR, NC, mode="numeric")

        check_read_multi(FUN, NR, NC, mode="numeric")

        check_read_type(FUN, NR, NC, mode="numeric")
        check_read_class(FUN(), mode="numeric", "delayed")

        check_read_errors(FUN, NR, NC, mode="numeric")
        check_read_all(FUN, nr=0, nc=0, mode="numeric")
        check_read_all(FUN, nr=10, nc=0, mode="numeric")
        check_read_all(FUN, nr=0, nc=10, mode="numeric")
    }

    # Proper type check upon coercion!
    expect_identical("logical", .Call("get_type", hFUN() > 0, PACKAGE="beachtest"))
})