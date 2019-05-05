#include <QCoreApplication>
#include <iostream>
#include "fft.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication b(argc, argv);

    vector<double> a;
    a.push_back(1.);
    a.push_back(2.);
    a.push_back(3.);
    a.push_back(4.);
    a.push_back(5.);
    vector<complex<double> > r = fft(a, 3);
    for(size_t i=0; i<r.size(); ++i)
        cout << r.at(i) << "\t";
    cout << endl;

//    cout<<calcN(5);

    return b.exec();
}
