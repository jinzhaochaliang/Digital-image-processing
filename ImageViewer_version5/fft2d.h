#ifndef FFT2D_H
#define FFT2D_H
#include"matrix.h"
#include"fft.h"

Matrix<std::complex<double>> fft2d(const Matrix<int>&,size_t,size_t);
Matrix<std::complex<double>> fft2d(const Matrix<double>&,size_t,size_t);
Matrix<std::complex<double>> fft2d(const Matrix<std::complex<double> >&,size_t,size_t);
Matrix<std::complex<double>> fftRow(const Matrix<std::complex<double>>& data);

Matrix<std::complex<double>> ifft2d(const Matrix<int>&,size_t,size_t);
Matrix<std::complex<double>> ifft2d(const Matrix<double>&,size_t,size_t);
Matrix<std::complex<double>> ifft2d(const Matrix<std::complex<double> >&,size_t,size_t);
Matrix<std::complex<double>> ifftRow(const Matrix<std::complex<double>>& data);

#endif
