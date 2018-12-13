#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
//base class for matrix
#define MATRIX_1D 1 
#define MATRIX_2D 2
#define MATRIX_3D 3
typedef struct {
  int _demension; // demension
} Matrix_base;

typedef struct {
  Matrix_base _base;
  double ** _array;
  int _row;
  int _col;
} Matrix2d ;

void * M_create(const int& d,const int& row, const int& col, const double& val = 0);

int M_mul_2d(void * matrix1, void * matrix2, void * matrixResult = NULL);
int M_mul_2d_scalar(void * matrix1, const double & val, void * matrixResult = NULL);

int M_div_2d(void * matrix1, void * matrix2, void * matrixResult = NULL);
int M_div_2d_scalar(void * matrix1, const double & val, void * matrixResult = NULL);

int M_add_2d(void * matrix1, void * matrix2, void * matrixResult = NULL);
int M_add_2d_scalar(void * matrix1, const double& val ,void * matrixResult = NULL);

int M_sub_2d(void * matrix1, void * matrix2, void * matrixResult = NULL);
int M_sub_2d_scalar(void * matrix1, const double& val ,void * matrixResult = NULL);

void M_cleanup(void * matrix = NULL);

#endif
