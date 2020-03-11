#include "data_point.h"
#include <stdexcept>
#include <limits>

namespace usermodel{
DataPoint::DataPoint(const DataPoint &other_point)=default;
DataPoint::~DataPoint() = default;    
DataPoint::DataPoint(const std::string &data){
    type = DataType::text_data;
    data_text = data;
    n_dims=0;
}

DataPoint::DataPoint(const std::vector<float> &data){
    type = DataType::vector_data;
    data_vector = data;
    n_dims = data.size();
}

DataPoint::DataPoint(const std::map<unsigned,float> &data, int dims){
    type = DataType::sparse_vector;
    n_dims=dims;
    data_sparse = data;
}

float operator * (const DataPoint a, const DataPoint b){
    if ( (a.n_dims==0)||(b.n_dims==0)){
        return std::numeric_limits<double>::quiet_NaN();
    }
        
    if (a.n_dims!=b.n_dims){
        return std::numeric_limits<double>::quiet_NaN();
    }

    float rtn = 0.0;
    if( (a.type == DataType::vector_data) && (b.type==DataType::vector_data)){
        for (unsigned i = 0; i < a.data_vector.size(); i++)
            rtn+= a.data_vector[i]*b.data_vector[i];
    }else if ((a.type==DataType::vector_data)&&(b.type==DataType::sparse_vector)){
        for (auto kv : b.data_sparse)
            rtn += a.data_vector[kv.first] * kv.second;
    }else if ((a.type==DataType::sparse_vector)&&(b.type==DataType::vector_data)){
        for (auto kv : a.data_sparse)
            rtn += b.data_vector[kv.first] * kv.second;
    }else{
        for (auto kv : a.data_sparse)
            if ( b.data_sparse.count(kv.first)>0 ){
                auto tmp = b.data_sparse.at(kv.first);
                rtn+=kv.second*tmp; 
            }
    }
    return rtn;
}

}