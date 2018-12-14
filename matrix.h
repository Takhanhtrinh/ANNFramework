#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
//base class for matrix
#define MATRIX_1D 1 
#define MATRIX_2D 2
#define MATRIX_3D 3
#define MATRIX_1D_V 1
#define MATRIX_1D_H 2

#define MATRIX_2D_MUL_SCALAR_OK  20
#define MATRIX_2D_MUL_SCALAR_FAILED  -20

#define MATRIX_2D_DIV_SCALAR_OK 21
#define MATRIX_2D_DIV_SCALAR_FAILED -21

#define MATRIX_2D_ADD_SCALAR_OK 22 
#define MATRIX_2D_ADD_SCALAR_FAILED -22

#define MATRIX_2D_SUB_SCALAR_OK 23
#define MATRIX_2D_SUB_SCALAR_FAILED -23

#define MATRIX_NO_RETURN -1
#define MATRIX_RETURN 1
typedef struct {
  int _demension; // demension
} Matrix_base;

typedef struct {
  Matrix_base _base; 
  double * _array; 
  int _size;
  int _order;
} Matrix1D;

typedef struct {
  Matrix_base _base;
  double ** _array;
  int _row;
  int _col;
} Matrix2D ;

void * M_copy(void * matrix);

Matrix1D * M_create1D (int size,int order ,double val);
Matrix2D * M_create2D (int row, int col, double val);

int M_mul_2d(void * matrix1, void * matrix2,int rt,  void ** matrixResult);
int M_mul_2d_scalar(void * matrix1, double val,int rt,  void ** matrixResult);

int M_div_2d(void * matrix1, void * matrix2,int rt, void ** matrixResult);
int M_div_2d_scalar(void * matrix1, double val,int rt, void ** matrixResult);

int M_add_2d(void * matrix1, void * matrix2,int rt, void ** matrixResult);
int M_add_2d_scalar(void * matrix1, double val ,int rt,void ** matrixResult);

int M_sub_2d(void * matrix1, void * matrix2, int rt , void ** matrixResult);
int M_sub_2d_scalar(void * matrix1, double val ,int rt, void ** matrixResult);

void M_cleanup(void * matrix);

void M_print(void * matrix);

void M_save(const char* filePath);

void * M_load(const char* filePath);

#endif
