# This tests the LIN block reader.
# library(testthat); library(morebeachtests); source("setup.R"); source("test-dense-column.R")

set.seed(10000)

test_that("dense matrix column reads are done correctly", {
    for (mats in list(
            SPAWN(100, 20, mode=0),
            SPAWN(10, 200, mode=1),
            SPAWN(50, 50, mode=2)
        )
    ) {
        reference <- mats[[1]]
        nc <- ncol(reference)
        for (M in mats) {

            for (perm in list(
                    sample(nc),
                    seq_len(nc),
                    rev(seq_len(nc))
                )
            ) {

                for (j in 0:2) {
                    out <- morebeachtests:::get_column(M, perm - 1L, j)
                    CHECK_IDENTITY(reference, out, mode=j)
                }
            }
        }
    }
})

test_that("dense matrix column reads are done correctly with slices", {
    SLICE <- function(x, order, starts, ends) {
        for (o in order) {
            y <- x[starts[o]:ends[o],o]
            x[,o] <- vector(typeof(y), 1L)
            x[starts[o]:ends[o],o] <- y 
        }
        x
    }

    for (mats in list(
            SPAWN(100, 20, mode=0),
            SPAWN(10, 200, mode=1),
            SPAWN(50, 50, mode=2)
        )
    ) {
        reference <- mats[[1]]
        nr <- nrow(reference)
        nc <- ncol(reference)
        for (M in mats) {

            for (perm in list(
                    sample(nc),
                    seq_len(nc),
                    rev(seq_len(nc))
                )
            ) {
                x1 <- sample(nr, nc, replace=TRUE)
                x2 <- sample(nr, nc, replace=TRUE)
                starts <- pmin(x1, x2)
                ends <- pmax(x1, x2)
                ref <- SLICE(reference, perm, starts, ends)

                for (j in 0:2) {
                    mat <- morebeachtests:::get_column_slice(M, perm - 1L, starts - 1L, ends, j)
                    CHECK_IDENTITY(ref, mat, mode=j)
                }
            }
        }
    }
})

test_that("dense matrix column reads are correctly bounded", {
    mats <- SPAWN(100, 20, mode=2)

    for (M in mats) {
        expect_error(morebeachtests:::get_column(M, 1000L, mode=2L), 
            "column index out of range")

        expect_error(morebeachtests:::get_column_slice(M, 1000L, 0, 1, mode=2L),
            "column index out of range")

        expect_error(morebeachtests:::get_column_slice(M, 0L, -1, 1, mode=2L),
            "row start index is greater than row end index")

        expect_error(morebeachtests:::get_column_slice(M, 0L, 0, 1000, mode=2L),
            "row end index out of range")
    }
})
