#ifndef HDF5EXPORT_H_
#define HDF5EXPORT_H_

#include <array>
#include "control.h"

using namespace H5;
using namespace std;

int write_data_to_hdf5(H5std_string FILE_NAME, H5std_string DATASETNAME,  double* dataext, int cols);
int write_data_to_hdf5(H5std_string FILE_NAME, H5std_string DATASETNAME,  double dataext_scalar);
int init_hdf5_file(H5std_string FILE_NAME, int cols, string* dataset_name_list, int dataset_name_length);


#endif /* HDF5EXPORT_H_ */
