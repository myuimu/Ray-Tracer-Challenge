#pragma once
#include <iostream>
#include <vector>
#include "tuple/tuple.h"

namespace rayTracer {
    class matrix {
        private:
            std::vector<std::vector<double>> values;
        public:
            matrix(const int &width, const int &height);
            matrix(const std::vector<std::vector<double>> &values);
            matrix(const matrix &m);

            int getWidth() const;
            int getHeight() const;

            matrix getTranspose() const;
            double getDeterminant() const;
            matrix getSubmatrix(const int &row, const int &col) const;
            double getMinor(const int &row, const int &col) const;
            double getCofactor(const int &row, const int &col) const;
            bool isInvertable() const;
            matrix getInverse() const;

            matrix translate(const double &x, const double &y, const double &z) const;
            matrix scale(const double &x, const double &y, const double &z) const;
            matrix rotateX(const double &r) const;
            matrix rotateY(const double &r) const;
            matrix rotateZ(const double &r) const;
            matrix shear(const double &xY, const double &xZ, const double &yX, const double &yZ, const double &zX, const double &zY) const;

            const std::vector<double> &operator[](const int &index) const;
            matrix operator*(const matrix &rhs) const;
            tuple operator*(const tuple &rhs) const;
            bool operator==(const matrix &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const matrix &m);
    };

    matrix getIdentityMatrix();

    inline const matrix IDENTITY_MATRIX = getIdentityMatrix();
};