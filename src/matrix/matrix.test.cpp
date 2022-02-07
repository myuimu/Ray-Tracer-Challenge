#include <boost/test/unit_test.hpp>
#include "matrix/matrix.h"

using namespace ray;

BOOST_AUTO_TEST_SUITE(matrixTest)

/*-----CONSTRUCTOR TESTS-----*/

BOOST_AUTO_TEST_CASE(construct4x4Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    }));

    BOOST_CHECK_EQUAL(m[0][0], 1);
    BOOST_CHECK_EQUAL(m[0][3], 4);
    BOOST_CHECK_EQUAL(m[1][0], 5.5);
    BOOST_CHECK_EQUAL(m[1][2], 7.5);
    BOOST_CHECK_EQUAL(m[2][2], 11);
    BOOST_CHECK_EQUAL(m[3][0], 13.5);
    BOOST_CHECK_EQUAL(m[3][2], 15.5);
}

BOOST_AUTO_TEST_CASE(construct2x2Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {-3, 5},
        {1, -2}
    }));

    BOOST_CHECK_EQUAL(m[0][0], -3);
    BOOST_CHECK_EQUAL(m[0][1], 5);
    BOOST_CHECK_EQUAL(m[1][0], 1);
    BOOST_CHECK_EQUAL(m[1][1], -2);
}

BOOST_AUTO_TEST_CASE(construct3x3Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    }));

    BOOST_CHECK_EQUAL(m[0][0], -3);
    BOOST_CHECK_EQUAL(m[1][1], -2);
    BOOST_CHECK_EQUAL(m[2][2], 1);
}

/*-----OPERATOR TESTS-----*/

BOOST_AUTO_TEST_CASE(compareIdenticalMatrices) {
    auto m1 = matrix(std::vector<std::vector<double>>({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    }));
    auto m2 = matrix(std::vector<std::vector<double>>({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    }));

    BOOST_CHECK_EQUAL(m1, m2);
}

BOOST_AUTO_TEST_CASE(compareDifferentMatrices) {
    auto m1 = matrix(std::vector<std::vector<double>>({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    }));
    auto m2 = matrix(std::vector<std::vector<double>>({
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    }));

    BOOST_CHECK_EQUAL(m1 == m2, false);
}

BOOST_AUTO_TEST_CASE(multiplyMatrices) {
    auto m1 = matrix(std::vector<std::vector<double>>({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    }));
    auto m2 = matrix(std::vector<std::vector<double>>({
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}
    }));

    auto expected = matrix(std::vector<std::vector<double>>({
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    }));

    BOOST_CHECK_EQUAL(m1 * m2, expected);
}

BOOST_AUTO_TEST_CASE(multiplyMatrixAndTuple) {
    auto m = matrix(std::vector<std::vector<double>>({
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    }));
    auto t = tuple(1, 2, 3, 1);

    auto expected = tuple(18, 24, 33, 1);

    BOOST_CHECK_EQUAL(m * t, expected);
}

BOOST_AUTO_TEST_CASE(identityMultiply) {
    auto m = matrix(std::vector<std::vector<double>>({
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    }));

    BOOST_CHECK_EQUAL(m * IDENTITY_MATRIX, m);
}

BOOST_AUTO_TEST_CASE(transposeMatrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}
    }));

    auto expected = matrix(std::vector<std::vector<double>>({
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}
    }));

    BOOST_CHECK_EQUAL(m.getTranspose(), expected);
}

BOOST_AUTO_TEST_CASE(transposeIdentityMatrix) {
    BOOST_CHECK_EQUAL(IDENTITY_MATRIX.getTranspose(), IDENTITY_MATRIX);
}

BOOST_AUTO_TEST_CASE(determinantOf2x2Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {1, 5},
        {-3, 2}
    }));

    BOOST_CHECK_EQUAL(m.getDeterminant(), 17);
}

BOOST_AUTO_TEST_CASE(subMatrixOf3x3Is2x2) {
    auto m = matrix(std::vector<std::vector<double>>({
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3}
    }));

    auto expected = matrix(std::vector<std::vector<double>>({
        {-3, 2},
        {0, 6}
    }));

    BOOST_CHECK_EQUAL(m.getSubmatrix(0, 2), expected);
}

BOOST_AUTO_TEST_CASE(subMatrixOf4x4Is3x3) {
    auto m = matrix(std::vector<std::vector<double>>({
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    }));

    auto expected = matrix(std::vector<std::vector<double>>({
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    }));

    BOOST_CHECK_EQUAL(m.getSubmatrix(2, 1), expected);
}

BOOST_AUTO_TEST_CASE(minorOf3x3Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    }));
    auto s = m.getSubmatrix(1, 0);

    BOOST_CHECK_EQUAL(s.getDeterminant(), 25);
    BOOST_CHECK_EQUAL(m.getMinor(1, 0), 25);
}

BOOST_AUTO_TEST_CASE(cofactorOf3x3Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    }));

    BOOST_CHECK_EQUAL(m.getMinor(0, 0), -12);
    BOOST_CHECK_EQUAL(m.getCofactor(0, 0), -12);
    BOOST_CHECK_EQUAL(m.getMinor(1, 0), 25);
    BOOST_CHECK_EQUAL(m.getCofactor(1, 0), -25);
}

BOOST_AUTO_TEST_CASE(determinantOf3x3Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    }));

    BOOST_CHECK_EQUAL(m.getCofactor(0, 0), 56);
    BOOST_CHECK_EQUAL(m.getCofactor(0, 1), 12);
    BOOST_CHECK_EQUAL(m.getCofactor(0, 2), -46);
    BOOST_CHECK_EQUAL(m.getDeterminant(), -196);
}

BOOST_AUTO_TEST_CASE(determinantOf4x4Matrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    }));

    BOOST_CHECK_EQUAL(m.getCofactor(0, 0), 690);
    BOOST_CHECK_EQUAL(m.getCofactor(0, 1), 447);
    BOOST_CHECK_EQUAL(m.getCofactor(0, 2), 210);
    BOOST_CHECK_EQUAL(m.getCofactor(0, 3), 51);
    BOOST_CHECK_EQUAL(m.getDeterminant(), -4071);
}

BOOST_AUTO_TEST_CASE(matrixIsInvertable) {
    auto m = matrix(std::vector<std::vector<double>>({
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6}
    }));

    BOOST_CHECK_EQUAL(m.getDeterminant(), -2120);
    BOOST_CHECK_EQUAL(m.isInvertable(), true);
}

BOOST_AUTO_TEST_CASE(matrixIsNotInvertable) {
    auto m = matrix(std::vector<std::vector<double>>({
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}
    }));

    BOOST_CHECK_EQUAL(m.getDeterminant(), 0);
    BOOST_CHECK_EQUAL(m.isInvertable(), false);
}

BOOST_AUTO_TEST_CASE(inverseOfMatrix) {
    auto m = matrix(std::vector<std::vector<double>>({
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    }));
    auto i = m.getInverse();

    auto expected = matrix(std::vector<std::vector<double>>({
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}
    }));

    BOOST_CHECK_EQUAL(m.getDeterminant(), 532);
    BOOST_CHECK_EQUAL(m.getCofactor(2, 3), -160);
    BOOST_CHECK_EQUAL(i[3][2], -160.0/532.0);
    BOOST_CHECK_EQUAL(m.getCofactor(3, 2), 105);
    BOOST_CHECK_EQUAL(i[2][3], 105.0/532.0);
    BOOST_CHECK_EQUAL(i, expected);
}

BOOST_AUTO_TEST_CASE(inverseOfMatrix2) {
    auto m = matrix(std::vector<std::vector<double>>({
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    }));
    auto i = m.getInverse();

    auto expected = matrix(std::vector<std::vector<double>>({
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}
    }));

    BOOST_CHECK_EQUAL(i, expected);
}

BOOST_AUTO_TEST_CASE(inverseOfMatrix3) {
    auto m = matrix(std::vector<std::vector<double>>({
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    }));
    auto i = m.getInverse();

    auto expected = matrix(std::vector<std::vector<double>>({
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}
    }));

    BOOST_CHECK_EQUAL(i, expected);
}

BOOST_AUTO_TEST_CASE(multiplyingInverseGetsOriginal) {
    auto m1 = matrix(std::vector<std::vector<double>>({
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    }));
    auto m2 = matrix(std::vector<std::vector<double>>({
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    }));

    auto product = m1 * m2;

    BOOST_CHECK_EQUAL(product * m2.getInverse(), m1);
}

BOOST_AUTO_TEST_SUITE_END()