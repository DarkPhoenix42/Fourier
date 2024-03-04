#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
template <class T>
bool write_curve_to_file(const string &filename, const vector<T> &vecs)
{
    ofstream out_file;
    out_file.open(filename);
    if (!out_file)
    {
        cerr << "An error occured while trying to create " << filename << endl;
        return false;
    }
    out_file.write((char *)&vecs[0], vecs.size() * sizeof(T));
    out_file.close();
    return true;
}

template <class T>
vector<T> *load_curve_from_file(const string &filename, vector<T> *vecs)
{
    ifstream in_file;
    in_file.open(filename);
    if (!in_file)
    {
        cerr << "An error occured while trying to read " << filename << endl;
        return nullptr;
    }
    while (in_file)
    {
        T current;
        in_file.read((char *)&current, sizeof(T));
        vecs->push_back(current);
    }
    in_file.close();
    return vecs;
}