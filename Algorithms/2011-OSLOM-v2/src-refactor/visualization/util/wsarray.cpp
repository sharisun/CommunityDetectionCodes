//
// Created by cheyulin on 3/20/17.
//

#include "wsarray.h"

wsarray::wsarray(int a) {
    position = 0;
    _size_ = a;
    l = new int[_size_];
    w = new double[_size_];
}

wsarray::~wsarray() {
    delete[] l;
    l = NULL;
    delete[] w;
    w = NULL;
}

pair<int, double> wsarray::posweightof(int x) {
    int i = find(x);
    if (i == -1)
        return (make_pair(-1, 0));
    return (make_pair(i, w[i]));
};

int wsarray::find(int a) {
    int one = 0;
    int two = position - 1;
    if (position == 0)
        return -1;
    if (a < l[one] || a > l[two])
        return -1;
    if (a == l[one])
        return one;
    if (a == l[two])
        return two;
    while (two - one > 1) {
        int middle = (two - one) / 2 + one;
        if (a == l[middle])
            return middle;
        if (a > l[middle])
            one = middle;
        else
            two = middle;
    }
    return -1;
}

void wsarray::push_back(int a, double b) {
    l[position] = a;
    w[position++] = b;
}

bool wsarray::erase(int y) {
    int pos_of_y = find(y);
    if (pos_of_y == -1)
        return false;
    //cout<<"you want to erase "<<y<<endl;
    _size_--;
    position = _size_;
    //cout<<"_size_ "<<_size_<<endl;
    int ll[_size_];
    double ww[_size_];
    int poi = 0;
    for (int i = 0; i < _size_ + 1; i++)
        if (l[i] != y) {
            ll[poi] = l[i];
            ww[poi] = w[i];
            poi++;
        }
    delete[] l;
    l = NULL;
    delete[] w;
    w = NULL;
    l = new int[_size_];
    w = new double[_size_];
    for (int i = 0; i < _size_; i++) {
        l[i] = ll[i];
        w[i] = ww[i];
    }
    return true;
}

void wsarray::freeze() {
    map<int, double> M;
    for (int i = 0; i < position; i++) {
        /*	//this is to sum up multiple entries
        map<int, double>::iterator itf=M.find(l[i]);
        if (itf==M.end())
            M.insert(make_pair(l[i], w[i]));
        else
            itf->second+=w[i];
        //*/
        M.insert(make_pair(l[i], w[i]));
    }
    if (_size_ != M.size()) {
        delete[] l;
        l = NULL;
        delete[] w;
        w = NULL;
        _size_ = M.size();
        position = M.size();
        l = new int[_size_];
        w = new double[_size_];
    }
    int poi = 0;
    for (map<int, double>::iterator itm = M.begin(); itm != M.end(); itm++) {
        l[poi] = itm->first;
        w[poi] = itm->second;
        poi++;
    }
}

void prints(wsarray &a) {
    for (int i = 0; i < a.size(); i++)
        cout << a.l[i] << "\t" << a.w[i] << endl;
    cout << endl;
}

void prints(wsarray &a, ostream &out) {
    for (int i = 0; i < a.size(); i++)
        cout << a.l[i] << "\t" << a.w[i] << endl;
    out << endl;
}

void prints(wsarray *a, ostream &out) {
    for (int i = 0; i < a->size(); i++)
        cout << a->l[i] << "\t" << a->w[i] << endl;
    out << endl;
}

void prints(wsarray *a) {
    prints(a, cout);
}