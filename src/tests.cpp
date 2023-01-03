#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(S21Matrix, standart_methods) {
    S21Matrix m1;
    EXPECT_EQ(3, m1.GetRow());
    EXPECT_EQ(3, m1.GetCol());

    S21Matrix m2(9, 8);
    EXPECT_EQ(9, m2.GetRow());
    EXPECT_EQ(8, m2.GetCol());

    S21Matrix* m3 = new S21Matrix(5, 5);
    EXPECT_EQ(5, m3->GetRow());
    EXPECT_EQ(5, m3->GetCol());
    delete m3;

    S21Matrix m4;
    m2.ValGen();
    m1.ValGen();
    m4 = m2;
    m2 = m1;
    EXPECT_EQ(9, m4.GetRow());
    EXPECT_EQ(8, m4.GetCol());
    EXPECT_EQ(3, m1.GetRow());
    EXPECT_EQ(3, m1.GetCol());
}

TEST(S21Matrix, EqMatrix) {
    S21Matrix m1(7, 9);
    S21Matrix m2(7, 9);
    S21Matrix m3(7, 8);
    EXPECT_EQ(0, m1.EqMatrix(m3));
    m1.ValGen();
    m2.ValGen();
    EXPECT_EQ(1, m1.EqMatrix(m2));
    m1.SetVal(4, 4, 33);
    EXPECT_EQ(0, m1.EqMatrix(m2));
    m3 = m1;
    EXPECT_EQ(1, m1.EqMatrix(m3));
    EXPECT_EQ(1, m3.EqMatrix(m1));
}

TEST(S21Matrix, SumMatrix) {
    S21Matrix m1(4, 5);
    S21Matrix m2(4, 5);
    // S21Matrix m3(7, 8);
    m1.ValGen();
    m2.ValGen();
    m1.SumMatrix(m2);
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(n++ * 2, m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, SubMatrix) {
    S21Matrix m1(4, 5);
    S21Matrix m2(4, 5);
    // S21Matrix m3(7, 8);
    m1.ValGen();
    m2.ValGen();
    m1.SubMatrix(m2);
    // int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(0, m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, MulNumber) {
    S21Matrix m1(4, 5);
    // S21Matrix m2(4, 5);
    // S21Matrix m3(7, 8);
    m1.ValGen();
    double num = 3;
    // m2.ValGen();
    m1.MulNumber(num);
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(n++ * num, m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, MulMatrix) {
    S21Matrix m1(3, 2);
    m1.SetVal(0, 0, 1);
    m1.SetVal(0, 1, 4);
    m1.SetVal(1, 0, 2);
    m1.SetVal(1, 1, 5);
    m1.SetVal(2, 0, 3);
    m1.SetVal(2, 1, 6);
    S21Matrix m2(2, 3);
    m2.SetVal(0, 0, 1);
    m2.SetVal(0, 1, -1);
    m2.SetVal(0, 2, 1);
    m2.SetVal(1, 0, 2);
    m2.SetVal(1, 1, 3);
    m2.SetVal(1, 2, 4);
    S21Matrix m3(3, 3);
    m3.SetVal(0, 0, 9);
    m3.SetVal(0, 1, 11);
    m3.SetVal(0, 2, 17);
    m3.SetVal(1, 0, 12);
    m3.SetVal(1, 1, 13);
    m3.SetVal(1, 2, 22);
    m3.SetVal(2, 0, 15);
    m3.SetVal(2, 1, 15);
    m3.SetVal(2, 2, 27);

    m1.MulMatrix(m2);
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(m3.GetVal(i, j), m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, Determinant) {
    S21Matrix m1(4, 4);
    m1.ValGen();
    S21Matrix m2(3, 3);
    m2.ValGen();
    EXPECT_EQ(0, m1.Determinant());
    EXPECT_EQ(0, m2.Determinant());
}

TEST(S21Matrix, CalcComplements) {
    S21Matrix m1(3, 3);
    m1.SetVal(0, 0, 1);
    m1.SetVal(0, 1, 2);
    m1.SetVal(0, 2, 3);
    m1.SetVal(1, 0, 0);
    m1.SetVal(1, 1, 4);
    m1.SetVal(1, 2, 2);
    m1.SetVal(2, 0, 5);
    m1.SetVal(2, 1, 2);
    m1.SetVal(2, 2, 1);
    S21Matrix result(3, 3);
    result.SetVal(0, 0, 0);
    result.SetVal(0, 1, 10);
    result.SetVal(0, 2, -20);
    result.SetVal(1, 0, 4);
    result.SetVal(1, 1, -14);
    result.SetVal(1, 2, 8);
    result.SetVal(2, 0, -8);
    result.SetVal(2, 1, -2);
    result.SetVal(2, 2, 4);
    m1.CalcComplements();

    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(result.GetVal(i, j), m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, Transpose) {
    S21Matrix m1(3, 2);
    m1.ValGen();
    m1.Transpose();
    S21Matrix result(2, 3);
    result.SetVal(0, 0, 1);
    result.SetVal(0, 1, 3);
    result.SetVal(0, 2, 5);
    result.SetVal(1, 0, 2);
    result.SetVal(1, 1, 4);
    result.SetVal(1, 2, 6);

    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(result.GetVal(i, j), m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, InverseMatrix) {
    S21Matrix m1;
    S21Matrix result;
    m1.SetVal(0, 0, 2);
    m1.SetVal(0, 1, 5);
    m1.SetVal(0, 2, 7);
    m1.SetVal(1, 0, 6);
    m1.SetVal(1, 1, 3);
    m1.SetVal(1, 2, 4);
    m1.SetVal(2, 0, 5);
    m1.SetVal(2, 1, -2);
    m1.SetVal(2, 2, -3);
    result.SetVal(0, 0, 1);
    result.SetVal(0, 1, -1);
    result.SetVal(0, 2, 1);
    result.SetVal(1, 0, -38);
    result.SetVal(1, 1, 41);
    result.SetVal(1, 2, -34);
    result.SetVal(2, 0, 27);
    result.SetVal(2, 1, -29);
    result.SetVal(2, 2, 24);
    m1.InverseMatrix();

    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(result.GetVal(i, j), m1.GetVal(i, j));
        }
    }
}

// ################################ OVERLOADS ###################################

TEST(S21Matrix, operotorSUM) {
    S21Matrix m1(4, 5);
    S21Matrix m2(4, 5);
    // S21Matrix m3(7, 8);
    m1.ValGen();
    m2.ValGen();
    m1 += m2;
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(n++ * 2, m1.GetVal(i, j));
        }
    }
    S21Matrix m3 = m1 + m2;
    n = 1;
    for (int i = 0; i < m3.GetRow(); i++) {
        for (int j = 0; j < m3.GetCol(); j++) {
            EXPECT_EQ(n++ * 3, m3.GetVal(i, j));
        }
    }
    EXPECT_EQ(0, m1.EqMatrix(m2));
    EXPECT_EQ(0, m3.EqMatrix(m2));
}

TEST(S21Matrix, operotorSUB) {
    S21Matrix m1(4, 5);
    S21Matrix m2(4, 5);
    m1.ValGen();
    m2.ValGen();
    m1 -= m2;
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(0, m1.GetVal(i, j));
        }
    }
    S21Matrix m3 = m1 - m2;
    n = 0;
    for (int i = 0; i < m3.GetRow(); i++) {
        for (int j = 0; j < m3.GetCol(); j++) {
            EXPECT_EQ(--n, m3.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, operotorEQ) {
    S21Matrix m1(4, 5);
    S21Matrix m2(6, 6);
    m1.ValGen();
    m1 = m2;
    S21Matrix m3 = m1;
    EXPECT_EQ(1, m1.EqMatrix(m2));
    EXPECT_EQ(1, m3.EqMatrix(m1));
}

TEST(S21Matrix, operatorMulNumber) {
    S21Matrix m1(4, 5);
    m1.ValGen();
    double num = 3;
    m1 *= num;
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(n++ * num, m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, operatorMulMatrix) {
    S21Matrix m1(3, 2);
    m1.SetVal(0, 0, 1);
    m1.SetVal(0, 1, 4);
    m1.SetVal(1, 0, 2);
    m1.SetVal(1, 1, 5);
    m1.SetVal(2, 0, 3);
    m1.SetVal(2, 1, 6);
    S21Matrix m2(2, 3);
    m2.SetVal(0, 0, 1);
    m2.SetVal(0, 1, -1);
    m2.SetVal(0, 2, 1);
    m2.SetVal(1, 0, 2);
    m2.SetVal(1, 1, 3);
    m2.SetVal(1, 2, 4);
    S21Matrix m3(3, 3);
    m3.SetVal(0, 0, 9);
    m3.SetVal(0, 1, 11);
    m3.SetVal(0, 2, 17);
    m3.SetVal(1, 0, 12);
    m3.SetVal(1, 1, 13);
    m3.SetVal(1, 2, 22);
    m3.SetVal(2, 0, 15);
    m3.SetVal(2, 1, 15);
    m3.SetVal(2, 2, 27);

    m1 *= m2;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(m3.GetVal(i, j), m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, operatorEqMatrix) {
    S21Matrix m1(7, 9);
    S21Matrix m2(7, 9);
    S21Matrix m3(7, 8);
    EXPECT_EQ(0, m1 == m3);
    m1.ValGen();
    m2.ValGen();
    EXPECT_EQ(1, m1 == m2);
    m1.SetVal(4, 4, 33);
    EXPECT_EQ(0, m1 == m2);
    m3 = m1;
    EXPECT_EQ(1, m1 == m3);
    EXPECT_EQ(1, m3 == m1);
}

TEST(S21Matrix, operotorSumEq) {
    S21Matrix m1(4, 5);
    S21Matrix m2(4, 5);
    m1.ValGen();
    m2.ValGen();
    m1 += m2;
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(n++ * 2, m1.GetVal(i, j));
        }
    }
    EXPECT_EQ(0, m1.EqMatrix(m2));
}

TEST(S21Matrix, operotorSubEq) {
    S21Matrix m1(4, 5);
    S21Matrix m2(4, 5);
    m1.ValGen();
    m2.ValGen();
    m1 -= m2;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(0, m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, operatorMulNumberEq) {
    S21Matrix m1(4, 5);
    m1.ValGen();
    double num = 3;
    m1 *= num;
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(n++ * num, m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, operatorMulMatrixEq) {
    S21Matrix m1(3, 2);
    m1.SetVal(0, 0, 1);
    m1.SetVal(0, 1, 4);
    m1.SetVal(1, 0, 2);
    m1.SetVal(1, 1, 5);
    m1.SetVal(2, 0, 3);
    m1.SetVal(2, 1, 6);
    S21Matrix m2(2, 3);
    m2.SetVal(0, 0, 1);
    m2.SetVal(0, 1, -1);
    m2.SetVal(0, 2, 1);
    m2.SetVal(1, 0, 2);
    m2.SetVal(1, 1, 3);
    m2.SetVal(1, 2, 4);
    S21Matrix m3(3, 3);
    m3.SetVal(0, 0, 9);
    m3.SetVal(0, 1, 11);
    m3.SetVal(0, 2, 17);
    m3.SetVal(1, 0, 12);
    m3.SetVal(1, 1, 13);
    m3.SetVal(1, 2, 22);
    m3.SetVal(2, 0, 15);
    m3.SetVal(2, 1, 15);
    m3.SetVal(2, 2, 27);

    m1 *= m2;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(m3.GetVal(i, j), m1.GetVal(i, j));
        }
    }
}

TEST(S21Matrix, operatorHZ) {
    S21Matrix m1(4, 5);
    m1.ValGen();
    int n = 1;
    for (int i = 0; i < m1.GetRow(); i++) {
        for (int j = 0; j < m1.GetCol(); j++) {
            EXPECT_EQ(n++, m1(i, j));
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}