#pragma once // NOLINT

#include <vector>
#include <istream>

namespace prep {
class Matrix {
 private:
  double *element;

  size_t rows;
  size_t cols;

 public:
  explicit Matrix(size_t rows = 0, size_t cols = 0);
  explicit Matrix(std::istream& is);
  Matrix(const Matrix& rhs);
  ~Matrix();

  size_t getRows() const;
  size_t getCols() const;

  double operator()(size_t i, size_t j) const;
  double& operator()(size_t i, size_t j);

  bool operator==(const Matrix& rhs) const;
  bool operator!=(const Matrix& rhs) const;

  Matrix& operator=(const Matrix& rhs);

  friend
  void sumOrSub(int key, const Matrix& matrixSumOrSub, const Matrix& rhs);
  friend
  void sum(const Matrix& matrixSumOrSub, const Matrix& rhs);
  friend
  void sub(const Matrix& matrixSumOrSub, const Matrix& rhs);

  Matrix operator+(const Matrix& rhs) const;
  Matrix operator-(const Matrix& rhs) const;
  Matrix operator*(const Matrix& rhs) const;

  Matrix operator*(double val) const;

  friend
  Matrix operator*(double val, const Matrix& matrix);
  friend
  std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

  Matrix transp() const;
  double det() const;
  Matrix adj() const;
  Matrix inv() const;

  friend
  Matrix deleteRowAndColFromMatrix(const Matrix& matrix, size_t indRow, size_t indCol);
  friend
  double findDet(const Matrix& matrix, size_t n);
};

Matrix operator*(double val, const Matrix& matrix);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}  // namespace prep
