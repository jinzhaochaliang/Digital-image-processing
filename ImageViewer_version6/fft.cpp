#include "fft.h"
#include<iostream>

#define PI 3.1415926

using std::complex;
using std::vector;


size_t calcN(size_t length) {
  // check if length is power of 2
  // if it is, just return length
  // if not, get the correct N and return
    if((length&(length-1))==0){
        return length;
    }else{
        size_t temp = length;
        while(1){
            length = length>>1;
//            std::cout<<length<<" ----\n";
            temp = length|temp;
//            std::cout<<temp<<"******\n";
            if(length==0) break;
        }
        return temp+1;
    }
}

std::complex<double> w(int N,int k){
//    return exp(std::complex<double>(0,-2*PI*k/N));
    return complex<double>(cos(2*PI*k/N),sin(2*PI*k/N));
}

vector<complex<double> >
fft(vector<int> data, size_t N)
{
  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)
    vector<complex<double>> temp;
    for(size_t i=0;i<data.size();i++){
        temp.push_back(complex<double>(data[i],0));
    }
    return fft(temp,N);
}

vector<complex<double> >
fft(vector<double> data, size_t N)
{

  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)
    vector<complex<double>> temp;
    for(size_t i=0;i<data.size();i++){
        temp.push_back(complex<double>(data[i],0));
    }
    return fft(temp,N);
}

vector<complex<double>> fft(vector<complex<double> > data, size_t N) {

  // check length of data, and append 0 if neccessary

  // start fft
  // check if N is 0, 1, 2
  // if N is 0 or 1, just return data
  // if N is 2, do dft on them
  // if N > 2, do fft
    // 1. split input into two parts
    // 2. do fft on them seperately
    // 3. construct result from output
    vector<complex<double> > temp = data;
    if(data.size()==calcN(N)){
        N = calcN(data.size());
//        data.assign(data.begin(),data.begin()+N);
    }else if(data.size()>calcN(N)){
        N = calcN(data.size());
        data.assign(temp.begin(),temp.begin()+N);
    }else{
        N = calcN(N);
        data.assign(temp.begin(),temp.begin()+N);
    }
    if(N==0||N==1){
        return data;
    }else if(N==2){
        complex<double> x0 = data[0];
        complex<double> x1 = data[1];
        data[0] = x0 + x1*w(N,0);
        data[1] = x0 + x1*w(N,1);
        return  data;
    }else if(N>2){
        vector<complex<double>> xk1,xk2;
        for(size_t i=0;i<N/2;i++){
            xk1.push_back(data[2*i]);
            xk2.push_back(data[2*i+1]);
        }
        xk1 = fft(xk1,N/2);
        xk2 = fft(xk2,N/2);
        for(size_t i=0;i<N/2;i++){
            data[i] = xk1[i]+xk2[i]*w(N,i);
            data[i+N/2] = xk1[i]-xk2[i]*w(N,i);
        }
        return data;
    }
}

vector<complex<double> >
ifft(vector<int> data, size_t N)
{
  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)
    vector<complex<double>> temp;
    for(size_t i=0;i<data.size();i++){
        temp.push_back(complex<double>(data[i],0));
    }
    return ifft(temp,N);
}

vector<complex<double> >
ifft(vector<double> data, size_t N)
{

  // convert data to vector<complex<double> >
  // call:
  // vector<complex<double> >
  // fft(vector<complex<double> > data, size_t N)
    vector<complex<double>> temp;
    for(size_t i=0;i<data.size();i++){
        temp.push_back(complex<double>(data[i],0));
    }
    return ifft(temp,N);
}

vector<complex<double>> ifft(vector<complex<double> > data, size_t N) {

  // check length of data, and append 0 if neccessary

  // start fft
  // check if N is 0, 1, 2
  // if N is 0 or 1, just return data
  // if N is 2, do dft on them
  // if N > 2, do fft
    // 1. split input into two parts
    // 2. do fft on them seperately
    // 3. construct result from output
    vector<complex<double> > temp = data;
    if(data.size()==calcN(N)){
        N = calcN(data.size());
//        data.assign(data.begin(),data.begin()+N);
    }else if(data.size()>calcN(N)){
        N = calcN(data.size());
        data.assign(temp.begin(),temp.begin()+N);
    }else{
        N = calcN(N);
        data.assign(temp.begin(),temp.begin()+N);
    }
    if(N==0||N==1){
        return data;
    }else if(N==2){
        complex<double> x0 = data[0];
        complex<double> x1 = data[1];
        data[0] = x0 + x1*w(-N,0);
        data[1] = x0 + x1*w(-N,1);
        data[0].imag(data[0].imag()/2);
        data[0].real(data[0].real()/2);
        data[1].imag(data[1].imag()/2);
        data[1].real(data[1].real()/2);
        return  data;
    }else if(N>2){
        vector<complex<double>> xk1,xk2;
        for(size_t i=0;i<N/2;i++){
            xk1.push_back(data[2*i]);
            xk2.push_back(data[2*i+1]);
        }
        xk1 = ifft(xk1,N/2);
        xk2 = ifft(xk2,N/2);
        for(size_t i=0;i<N/2;i++){
            data[i] = xk1[i]+xk2[i]*w(-N,i);
            data[i+N/2] = xk1[i]-xk2[i]*w(-N,i);
        }

        for(size_t i=0;i<data.size();i++){
            data[i].imag(data[i].imag()*2/N);
            data[i].real(data[i].real()*2/N);
        }
        return data;
    }
}













