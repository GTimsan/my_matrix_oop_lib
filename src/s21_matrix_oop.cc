#include "s21_matrix_oop.h"

//            ##############################  PUBLIC FUNCTIONS #################################
// Конструктор дефолт
S21Matrix::S21Matrix() : rows_(3), cols_(3) { NewMatrix(); }

// Деструктор
S21Matrix::~S21Matrix() { FreeMatrix(); }

// Конструктор с двумя аргументами
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) { NewMatrix(); }

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other) { CopyMatrix(other); }

// Конструктор перемещения
S21Matrix::S21Matrix(S21Matrix&& other) : rows_(0), cols_(0), matrix_(nullptr) { *this = std::move(other); }

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
    bool flag = true;
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        flag = false;
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (matrix_[i][j] != other.matrix_[i][j]) {
                    flag = false;
                }
            }
        }
    }
    return flag;
}

void S21Matrix::SumMatrix(const S21Matrix& other) const {
    CheckMatrix(other);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) const {
    CheckMatrix(other);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double num) const {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    CheckMulMatrix(other);
    S21Matrix res(rows_, other.cols_);
    for (int i = 0; i < res.rows_; i++) {
        for (int j = 0; j < res.cols_; j++) {
            res.matrix_[i][j] = 0;
            for (int k = 0; k < cols_; k++) {
                res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    FreeMatrix();
    CopyMatrix(res);
}

double S21Matrix::Determinant() const {
    double result = 0;
    CheckDeter();
    if (rows_ == 1 && cols_ == 1) {
        result = matrix_[0][0];
    } else {
        result = Deter();
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() {
    CheckDeter();
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            S21Matrix m(rows_ - 1, cols_ - 1);
            Slicer(i, j, m);
            if (m.rows_ >= 2 && m.cols_ >= 2) {
                result.matrix_[i][j] = m.Deter() * std::pow(-1, i + j);
            } else if (m.rows_ == 1 && m.cols_ == 1) {
                result.matrix_[i][j] = m.matrix_[0][0] * std::pow(-1, i + j);
            }
        }
    }
    *this = std::move(result);
    return *this;
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            result.matrix_[i][j] = matrix_[j][i];
        }
    }
    *this = std::move(result);
    return *this;
}

S21Matrix S21Matrix::InverseMatrix() {
    double res = Determinant();
    if (res == 0) {
        throw std::runtime_error("Error:  Определитель равен 0");
    }
    CalcComplements();
    Transpose();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] / res;
        }
    }
    return *this;
}

//            ##############################  OVERLOADS  #################################

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
    S21Matrix tmp(*this);
    tmp.SumMatrix(other);
    return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
    S21Matrix tmp(*this);
    tmp.SubMatrix(other);
    return tmp;
}

S21Matrix S21Matrix::operator*(const double num) const {
    S21Matrix tmp(*this);
    tmp.MulNumber(num);
    return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix tmp(*this);
    tmp.MulMatrix(other);
    return tmp;
}

bool S21Matrix::operator==(const S21Matrix& other) const { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    FreeMatrix();
    CopyMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
    MulNumber(num);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
}

double S21Matrix::operator()(int i, int j) const {
    CheckIndex(i, j);
    return GetVal(i, j);
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
    if (this != &other) {
        FreeMatrix();
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_ = other.matrix_;
        other.rows_ = 0;
        other.cols_ = 0;
        other.matrix_ = nullptr;
    }
    return *this;
}

void S21Matrix::SetRows(int rows) { ColsOrRows(rows, 1); }

void S21Matrix::SetCols(int cols) { ColsOrRows(cols, 0); }

//            ##############################  PRIVATE FUNCTIONS #################################

void S21Matrix::ColsOrRows(int value, bool flag) {
    int size_rows, value_rows, size_cols, value_cols;
    size_rows = value_rows = rows_;
    size_cols = value_cols = cols_;
    if (flag == true) {
        if (value < rows_) {
            size_rows = value;
        }
        value_rows = value;
    } else {
        if (value < cols_) {
            size_cols = value;
        }
        value_cols = value;
    }
    S21Matrix tmp(value_rows, value_cols);
    tmp.CheckZero();
    for (int i = 0; i < size_rows; i++) {
        for (int j = 0; j < size_cols; j++) {
            tmp.matrix_[i][j] = matrix_[i][j];
        }
    }
    *this = tmp;
}

double S21Matrix::Deter() const {
    double val = 0;
    if (rows_ == 2 && cols_ == 2) {
        val = MinorFinder();
    } else {
        for (int j = 0; j < cols_; j++) {
            S21Matrix tmp(rows_ - 1, cols_ - 1);
            Slicer(0, j, tmp);
            int x = j % 2 == 0 ? 1 : -1;
            if (tmp.rows_ == 2) {
                val += x * matrix_[0][j] * tmp.MinorFinder();
            } else {
                val += x * matrix_[0][j] * tmp.Deter();
            }
        }
    }
    return val;
}

void S21Matrix::Slicer(int i_val, int j_val, S21Matrix& minor) const {
    int a = 0, b = 0;
    for (int i = 0; i < rows_; i++) {
        if (i_val != i) {
            for (int j = 0; j < cols_; j++) {
                if (j_val != j) {
                    minor.matrix_[a][b] = matrix_[i][j];
                    b++;
                }
            }
            b = 0;
            a++;
        }
    }
}

double S21Matrix::MinorFinder() const {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
}

void S21Matrix::NewMatrix() {
    matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]();
    }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    NewMatrix();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

void S21Matrix::FreeMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }
}

void S21Matrix::CheckZero() const {
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::runtime_error("Error:  Хреновая матрица rows или cols <= 0");
    }
}

void S21Matrix::CheckMatrix(const S21Matrix& other) const {
    CheckZero();
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::runtime_error("Error:  Кривые матрицы");
    }
}

void S21Matrix::CheckMulMatrix(const S21Matrix& other) const {
    CheckZero();
    other.CheckZero();
    if (cols_ != other.rows_) {
        throw std::runtime_error("Error:   Количество столбцев совпадает с количеством рядов");
    }
}

void S21Matrix::CheckIndex(int i, int j) const {
    if (cols_ - 1 < j || rows_ - 1 < i) {
        throw std::runtime_error("Error:  Индекс выходит за границы матрицы");
    }
}

void S21Matrix::CheckDeter() const {
    CheckZero();
    if (cols_ != rows_) {
        throw std::runtime_error("Error:   Нужна квадратная матрица");
    }
}

//            ##############################  OTHER FUNCTIONS #################################

void S21Matrix::PrintMatrix() const {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void S21Matrix::ValGen() const {
    double val = 1;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = val;
            val++;
        }
    }
}
