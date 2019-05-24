#include "fft2d.h"

Matrix<std::complex<double>> fftRow(const Matrix<std::complex<double>>& data){

    size_t r = data.getNRow();
    for(size_t i=0;i<r;i++){
        data.setRow(i,fft(data.getRow(i)));
    }
    return data;
}
Matrix<std::complex<double>> fft2d(const Matrix<int>& data,size_t r,size_t c){
    Matrix<std::complex<double>> temp(data.getNRow(),data.getNCol(),0);
    for(size_t i=0;i<data.getNRow();i++){
        for(size_t j=0;j<data.getNCol();j++){
            temp(i,j).real(data(i,j));
        }
    }
    return fft2d(temp,r,c);
}
Matrix<std::complex<double>> fft2d(const Matrix<double>& data,size_t r,size_t c){
    Matrix<std::complex<double>> temp(data.getNRow(),data.getNCol(),0);
    for(size_t i=0;i<data.getNRow();i++){
        for(size_t j=0;j<data.getNCol();j++){
            temp(i,j).real(data(i,j));
        }
    }
    return fft2d(temp,r,c);
}
Matrix<std::complex<double>> fft2d(const Matrix<std::complex<double> >& data,size_t r,size_t c){
    r = calcN(r);
    c = calcN(c);
    Matrix<std::complex<double> > res(r,c,0);
    //二重循环
    for(size_t i=0;i<data.getNRow();i++){
        for(size_t j=0;j<data.getNCol();j++){
            res(i,j) = data(i,j);
        }
    }
//    return fftRow(fftRow(data).transpose()).transpose();

    Matrix<std::complex<double> > res1(fftRow(res));
//    cout<<res1;
    Matrix<std::complex<double> > res2(res1.getNCol(),res1.getNRow(),0);
    for(size_t i=0;i<res1.getNCol();i++){
        for(size_t j=0;j<res1.getNRow();j++){
            res2(i,j) = res1(j,i);
        }
    }
//    cout<<res2;
    Matrix<std::complex<double> > res3(fftRow(res2));
//    cout<<res3;
    Matrix<std::complex<double> > res4(res3.getNCol(),res3.getNRow(),0);
    for(size_t i=0;i<res3.getNCol();i++){
        for(size_t j=0;j<res4.getNRow();j++){
            res4(i,j) = res3(j,i);
        }
    }
    return res4;
}


Matrix<std::complex<double>> ifftRow(const Matrix<std::complex<double>>& data){

    size_t r = data.getNRow();
    for(size_t i=0;i<r;i++){
        data.setRow(i,ifft(data.getRow(i)));
    }
    return data;
}
Matrix<std::complex<double>> ifft2d(const Matrix<int>& data,size_t r,size_t c){
    Matrix<std::complex<double>> temp(data.getNRow(),data.getNCol(),0);
    for(size_t i=0;i<data.getNRow();i++){
        for(size_t j=0;j<data.getNCol();j++){
            temp(i,j).real(data(i,j));
        }
    }
    return ifft2d(temp,r,c);
}
Matrix<std::complex<double>> ifft2d(const Matrix<double>& data,size_t r,size_t c){
    Matrix<std::complex<double>> temp(data.getNRow(),data.getNCol(),0);
    for(size_t i=0;i<data.getNRow();i++){
        for(size_t j=0;j<data.getNCol();j++){
            temp(i,j).real(data(i,j));
        }
    }
    return ifft2d(temp,r,c);
}
Matrix<std::complex<double>> ifft2d(const Matrix<std::complex<double> >& data,size_t r,size_t c){
    r = calcN(r);
    c = calcN(c);
    Matrix<std::complex<double> > res(r,c,0);
    //二重循环
    for(size_t i=0;i<data.getNRow();i++){
        for(size_t j=0;j<data.getNCol();j++){
            res(i,j) = data(i,j);
        }
    }
//    return ifftRow(ifftRow(data).transpose()).transpose();

    Matrix<std::complex<double> > res1(ifftRow(res));
    Matrix<std::complex<double> > res2(res1.getNCol(),res1.getNRow(),0);
    for(size_t i=0;i<res1.getNCol();i++){
        for(size_t j=0;j<res1.getNRow();j++){
            res2(i,j) = res1(j,i);
        }
    }
    Matrix<std::complex<double> > res3(ifftRow(res2));
    Matrix<std::complex<double> > res4(res3.getNCol(),res3.getNRow(),0);
    for(size_t i=0;i<res3.getNCol();i++){
        for(size_t j=0;j<res4.getNRow();j++){
            res4(i,j) = res3(j,i);
        }
    }

    return res4;
}
