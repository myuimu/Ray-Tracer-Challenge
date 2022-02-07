#pragma once
#include <iostream>
#include <vector>
#include "tuple/tuple.h"

namespace ray {

    class matrix {
        private:
            std::vector<std::vector<double>> values;
        public:
            matrix(const int &width, const int &height);
            matrix(const std::vector<std::vector<double>> &values);

            int getWidth() const;
            int getHeight() const;

            matrix getTranspose() const;
            double getDeterminant() const;
            matrix getSubmatrix(const int &row, const int &col) const;
            double getMinor(const int &row, const int &col) const;
            double getCofactor(const int &row, const int &col) const;
            bool isInvertable() const;
            matrix getInverse() const;

            const std::vector<double> &operator[](const int &index) const;
            matrix operator*(const matrix &rhs) const;
            tuple operator*(const tuple &rhs) const;
            bool operator==(const matrix &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const matrix &m);
    };

    matrix getIdentityMatrix();

    inline const matrix IDENTITY_MATRIX = getIdentityMatrix();
};