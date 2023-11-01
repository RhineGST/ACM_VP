#include <bits/stdc++.h>

using ll = long long;
using std::vector, std::swap, std::cin, std::cout, std::endl;

struct Complex {
    double real = 0, imag = 0;

    ~Complex() = default;

    Complex operator+ (const Complex &b) const {
        return {real + b.real, imag + b.imag};
    }

    Complex operator- (const Complex &b) const {
        return {real - b.real, imag - b.imag};
    }

    Complex operator* (const Complex &b) const {
        return {real * b.real - imag * b.imag, real * b.imag + imag * b.real};
    }
};

struct Poly : public std::vector<Complex> {

    using std::vector<Complex>::vector;

    bool operator<(const Poly &b) const {
        return size() > b.size();
    }
};

void FFT(Poly &A, vector<int> &R, int lim, int type) {
    for (int i = 0; i < lim; i++) {
        if (i < R[i]) {
            swap(A[i], A[R[i]]);
        }
    }
    for (int mid = 1; mid < lim; mid <<= 1) {
        Complex wn(cos(M_PI / mid), type * sin(M_PI / mid));
        for (int len = mid << 1, pos = 0; pos < lim; pos += len) {
            Complex w(1.0, 0.0);
            for (int k = 0; k < mid; ++k, w = w * wn) {
                Complex x = A[pos + k];
                Complex y = w * A[pos + mid + k];
                A[pos + k] = x + y;
                A[pos + mid + k] = x - y;
            }
        }
    }
    if (type == -1) {
        Complex inv(1.0 / lim, 0.0);
        for (int i = 0; i < lim; i++) {
            A[i] = A[i] * inv;
        }
    }
}

Poly operator*(Poly A, Poly B) {
    int lim = 1, lim_bit = 0;
    auto sz = A.size() + B.size() - 1;
    while (lim <= A.size() + B.size()) {
        lim <<= 1, lim_bit++;
    }
    A.resize(lim);
    B.resize(lim);
    vector<int> R(lim, 0);
    for (int i = 1; i < lim; i++) {
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (lim_bit - 1));
    }
    FFT(A, R, lim, 1);
    FFT(B, R, lim, 1);
    Poly res(lim);
    for (int i = 0; i < lim; i++) {
        res[i] = A[i] * B[i];
    }
    FFT(res, R, lim, -1);
    res.resize(sz);
    return res;
}