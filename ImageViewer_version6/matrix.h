#ifndef MATRIX__H
#define MATRIX__H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <QImage>

using std::range_error;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;

template<typename T>
class Matrix
{
private:
    // point to the data
    T** _data;
    // number of row and column
    //矩阵的行与列
    size_t _nRow, _nCol;
    // flag to indicate row-first or column-first
    //转置的标志
    int _t;
    //检查是否越界
    bool checkRange(size_t r, size_t c) const;
    //用于重载=操作符
    void swap(Matrix<T>& mat);

public:
    // construct a r-row and c-column matrix with all init element
    // 构造函数
    Matrix(size_t r, size_t c, T init);
    // copy constructor
    // 复制构造函数
    Matrix(const Matrix<T>& mat);
    //重载=操作符
    Matrix& operator=(Matrix<T> mat);
    //析构函数
    ~Matrix();
    // get element at r-row and c-column
    // return reference to make it modifiable
    //重载（）操作符
    T& operator()(size_t r, size_t c) const;
    // get a submatrix [rs:re,cs:ce]
    //矩阵选取一部分
    Matrix<T> subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const;
    // output the matrix

    //重载<<操作符
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& rhs);
    //得到行数
    size_t getNRow() const;
    //得到列数
    size_t getNCol() const;
    //得到某行所有元素的值
    std::vector<T> getRow(size_t r) const;
    //得到某列所有元素的值
    std::vector<T> getCol(size_t c) const;
    //给某行所有元素的赋值
    bool setRow(size_t r, const std::vector<T>& d) const;
    //给某列所有元素的赋值
    bool setCol(size_t c, const std::vector<T>& d) const;
    // transpose it in-place
    //矩阵转置函数
    Matrix<T>& transpose();

    //重载+-*/操作符
    Matrix<T> operator+(Matrix<T>& mat);
    Matrix<T> operator-(Matrix<T>& mat);
    Matrix<T> operator*(Matrix<T>& mat);
    template<typename K>
    Matrix<T> operator/(K m);

    template<typename U,typename K>
    friend Matrix<U> operator+(K m,Matrix<T>& mat);
    template<typename U,typename K>
    friend Matrix<U> operator+(Matrix<T>& mat,K m);

    Matrix<T> conv(Matrix<T>& mat2);

    Matrix<int> fromQImage(const QImage&,char);
    QImage toQImage(const Matrix<int>&);
    QImage toQImage(const Matrix<int>&,const Matrix<int>&,const Matrix<int>&);
    Matrix<T>& fftshift();
    Matrix<T> inverted3(Matrix<T>&);
};
template <typename T>
Matrix<T> Matrix<T>::inverted3(Matrix<T>& mat){
    T a1 = mat(0,0);
    T a2 = mat(1,0);
    T a3 = mat(2,0);
    T b1 = mat(0,1);
    T b2 = mat(1,1);
    T b3 = mat(2,1);
    T c1 = mat(0,2);
    T c2 = mat(1,2);
    T c3 = mat(2,2);
    Matrix<T> temp(3,3,0);
    T A = 1.0/(a1*(b2*c3-c2*b3)-a2*(b1*c3-c1*b3)+a3*(b1*c2-c1*b2));
    temp(0,0)=b2*c3-c2*b3;temp(0,1)=b3*c1-c3*b1;temp(0,2)=b1*c2-c1*b2;
    temp(1,0)=c2*a3-a2*c3;temp(1,1)=a1*c3-c1*a3;temp(1,2)=a2*c1-c2*a1;
    temp(2,0)=a2*b3-b2*a3;temp(2,1)=b1*a3-a1*b3;temp(2,2)=a1*b2-a2*b1;
    return A*temp;
}
template <typename T>
Matrix<T>& Matrix<T>::fftshift(){
    size_t r = this->_nRow;
    size_t c = this->_nCol;
    size_t start_r = r/2,start_c = c/2;
    Matrix<T> temp(r,c,0);
    for(size_t i=0;i<r;i++){
        for(size_t j=0;j<c;j++){
            temp(i,j) = this->operator()(i,j);
        }
    }
    for(size_t i=0;i<r;i++){
        for(size_t j=0;j<c;j++){
            this->operator()(i,j) = temp((i+start_r)%r,(j+start_c)%c);
        }
    }
    return *this;
}

template<typename T>
Matrix<int> Matrix<T>::fromQImage(const QImage& img,char c){
    Matrix<int> temp(img.height(),img.width(),0);
    for(size_t i=0;i<temp.getNRow();i++){
        for(size_t j=0;j<temp.getNCol();j++){
            QRgb rgb = img.pixel(i,j);
            switch(c){
                case 'r':
                    temp(i,j) = qRed(rgb);
                    break;
                case 'g':
                    temp(i,j) = qGreen(rgb);
                    break;
                case 'b':
                    temp(i,j) = qBlue(rgb);
                    break;
                case 'y':
                    temp(i,j) = qGray(rgb);
                    break;
            }
        }
    }
    return temp;
}

template<typename T>
QImage Matrix<T>::toQImage(const Matrix<int>& mat){
    QImage img(mat.getNCol(),mat.getNRow(),QImage::Format_RGB888);

    for(size_t i=0;i<mat.getNRow();i++){
        for(size_t j=0;j<mat.getNCol();j++){
            img.setPixel(i,j,qRgb(int(mat(i,j)),int(mat(i,j)),int(mat(i,j))));
        }
    }
    return img;
}

template<typename T>
QImage Matrix<T>::toQImage(const Matrix<int>& mat1,const Matrix<int>& mat2,const Matrix<int>& mat3){
    QImage img(mat1.getNCol(),mat1.getNRow(),QImage::Format_RGB888);

    for(size_t i=0;i<mat1.getNRow();i++){
        for(size_t j=0;j<mat1.getNCol();j++){
            img.setPixel(i,j,qRgb(int(mat1(i,j)),int(mat2(i,j)),int(mat3(i,j))));
        }
    }
    return img;
}

template <typename T>
Matrix<T> Matrix<T>::conv(Matrix<T>& mat2){
    size_t r = mat2._nRow;
    size_t c = mat2._nCol;
    Matrix<T> m(mat2);
    for(size_t i=0;i<r;++i){
        for(size_t j=0;j<c;++j){
            mat2(i,j) = m(r-1-i,c-1-j);
        }
    }
    Matrix<T> temp(_nRow+r-1,_nCol+c-1,0);
    for(size_t i=0;i<_nRow;++i){
        for(size_t j=0;j<_nCol;++j){
            temp(i+(r-1)/2,j+(c-1)/2) = this->operator()(i,j);
        }
    }
    for(size_t i=0;i<_nRow;++i){
        for(size_t j=0;j<_nCol;++j){
            size_t sum = 0;
            for(size_t k1=0;k1<r;k1++){
                for(size_t k2=0;k2<c;k2++){
                    sum += temp(i+k1,j+k2)*mat2(k1,k2);
                }
            }
            this->operator()(i,j) = sum;
        }
    }
    return *this;
}
//矩阵相加
template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& mat){
    Matrix<T> temp(mat);
    if(_nCol==mat._nCol&&_nRow==mat._nRow){
        for(size_t i=0;i<_nRow;++i){
            for(size_t j=0;j<_nCol;++j){
                temp(i,j) = this->operator()(i,j) + mat(i,j);
            }
        }
    }else{
        throw std::range_error("error!!!");
    }
    return temp;
}

//矩阵与其它类型相加
template<typename U,typename K>
Matrix<U> operator+(K m,Matrix<U>& mat){
    Matrix<U> temp(mat);
    for(size_t i=0;i<mat.getNRow();++i){
        for(size_t j=0;j<mat.getNCol();++j){
            temp(i,j) = m + mat(i,j);
        }
    }
    return temp;
}
template<typename U,typename K>
Matrix<U> operator+(Matrix<U>& mat,K m){
    return m+mat;
}

//矩阵相减
template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& mat){
    Matrix<T> temp(mat);
    if(_nCol==mat._nCol&&_nRow==mat._nRow){
        for(size_t i=0;i<_nRow;++i){
            for(size_t j=0;j<_nCol;++j){
                temp(i,j) = this->operator()(i,j) - mat(i,j);
            }
        }
    }else{
        throw std::range_error("error!!!");
    }
    return temp;
}

//矩阵与其他元素相减
template<typename T,typename K>
Matrix<T> operator-(K m,Matrix<T>& mat){
    Matrix<T> temp(mat);
    for(size_t i=0;i<mat.getNRow();++i){
        for(size_t j=0;j<mat.getNCol();++j){
            temp(i,j) = m - mat(i,j);
        }
    }
    return temp;
}
template<typename T,typename K>
Matrix<T> operator-(Matrix<T>& mat,K m){
    Matrix<T> temp(mat);
    for(size_t i=0;i<mat.getNRow();++i){
        for(size_t j=0;j<mat.getNCol();++j){
            temp(i,j) = mat(i,j) - m;
        }
    }
    return temp;
}

//矩阵相乘
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& mat){
    Matrix<T> temp(_nRow,mat._nCol,0);
    if(_nCol==mat._nRow){
        for(size_t i=0;i<temp._nRow;++i){
            for(size_t j=0;j<temp._nCol;++j){
                T sum = 0;
                for(size_t k=0;k<_nCol;++k){
                    sum += this->operator()(i,k) * mat(k,j);
                }
                temp(i,j) = sum;
            }
        }
    }else{
        throw std::range_error("error!!!");
    }
    return temp;
}
//矩阵与其他元素相乘
template<typename T,typename K>
Matrix<T> operator*(K m,Matrix<T>& mat){
    Matrix<T> temp(mat);
    for(size_t i=0;i<mat.getNRow();++i){
        for(size_t j=0;j<mat.getNCol();++j){
            temp(i,j) = m * mat(i,j);
        }
    }
    return temp;
}
template<typename T,typename K>
Matrix<T> operator*(Matrix<T>& mat,K m){
    return m*mat;
}

//矩阵除以其他元素
template<typename T>
template<typename K>
Matrix<T> Matrix<T>::operator/(K m){
    Matrix<T> temp(_nRow,_nCol,0);
    for(size_t i=0;i<_nRow;++i){
        for(size_t j=0;j<_nCol;++j){
            temp(i,j) = this->operator()(i,j) / m;
        }
    }
    return temp;
}

//构造函数
template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T init):
_nRow(r), _nCol(c), _t(0)
{
    // new _data
    _data = new T*[r];
    for(size_t i=0;i<r;i++){
        // new _data[i] within loop
        _data[i] = new T[c];
        for(size_t j=0;j<c;j++){
            _data[i][j] = init;
        }
    }
}

//复制构造函数
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat):
_nRow(mat._nRow), _nCol(mat._nCol), _t(mat._t)
{
    // new _data
    _data = new T*[_nRow];
    for(size_t i=0;i<_nRow;++i){
        // new _data[i] within loop
        _data[i] = new T[_nCol];
        for(size_t j=0;j<_nCol;++j){
            _data[i][j] = mat._data[i][j];
        }
    }
}

template<typename T>
void Matrix<T>::swap(Matrix<T>& mat) {
    std::swap(_data, mat._data);
    std::swap(_nRow, mat._nRow);
    std::swap(_nCol, mat._nCol);
    std::swap(_t, mat._t);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> mat)
{
    swap(mat);
    return *this;
}

template<typename T>
size_t Matrix<T>::getNRow() const
{
    // return the number of row
    return _nRow;
}

template<typename T>
size_t Matrix<T>::getNCol() const
{
    // return the number of column
    return _nCol;
}

template<typename T>
bool Matrix<T>::checkRange(size_t r, size_t c) const
{
    // check if r-row and c-column is out of range
    if(r > _nRow){
        return false;
    }
    if(c > _nCol){
        return false;
    }
    return true;
}

template<typename T>
T& Matrix<T>::operator()(size_t r, size_t c) const
{
    // get element in (r,c)
    // remember check first
    // different of _t has different order
    if(!checkRange(r,c)){
        if(r>=_nRow)
            throw std::range_error("row error!!!");
        if(c>=_nCol)
            throw std::range_error("col error!!!");
    }
    if(_t==0){
        return _data[r][c];
    }else{
        return _data[c][r];
    }
}

template<typename T>
Matrix<T> Matrix<T>::subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const
{
    // note the validity of value:rs, re, cs, ce
    // try to use "except" to broadcast the exception
    if(rs>re||cs>ce||(!checkRange(rs+1,cs+1))||(!checkRange(re+1,ce+1))){
        throw std::range_error("error!!!");
    }
    Matrix temp(re-rs+1,ce-cs+1,0);
    for(size_t i=0;i<re-rs+1;i++){
        for(size_t j=0;j<ce-cs+1;j++){
            temp(i,j) = this->operator()(i+rs,j+cs);
        }
    }
    return temp;
}

template<typename T>
std::vector<T> Matrix<T>::getRow(size_t r) const
{
    // get all element in r-row and push it back in a vector
    // remember check range first
    if(!checkRange(r,0)){
        throw std::range_error("row error!!!");
    }
    vector<T> ret;
    for(size_t i=0;i<_nCol;i++){
        ret.push_back(this->operator()(r,i));
    }
    return ret;
}

template<typename T>
std::vector<T> Matrix<T>::getCol(size_t c) const
{
    // get all element in c-column and push it back in a vector
    // remember check range first
    if(!checkRange(0,c)){
        throw std::range_error("col error!!!");
    }
    vector<T> ret;
    for(size_t i=0;i<_nRow;i++){
        ret.push_back(this->operator()(i,c));
    }
    return ret;
}

template<typename T>
bool Matrix<T>::setRow(size_t r, const vector<T>& d) const
{
    // set the element of the r-row
    // remember check range first
    if(!checkRange(r,0)){
        throw std::range_error("row error!!!");
    }
    if(d.size()!=_nCol){
        throw std::range_error("col error!!!");
    }
    for(size_t i=0;i<_nCol;i++){
        _data[r][i] = d[i];
    }
    return true;
}

template<typename T>
bool Matrix<T>::setCol(size_t c, const vector<T>& d) const
{
    // set the element of the c-column
    // remember check range first
    if(!checkRange(0,c)){
        throw std::range_error("col error!!!");
    }
    if(d.size()!=_nRow){
        throw std::range_error("row error!!!");
    }
    for(size_t i=0;i<_nRow;i++){
        _data[i][c] = d[i];
    }
    return true;
}

template<typename T>
Matrix<T>::~Matrix()
{
    // delete _data[i] first
    // then delete _data
    // note the value of _t

    if(_t==0){
        for(size_t i = 0;i<_nRow;++i){
            delete []_data[i];
        }
    }else{
        for(size_t i = 0;i<_nCol;++i){
            delete []_data[i];
        }
    }

    delete []_data;
}

template<typename T>
Matrix<T>& Matrix<T>::transpose()
{
    // change _t
    _t = _t==0?1:0;
    // swap _nRow and _nCol
    size_t temp = _nRow;
    _nRow = _nCol;
    _nCol = temp;
    return *this;
}

template<typename T>
ostream& operator<<(ostream& out, const Matrix<T>& rhs)
{
    for(size_t i=0; i<rhs._nRow; ++i) {
        for(size_t j=0; j<rhs._nCol; ++j) {
            out << rhs(i,j) << "\t";
        }
        out << endl;
    }
    return out;
}
#endif
