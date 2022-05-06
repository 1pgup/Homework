#include <iomanip>
#include <iostream>
#include <cmath>
#include <limits>

#include "matrix.h"
#include "exceptions.h"

namespace prep {
    // Constructors
    Matrix:: Matrix(size_t rows, size_t cols): rows(rows), cols(cols) {
        element = new double[this->rows * this->cols];
        if (element == nullptr) {
            throw CouldNotAllocateMemory();
        }
    }

    Matrix:: Matrix(std::istream& is) {
        is >> this->rows >> this->cols;
        if (is.fail()) {
            throw InvalidMatrixStream();
        }

        this->element = new double[this->rows * this->cols];
        if (element == nullptr) {
            throw CouldNotAllocateMemory();
        }

        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                is >> *(this->element + i * this->cols + j);
                if (is.fail()) {
                    delete [] this->element;
                    throw InvalidMatrixStream();
                }
            }
        }
    }

    Matrix:: Matrix(const Matrix& rhs) {
        this->cols = rhs.getCols();
        this->rows = rhs.getRows();

        element = new double[rhs.getRows() * rhs.getCols()];
        if (element == nullptr) {
            throw CouldNotAllocateMemory();
        }

        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                *(element + i * this->cols + j) = rhs(i, j);
            }
        }
    }

    // Destructor
    Matrix::~Matrix() {
        delete[] element;
    }

    // Getting size of matrix
    size_t Matrix::getRows() const {
        return this->rows;
    }

    size_t Matrix::getCols() const {
        return this->cols;
    }

    // Getting element
    double Matrix::operator()(size_t i, size_t j) const {
        if (i + 1 > this->getRows() || j + 1> this->getCols()) {
            throw OutOfRange(i, j, *this);
        }

        return *(this->element + i * this->getCols() + j);
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i + 1 > this->getRows() || j + 1 > this->getCols()) {
            throw OutOfRange(i, j, *this);
        }

        return *(this->element + i * this->getCols() + j);
    }

    // Comparison
    bool Matrix::operator==(const Matrix& rhs) const {
        if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols()) {
            return false;
        }

        for (size_t i = 0; i < rhs.getRows(); i++) {
            for (size_t j = 0; j < rhs.getCols(); j++) {
                if (std::abs(*(this->element + i * this->getCols() + j) - rhs(i, j))
                    >= 1e-7) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols()) {
            return true;
        }

        for (size_t i = 0; i < rhs.getRows(); i++) {
            for (size_t j = 0; j < rhs.getCols(); j++) {
                if (std::abs(*(this->element + i * this->getCols() + j) - rhs(i, j))
                    >= 1e-7) {
                    return true;
                }
            }
        }
        return false;
    }

    // Matrix equation
    Matrix& Matrix::operator=(const Matrix& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete[] element;

        this->rows = rhs.getRows();
        this->cols = rhs.getCols();

        element = new double[rhs.getRows() * rhs.getCols()];
        if (element == nullptr) {
            throw CouldNotAllocateMemory();
        }

        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                *(element + i * this->cols + j) = rhs(i, j);
            }
        }
        return *this;
    }

    // Secondary functions for sum and sub opearators
    void sum(const Matrix& matrixSumOrSub, const Matrix& rhs) {
        for (size_t i = 0; i < matrixSumOrSub.getRows(); i++) {
            for (size_t j = 0; j < matrixSumOrSub.getCols(); j++) {
                *(matrixSumOrSub.element +i * matrixSumOrSub.getCols() + j) = *(matrixSumOrSub.element
                                                        + i * matrixSumOrSub.getCols()+ j) + rhs(i, j);
            }
        }
    }

    void sub(const Matrix& matrixSumOrSub, const Matrix& rhs) {
        for (size_t i = 0; i < matrixSumOrSub.getRows(); i++) {
            for (size_t j = 0; j < matrixSumOrSub.getCols(); j++) {
                *(matrixSumOrSub.element +i * matrixSumOrSub.getCols() + j) = *(matrixSumOrSub.element
                                                        + i * matrixSumOrSub.getCols() + j) - rhs(i, j);
            }
        }
    }

    void sumOrSub(void (*foo)(const Matrix&, const Matrix&),
                const Matrix& matrixSumOrSub,
                const Matrix& rhs) {
        if (foo != sum && foo != sub) {
            throw UnknownFunction();
        }
        foo(matrixSumOrSub, rhs);
    }

    // Summary
    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols()) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix matrixSum(*this);

        sumOrSub(sum, matrixSum, rhs);
        return matrixSum;
    }

    // Sublimation
    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (this->getRows() != rhs.getRows() || this->getCols() != rhs.getCols()) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix matrixSub(*this);

        sumOrSub(sub, matrixSub, rhs);
        return matrixSub;
    }

    // Matrix multiplication
    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (this->getCols() != rhs.getRows()) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix mulMatrix(this->getRows(), rhs.getCols());

        for (size_t i = 0; i < mulMatrix.getRows(); i++) {
            for (size_t j = 0; j < mulMatrix.getCols(); j++) {
                mulMatrix(i, j) = 0;
                for (size_t k = 0; k < this->getCols(); k++) {
                    mulMatrix(i, j) += *(this->element + i * this->getCols() + k) * rhs(k, j);
                }
            }
        }

        return mulMatrix;
    }

    // Scalar multiplication
    Matrix Matrix::operator*(double val) const {
        Matrix mulScalar(*this);

        for (size_t i = 0; i < mulScalar.getRows(); i++) {
            for (size_t j = 0; j < mulScalar.getCols(); j++) {
                mulScalar(i, j) *= val;
            }
        }

        return mulScalar;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix mulScalar(matrix);

        for (size_t i = 0; i < mulScalar.getRows(); i++) {
            for (size_t j = 0; j < mulScalar.getCols(); j++) {
                mulScalar(i, j) *= val;
            }
        }

        return mulScalar;
    }

    // Printing matrix
    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.rows << ' ' << matrix.getCols() << std::endl;

        for (size_t i = 0; i < matrix.getRows(); i++) {
            for (size_t j = 0; j < matrix.getCols(); j++) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10) << std::fixed
                   << matrix(i, j)
                   <<  " ";
            }
            os << std::endl;
        }
        os << std::endl;
        return os;
    }

    // Transposition
    Matrix Matrix::transp() const {
        Matrix transposition(this->getCols(), this->getRows());

        for (size_t i = 0; i < this->getRows(); i++) {
            for (size_t j = 0; j < this->getCols(); j++) {
                transposition(j, i) = *(this->element + i * this->getCols() + j);
            }
        }

        return transposition;
    }

    // Determinant
    double Matrix::det() const {
        if (this->getCols() != this->getRows()) {
            throw DimensionMismatch(*this);
        }

        return findDet(*this, this->getCols());
    }

    // Adjacency matrix
    Matrix Matrix::adj() const {
        if (this->getCols() != this->getRows()) {
            throw DimensionMismatch(*this);
        }

        Matrix adjMatrix(*this);

        for (size_t i = 0; i < this->getCols(); i++) {
            for (size_t j = 0; j < this->getCols(); j++) {
                adjMatrix(i, j) = pow(-1.0, i + j) * deleteRowAndColFromMatrix(*this, i, j).det();
            }
        }
        return adjMatrix.transp();
    }

    // Inversion matrix
    Matrix Matrix::inv() const {
        if (this->getCols() != this->getRows()) {
            throw DimensionMismatch(*this);
        }

        if (this->det() == 0.0) {
            throw SingularMatrix();
        }

        return this->adj() * (1.0 / this->det());;
    }

    // Secondary functions for Det
    Matrix deleteRowAndColFromMatrix(const Matrix& matrix, size_t indRow, size_t indCol) {
        Matrix temp_matrix(matrix.getRows() - 1, matrix.getCols() - 1);

        size_t ki = 0;

        for (size_t i = 0; i < matrix.getCols(); i++) {
            if (i != indRow) {
                for (size_t j = 0, kj = 0; j < matrix.getCols(); j++) {
                    if (j != indCol) {
                        temp_matrix(ki, kj) = matrix(i, j);
                        kj++;
                    }
                }
                ki++;
            }
        }
        return temp_matrix;
    }

    double findDet(const Matrix& matrix, size_t n) {
        if (n == 1) {
            return matrix(0, 0);
        }
        if (n == 2) {
            return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
        }

        double det = 0;
        for (size_t k = 0; k < n; k++) {
            Matrix newMatrix(n - 1, n - 1);
            for (size_t i = 1; i < n; i++) {
                size_t t = 0;
                for (size_t j = 0; j < n; j++) {
                    if (j != k) {
                        newMatrix(i - 1, t) = matrix(i, j);
                        t++;
                    }
                }
            }
            det += pow(-1.0, k + 2) * matrix(0, k) * findDet(newMatrix, n - 1);
        }
        return det;
    }
}  // namespace prep
