/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef DATAPOINT_H
#define DATAPOINT_H
#include <map>
#include <vector>
#include <iostream>
namespace usermodel{

enum class data_type{
    text_data = 0,
    vector_data = 1,
    sparse_vector = 2 
};

class DataPoint {
    public:
        DataPoint(const DataPoint &other_point);
        DataPoint(const std::string &data);
        DataPoint(const std::vector<float> &data);
        DataPoint(const std::map<unsigned,float> &data, int ndims);
        ~DataPoint();
        friend float operator * (const DataPoint a, const DataPoint b);
        // friend 
        data_type get_type();
        int get_dims();
        data_type type;
        int n_dims;
        std::string data_text;
        std::vector<float> data_vector;
        std::map<unsigned,float> data_sparse;
};

// float inner_product(DataPoint a, DataPoint b);
// float sum(DataPoint a, DataPoint b);

}

#endif