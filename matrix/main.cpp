#include <QCoreApplication>
#include <iostream>
#include "matrix.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "------------------------------------" << endl;
    cout << "test of constructor:" << endl;
    cout << "------------------------------------" << endl;
    Matrix<double> m(5,4,7.9);
    cout << "*******    m:\n" << m << endl;
    Matrix<double> mC(m);
    cout << "*******    mC:\n" << mC << endl;
    Matrix<double> mE = m;
    cout << "*******    mE:\n" << mE << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator()" << endl;
    cout << "------------------------------------" << endl;
    mC(1,2) = 2;
    cout << "*******  mC:\n" << mC << endl;
    mE(2,0) = 7;
    cout << "*******  mE:\n" << mE << endl;
    cout << "*******  m:\n" << m << endl;
    cout << "------------------------------------" << endl;
    cout << "test of transpose()" << endl;
    cout << "------------------------------------" << endl;
    cout << "*******  transpose mE:\n" << mE.transpose() << endl;
    cout << "------------------------------------" << endl;
    cout << "test of get and set" << endl;
    cout << "------------------------------------" << endl;
    vector<double> vd = mE.getRow(0);
    cout << "get the first row of mE:" << endl;
    for(size_t i = 0; i<vd.size(); ++i)
        cout << vd.at(i) << "  **  ";
    cout << endl;
    cout << "set the last column of mC:" << endl;
    vd.at(1) = -3.3;
    mC.setCol(3, vd);
    cout << "*******  mC:\n" << mC << endl;
    cout << "------------------------------------" << endl;
    cout << "test of subMatrix" << endl;
    cout << "------------------------------------" << endl;
    cout << "*******  mC.subMatrix(1,3,1,3):\n" << mC.subMatrix(1,3,1,3) << endl;

    cout << "------------------------------------" << endl;
    cout << "test of operator+" << endl;
    cout << "------------------------------------" << endl;
    mC(3,1) = -10;
    cout << "*******  m:\n" << m << endl;
    cout << "*******  mC:\n" << mC << endl;
    cout << "*******  m+mC:\n" << m+mC << endl;
    cout << "*******  9+mC:\n" << 9+mC << endl;
    cout << "*******  mC+9:\n" << mC+9 << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator-" << endl;
    cout << "------------------------------------" << endl;
    mC(3,2) = 4;
    cout << "*******  m:\n" << m << endl;
    cout << "*******  mC:\n" << mC << endl;
    cout << "*******  m-mC:\n" << m-mC << endl;
    cout << "*******  10-mC:\n" << 10-mC << endl;
    cout << "*******  mC-10:\n" << mC-10 << endl;
    cout << "test of operator*" << endl;
    cout << "------------------------------------" << endl;
    cout << "*******  mE\n" << mE<< endl;
    cout << "*******  mC:\n" << mC << endl;
    cout << "*******  mE*mC:\n" << mE*mC << endl;
    cout << "*******  10*mC:\n" << 10*mC << endl;
    cout << "*******  mC*10:\n" << mC*10 << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator/" << endl;
    cout << "------------------------------------" << endl;
    cout << "*******  mC:\n" << mC << endl;
    cout << "*******  mC/2:\n" << mC/2 << endl;

    return a.exec();
}
