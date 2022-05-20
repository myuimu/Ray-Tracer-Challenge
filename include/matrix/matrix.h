#pragma once
#include <iostream>
#include <vector>
#include "tuple/tuple.h"

namespace rayTracer {
    class matrix {
        private:
            std::vector<std::vector<float>> values;
        public:
            matrix(const int &width, const int &height);
            matrix(const std::vector<std::vector<float>> &values);
            matrix(const matrix &m);

            int getWidth() const;
            int getHeight() const;

            matrix getTranspose() const;
            float getDeterminant() const;
            matrix getSubmatrix(const int &row, const int &col) const;
            float getMinor(const int &row, const int &col) const;
            float getCofactor(const int &row, const int &col) const;
            bool isInvertable() const;
            matrix getInverse() const;

            matrix translate(const float &x, const float &y, const float &z) const;
            matrix scale(const float &x, const float &y, const float &z) const;
            matrix rotateX(const float &r) const;
            matrix rotateY(const float &r) const;
            matrix rotateZ(const float &r) const;
            matrix shear(const float &xY, const float &xZ, const float &yX, const float &yZ, const float &zX, const float &zY) const;

            const std::vector<float> &operator[](const int &index) const;
            matrix operator*(const matrix &rhs) const;
            tuple operator*(const tuple &rhs) const;
            bool operator==(const matrix &rhs) const;

            friend std::ostream& operator<<(std::ostream &os, const matrix &m);
    };
    std::ostream& operator<<(std::ostream &os, const matrix &m);

    matrix getIdentityMatrix();

    inline const matrix IDENTITY_MATRIX = getIdentityMatrix();
};