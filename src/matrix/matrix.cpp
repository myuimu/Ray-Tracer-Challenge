#include "matrix/matrix.h"
#include "matrix/transformation.h"
#include "ray_tracer.h"
#include <sstream>
#include <vector>

using namespace ray;

matrix::matrix(const int &width, const int &height):
    values{std::vector<std::vector<double>>(height, std::vector<double>(width, 0))}
    {}

matrix::matrix(const std::vector<std::vector<double>> &values):
    values{values}
    {}

int matrix::getWidth() const {
    if (values.size() > 0) {
        return values[0].size();
    }
    return 0;
}

int matrix::getHeight() const {
    return values.size();
}

matrix matrix::getTranspose() const {
    std::vector<std::vector<double>> newValues;

    for (int i = 0; i < getHeight(); i++) {
        newValues.push_back(std::vector<double>());
        for (int j = 0; j < getWidth(); j++) {
            newValues[i].push_back(values[j][i]);
        }
    }

    return matrix(newValues);
}

double matrix::getDeterminant() const {
    double det = 0;

    auto width = getWidth();
    auto height = getHeight();

    if (width == 2 && height == 2) {
        det = (values[0][0] * values[1][1]) - 
               (values[0][1] * values[1][0]);
    } else {
        for (int i = 0; i < width; i++) {
            det += values[0][i] * getCofactor(0, i);
        }
    }

    return det;
}

matrix matrix::getSubmatrix(const int &row, const int &col) const {
    auto newValues = values;

    newValues.erase(newValues.begin() + row);
    for (auto &newRow : newValues) {
        newRow.erase(newRow.begin() + col);
    }

    return matrix(newValues);
}

double matrix::getMinor(const int &row, const int &col) const {
    return getSubmatrix(row, col).getDeterminant();
}

double matrix::getCofactor(const int &row, const int &col) const {
    auto minor = getMinor(row, col);

    if ((row + col) % 2 != 0) {
        return -minor;
    }
    return minor;
}

bool matrix::isInvertable() const {
    return getDeterminant() != 0;
}

matrix matrix::getInverse() const {
    auto width = getWidth();
    auto height = getHeight();
    auto det = getDeterminant();

    auto newValues = std::vector<std::vector<double>>(height, std::vector<double>(width, 0));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newValues[j][i] = getCofactor(i, j) / det;
        }
    }

    return matrix(newValues);
}

matrix matrix::translate(const double &x, const double &y, const double &z) const {
    return ray::translation(x, y, z) * *this;
}

matrix matrix::scale(const double &x, const double &y, const double &z) const {
    return ray::scaling(x, y ,z) * *this;
}

matrix matrix::rotateX(const double &r) const {
    return ray::xRotation(r) * *this;
}

matrix matrix::rotateY(const double &r) const {
    return ray::yRotation(r) * *this;
}

matrix matrix::rotateZ(const double &r) const {
    return zRotation(r) * *this;
}

matrix matrix::shear(const double &xY, const double &xZ, const double &yX, const double &yZ, const double &zX, const double &zY) const {
    return shearing(xY, xZ, yX, yZ, zX, zY) * *this;
}

const std::vector<double> &matrix::operator[](const int &index) const {
    return values.at(index);
}

matrix matrix::operator*(const matrix &rhs) const {
    std::vector<std::vector<double>> newValues;

    auto width = getWidth();
    auto height = rhs.getHeight();

    if (width != height) {
        std::stringstream e;
        e << "Dimensions of matrices are incompatible:" << std::endl;
        e << "lhs columns: " << width << std::endl;
        e << "rhs rows: " << height << std::endl;
        throw std::invalid_argument(e.str());
    }

    for (int i = 0; i < height; i++) {
        newValues.push_back(std::vector<double>());
        for (int j = 0; j < width; j++) {
            double sum = 0;
            for (int k = 0; k < width; k++) {
                sum += values[i][k] * rhs.values[k][j];
            }
            newValues[i].push_back(sum);
        }
    }

    return matrix(newValues);
}

tuple matrix::operator*(const tuple &rhs) const {
    if (getWidth() != 4 || getHeight() != 4) {
        std::stringstream e;
        e << "Dimensions of matrix are incompatible with tuple(4):" << std::endl;
        e << "lhs columns: " << getWidth() << std::endl;
        e << "lhs rows: " << getHeight() << std::endl;
        throw std::invalid_argument(e.str());
    }

    return tuple(
        values[0][0] * rhs.getX() + values[0][1] * rhs.getY() + values[0][2] * rhs.getZ() + values[0][3] * rhs.getW(),
        values[1][0] * rhs.getX() + values[1][1] * rhs.getY() + values[1][2] * rhs.getZ() + values[1][3] * rhs.getW(),
        values[2][0] * rhs.getX() + values[2][1] * rhs.getY() + values[2][2] * rhs.getZ() + values[2][3] * rhs.getW(),
        values[3][0] * rhs.getX() + values[3][1] * rhs.getY() + values[3][2] * rhs.getZ() + values[3][3] * rhs.getW()
    );
}

bool matrix::operator==(const matrix &rhs) const {
    if (getWidth() != rhs.getWidth() || getHeight() != rhs.getHeight()) {
        return false;
    }

    for (int i = 0; i < values.size(); i++) {
        for (int j = 0; j < values[i].size(); j++) {
            if (!equalWithError(values[i][j], rhs.values[i][j])) {
                return false;
            }
        }
    }

    return true;
}

std::ostream& ray::operator<<(std::ostream &os, const matrix &m) {
    os << "Matrix(" << m.getHeight() << ", " << m.getWidth() << ")" << std::endl;
    return os;
}

matrix ray::getIdentityMatrix() {
    auto values = std::vector<std::vector<double>>({
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    });
    return matrix(values);
}