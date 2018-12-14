#include "matrix.h"
void * M_copy(void * matrix) {
  Matrix_base * base = (Matrix_base*) matrix;
  if (base ->_demension == MATRIX_1D) {
    Matrix1D * m = (Matrix1D*) matrix;
    int size = m->_size;
    int order = m->_order;
    Matrix1D * cp = M_create1D(size,order,0);
    double * cp_array = cp->_array;
    double * array = m->_array;
    for (int i = 0; i < size; i++) {
       cp_array[i] = array[i]; 
    }
    return (void*) cp;

  }
  else if (base->_demension == MATRIX_2D) {
    Matrix2D * m = (Matrix2D*) matrix;
    int row = m->_row;
    int col = m->_col;
    double ** array = m->_array;
    Matrix2D * cp = M_create2D(row, col, 0);
    double ** cp_array = cp->_array;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        cp_array[i][j] = array[i][j]; 
      }
    }
    return (void*) cp;
  }
  else if (base->_demension == MATRIX_3D) {

  }
  return NULL;
}
Matrix1D * M_create1D (int size,int order ,double val)
{
  Matrix1D * m = (Matrix1D*)malloc(sizeof (Matrix1D));
  m->_order = order;
  m->_size = size; 
  m->_array = (double*)malloc(sizeof(double) * size);
  for (int i = 0; i < size; i++){
    m->_array[i] = val;
  }
  m->_base._demension = MATRIX_1D;
  return m;
}
Matrix2D * M_create2D(int row, int col, double val)
{
  if (row <= 0 && col <= 0) {
    assert(0 && "row and col <= 0\n");
    return NULL;
  }
  Matrix2D * m = (Matrix2D*)malloc(sizeof (Matrix2D));
  m->_base._demension = MATRIX_2D;
  m->_array = (double**) malloc(row * sizeof(double*));
  m->_row = row;
  m->_col = col;
  for (int i = 0; i < row; i++) {
    m->_array[i] = (double*) malloc(col * sizeof(double));
  }
  for (int i = 0; i < row; i ++) {
    for (int j = 0; j < col; j++) {
      m->_array[i][j] = val;
    }
  }
  return m;
}

int M_mul_2d(void * matrix1, void * matrix2, int rt , void ** matrixResult) 
{
  return 1;
}
// If matrixResult is null then, matrix1 will be modified otherwise, it will
// return to matrixResult
int M_mul_2d_scalar(void * matrix1, double val, int rt , void ** matrixResult) 
{
  Matrix_base * base = (Matrix_base*) matrix1; 
  if (rt == MATRIX_NO_RETURN) {
    if (base->_demension == MATRIX_1D) {
      Matrix1D * m = (Matrix1D*) matrix1;
      int size = m->_size; 
      for (int i = 0; i < size; i++) 
        m->_array[i] *= val;
      return MATRIX_2D_MUL_SCALAR_OK;
    }
    else if (base->_demension == MATRIX_2D) {
      Matrix2D * m = (Matrix2D*) matrix1; 
      int row = m->_row;
      int col = m->_col;
      for (int i =0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          m->_array[i][j] *= val;
        }
      }
      return MATRIX_2D_MUL_SCALAR_OK;
    }
  }
  else {
    void * newMatrix = M_copy(matrix1);
    Matrix_base * base = (Matrix_base*) newMatrix;
    if (base->_demension == MATRIX_1D) {
      Matrix1D * m = (Matrix1D*) newMatrix;
      int size = m->_size; 
      for (int i = 0; i < size; i++) 
        m->_array[i] *= val;
      *matrixResult = newMatrix;

      return MATRIX_2D_MUL_SCALAR_OK;
    }
    else if (base->_demension == MATRIX_2D) {
      Matrix2D * m = (Matrix2D*) newMatrix;
      int row = m->_row;
      int col = m->_col;
      for (int i =0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          m->_array[i][j] *= val;
        }
      }
      *matrixResult = newMatrix;
      //printf("matrix address: %p\n", newMatrix);
      return MATRIX_2D_MUL_SCALAR_OK;
    }
  }
  return MATRIX_2D_MUL_SCALAR_FAILED;
}

int M_div_2d(void * matrix1, void * matrix2, int rt, void ** matrixResult)  
{
  return 1;
}
int M_div_2d_scalar(void * matrix1, double val, int rt, void ** matrixResult)  
{
  Matrix_base * base = (Matrix_base*) matrix1; 
  if (rt == MATRIX_NO_RETURN) {
    if (base->_demension == MATRIX_1D) {
      Matrix1D * m = (Matrix1D*) matrix1;
      int size = m->_size; 
      for (int i = 0; i < size; i++) 
        m->_array[i] /= val;
      return MATRIX_2D_DIV_SCALAR_OK;
    }
    else if (base->_demension == MATRIX_2D) {
      Matrix2D * m = (Matrix2D*) matrix1; 
      int row = m->_row;
      int col = m->_col;
      for (int i =0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          m->_array[i][j] /= val;
        }
      }
      return MATRIX_2D_DIV_SCALAR_OK;
    }
  }
  else {
    void * newMatrix = M_copy(matrix1);
    Matrix_base * base = (Matrix_base*) newMatrix;
    if (base->_demension == MATRIX_1D) {
      Matrix1D * m = (Matrix1D*) newMatrix;
      int size = m->_size; 
      for (int i = 0; i < size; i++) 
        m->_array[i] /= val;
      *matrixResult = newMatrix;

      return MATRIX_2D_DIV_SCALAR_OK;
    }
    else if (base->_demension == MATRIX_2D) {
      Matrix2D * m = (Matrix2D*) newMatrix;
      int row = m->_row;
      int col = m->_col;
      for (int i =0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          m->_array[i][j] /= val;
        }
      }
      *matrixResult = newMatrix;
      return MATRIX_2D_DIV_SCALAR_OK;
    }
  }
  return MATRIX_2D_DIV_SCALAR_FAILED;
}

int M_add_2d(void * matrix1, void * matrix2, int rt, void ** matrixResult)
{
  return 1;
}
int M_add_2d_scalar(void * matrix1, double val , int rt , void ** matrixResult)  
{
  Matrix_base * base = (Matrix_base*) matrix1; 
  if (rt == MATRIX_NO_RETURN) {
    if (base->_demension == MATRIX_1D) {
      Matrix1D * m = (Matrix1D*) matrix1;
      int size = m->_size; 
      for (int i = 0; i < size; i++) 
        m->_array[i] += val;
      return MATRIX_2D_ADD_SCALAR_OK;
    }
    else if (base->_demension == MATRIX_2D) {
      Matrix2D * m = (Matrix2D*) matrix1; 
      int row = m->_row;
      int col = m->_col;
      for (int i =0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          m->_array[i][j] += val;
        }
      }
      return MATRIX_2D_ADD_SCALAR_OK;
    }
  }
  else {
    void * newMatrix = M_copy(matrix1);
    Matrix_base * base = (Matrix_base*) newMatrix;
    if (base->_demension == MATRIX_1D) {
      Matrix1D * m = (Matrix1D*) newMatrix;
      int size = m->_size; 
      for (int i = 0; i < size; i++) 
        m->_array[i] += val;
      *matrixResult = newMatrix;

      return MATRIX_2D_ADD_SCALAR_OK;
    }
    else if (base->_demension == MATRIX_2D) {
      Matrix2D * m = (Matrix2D*) newMatrix;
      int row = m->_row;
      int col = m->_col;
      for (int i =0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          m->_array[i][j] += val;
        }
      }
      *matrixResult = newMatrix;
      return MATRIX_2D_ADD_SCALAR_OK;
    }
  }
  return MATRIX_2D_ADD_SCALAR_FAILED;
}

int M_sub_2d(void * matrix1, void * matrix2, int rt, void ** matrixResult)  
{
  return 1;
}
int M_sub_2d_scalar(void * matrix1, double val , int rt , void ** matrixResult) 
{
  int r = M_add_2d_scalar(matrix1, -val, rt, matrixResult);
  if (r == MATRIX_2D_ADD_SCALAR_OK) 
      return MATRIX_2D_SUB_SCALAR_OK;
  else 
      return MATRIX_2D_SUB_SCALAR_FAILED;
  
}

void M_cleanup(void * matrix) 
{
  Matrix_base * base = (Matrix_base*)matrix;
  int d = base->_demension;
  if (d == MATRIX_1D) { 
    Matrix1D * m = (Matrix1D*) matrix;
    free(m->_array);
    free(m);
    m = NULL;
  }
  else if (d == MATRIX_2D) {
    Matrix2D * m = (Matrix2D*) matrix;
    int row = m->_row;
    for (int i = 0; i < row; i++) {
      double * col = m->_array[i];
      free(col);
    }
    free(m->_array);
    free(m);
    m = NULL;
  }
  else if (d == MATRIX_3D) {

  }
}

void M_print(void * matrix)
{
  Matrix_base * base = (Matrix_base*) matrix;
  int d = base->_demension;
  if (d == MATRIX_1D){
    Matrix1D * m = (Matrix1D*) matrix;
    int size = m->_size;
    for (int i = 0; i < size; i++) {
      printf("%.3f ", m->_array[i]);
    }

  }
  else if (d == MATRIX_2D) {
    Matrix2D * m = (Matrix2D*) matrix; 
    int row = m->_row;
    int col = m->_col;
    double ** array = m->_array;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        printf("%lf ",array[i][j]);
      }
      printf("\n");
    }

  }
  else if (d == MATRIX_3D) {

  }
}
