#include "matrix.h"
void * M_create2D(const int& d,const int& row, const int& col, const double& val) {
  return NULL;
}

int M_mul_2d(void * matrix1, void * matrix2, void * matrixResult) {
  return 1;
}
int M_mul_2d_scalar(void * matrix1, const double & val, void * matrixResult) {
  return 1;
}

int M_div_2d(void * matrix1, void * matrix2, void * matrixResult) { 
  return 1;
}
int M_div_2d_scalar(void * matrix1, const double & val, void * matrixResult) {
  return 1;
}

int M_add_2d(void * matrix1, void * matrix2, void * matrixResult ) {
  return 1;
}
int M_add_2d_scalar(void * matrix1, const double& val ,void * matrixResult ) {
  return 1;
}

int M_sub_2d(void * matrix1, void * matrix2, void * matrixResult) {
  return 1;
}
int M_sub_2d_scalar(void * matrix1, const double& val ,void * matrixResult ) {
  return 1;
}

void M_cleanup(void * matrix) {
  if (matrix == NULL) 
    return;
  Matrix_base * m = (Matrix_base*) matrix;
  int d = m->_demension;
  if (d == MATRIX_1D) {

  }
  else if (d == MATRIX_2D) {

  }
  else if (d == MATRIX_3D) {

  }
  else {
#ifndef DEBUG
    assert(0 && "Matrix clean up, please check the demension");
#endif
  }
}
