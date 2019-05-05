#ifndef FFT__H
#define FFT__H

#include <complex>
#include <vector>
#include <cmath>

const double PI = 3.1415926;

size_t calcN(size_t length);
std::complex<double> pow(std::complex<double> base, int exponent);

// different function with different input
std::vector<std::complex<double> > fft(std::vector<int> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<double> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<std::complex<double> > data, size_t N=0) ;

std::complex<double> w(int N,int k);

#endif
