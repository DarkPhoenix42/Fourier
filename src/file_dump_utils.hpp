#pragma once

#include <iostream>
#include <fstream>
#include <vector>
/**
 * @file file_dump_utils.hpp
 * @brief This file contains utility functions for writing and loading curves from files.
 */

using namespace std;

/**
 * @brief Writes a vector of elements to a file.
 *
 * This function takes a vector of elements and writes them to a file with the specified filename.
 * The elements are written as binary data using the write() function from the ofstream class.
 *
 * @param filename The name of the file to write to.
 * @param vecs The vector of elements to write to the file.
 * @return true if the writing was successful, false otherwise.
 */
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

/**
 * @brief Loads a curve from a file and stores it as a vector containing points.
 *
 * This function reads a file with the specified filename and loads the curve data into a vector.
 * The data is read as binary data using the read() function from the ifstream class.
 *
 * @param filename The name of the file to load the curve from.
 * @param vecs A pointer to the vector to store the loaded curve.
 * @return True if the loading was successful, false otherwise.
 */
template <class T>
bool load_curve_from_file(const string &filename, vector<T> *vecs)
{
    ifstream in_file;
    in_file.open(filename);
    if (!in_file)
    {
        cerr << "An error occured while trying to read " << filename << " !" << endl;
        return false;
    }
    while (in_file)
    {
        T current;
        in_file.read((char *)&current, sizeof(T));
        vecs->push_back(current);
    }
    in_file.close();
    return true;
}