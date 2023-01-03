#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <typeinfo>

class S21Matrix {
   private:
    int rows_, cols_;
    double** matrix_;

    void NewMatrix();
    void CopyMatrix(const S21Matrix& other);
    void FreeMatrix();
    void CheckMatrix(const S21Matrix& other) const;
    void CheckMulMatrix(const S21Matrix& other) const;
    void CheckIndex(int i, int j) const;
    void CheckDeter() const;
    void CheckZero() const;
    void ColsOrRows(int value, bool flag);
    double MinorFinder() const;
    double Deter() const;
    void Slicer(int i_val, int j_val, S21Matrix& minor) const;

   public:
    S21Matrix();
    ~S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);

    bool EqMatrix(const S21Matrix& other) const;
    void SumMatrix(const S21Matrix& other) const;
    void SubMatrix(const S21Matrix& other) const;
    void MulNumber(const double num) const;
    void MulMatrix(const S21Matrix& other);
    S21Matrix InverseMatrix();
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant() const;

    // OVERLOADS
    S21Matrix operator+(const S21Matrix& other) const;
    S21Matrix operator-(const S21Matrix& other) const;
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(const double num) const;
    bool operator==(const S21Matrix& other) const;
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator=(S21Matrix&& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(const double num);
    double operator()(const int i, const int j) const;

    // Other methods..
    void SetVal(int i, int j, double val) const { matrix_[i][j] = val; }
    void SetRows(int rows);
    void SetCols(int cols);

    double** GetRef() const { return matrix_; }
    int GetRow() const { return rows_; }
    int GetCol() const { return cols_; }
    int GetVal(int i, int j) const { return matrix_[i][j]; }
    //-------------------------------------------------------------
    void ValGen() const;
    void PrintMatrix() const;
};

#endif  // SRC_S21_MATRIX_OOP_H_
