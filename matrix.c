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
#ifndef DEBUG
    assert(0 && "row and col <= 0\n");
#endif
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

int M_mul_2d(void * matrix1, void * matrix2, void ** matrixResult) 
{
  if (matrix1 == NULL || matrix2 == NULL){
    printf("matrix shouldnt NULL");
    return MATRIX_NULL_PTR;
  }
  Matrix_base * base1 = (Matrix_base*) matrix1;
  Matrix_base * base2 = (Matrix_base*) matrix2;
  if (base1->_demension == base2->_demension && base1->_demension == MATRIX_2D) {
    Matrix2D * m1 = (Matrix2D*) matrix1;
    Matrix2D * m2 = (Matrix2D*) matrix2;
    int row1 = m1->_row;
    int col1 = m1->_col;
    int row2 = m2->_row;
    int col2 = m2->_col;
    if (col1 != row2) {
      printf("row matrix1 should be equal col matrix2");
      return MATRIX_SIZE_FAILED;
    }
    // create new Matrix 
    double ** m1Array = m1->_array;
    double ** m2Array = m2->_array;
    Matrix2D * newMatrix = M_create2D(row1,col2,0);
    double ** newArray = newMatrix->_array;
    for (int i = 0; i < row1; i++) {
      for (int j = 0; j < col2; j++) {
        double sum = 0;
        for (int k = 0; k < row2; k++) {
          double mulVal = m1Array[i][k] * m2Array[k][j];
          sum += mulVal;
        }
        newArray[i][j] = sum;
      }
    }
    *matrixResult = newMatrix;
    return MATRIX_2D_MUL_OK;
  }

  printf("M_mul_2d matrices demension not match");
  return MATRIX_DEMENSION_NOT_MATCH;

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

int M_div_2d(void * matrix1, void * matrix2 , void ** matrixResult)  
{
  if (matrix1 == NULL || matrix2 == NULL) {
    printf("matrix inputs should not be null\n");
    return MATRIX_NULL_PTR;
  }
    
  Matrix_base * base = (Matrix_base*) matrix1; 
  Matrix_base * base1 = (Matrix_base*) matrix2;
  if (base->_demension != base1->_demension || base->_demension != MATRIX_2D) {
    printf("matrix add, the demension should be the same\n");
    return MATRIX_DEMENSION_NOT_MATCH;
  }

  Matrix2D * m1 = (Matrix2D*) matrix1;
  Matrix2D *m2 = (Matrix2D*) matrix2;
  
  int m1Row = m1->_row;
  int m1Col = m1->_col;
  int m2Row = m2->_row;
  int m2Col = m2->_col;
  if (m1Row != m2Row || m2Col != m1Col) {
    printf("both matrix should be same size\n");
    return MATRIX_SIZE_FAILED;
  }
  double ** m1Array = m1->_array;
  double ** m2Array = m2->_array;
  Matrix2D * result = M_create2D(m1Row, m1Col, 0.0);
  double ** rArray = result->_array;
  for (int i = 0; i < m1Row; i++) {
    for (int j = 0; j < m1Col; j++) {
      rArray[i][j] = m1Array[i][j] / m2Array[i][j];
    }
  }
  *matrixResult = result;
  return MATRIX_2D_DIV_OK;
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

int M_add_2d(void * matrix1, void * matrix2, void ** matrixResult)
{
  if (matrix1 == NULL || matrix2 == NULL) {
    printf("matrix inputs should not be null\n");
    return MATRIX_NULL_PTR;
  }
    
  Matrix_base * base = (Matrix_base*) matrix1; 
  Matrix_base * base1 = (Matrix_base*) matrix2;
  if (base->_demension != base1->_demension || base->_demension != MATRIX_2D) {
    printf("matrix add, the demension should be the same\n");
    return MATRIX_DEMENSION_NOT_MATCH;
  }

  Matrix2D * m1 = (Matrix2D*) matrix1;
  Matrix2D *m2 = (Matrix2D*) matrix2;
  
  int m1Row = m1->_row;
  int m1Col = m1->_col;
  int m2Row = m2->_row;
  int m2Col = m2->_col;
  if (m1Row != m2Row || m2Col != m1Col) {
    printf("both matrix should be same size\n");
    return MATRIX_SIZE_FAILED;
  }
  double ** m1Array = m1->_array;
  double ** m2Array = m2->_array;
  Matrix2D * result = M_create2D(m1Row, m1Col, 0.0);
  double ** rArray = result->_array;
  for (int i = 0; i < m1Row; i++) {
    for (int j = 0; j < m1Col; j++) {
      rArray[i][j] = m1Array[i][j] + m2Array[i][j];
    }
  }
  *matrixResult = result;
  return MATRIX_2D_ADD_OK;

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

int M_sub_2d(void * matrix1, void * matrix2 , void ** matrixResult)  
{
  if (matrix1 == NULL || matrix2 == NULL) {
    printf("matrix inputs should not be null\n");
    return MATRIX_NULL_PTR;
  }
    
  Matrix_base * base = (Matrix_base*) matrix1; 
  Matrix_base * base1 = (Matrix_base*) matrix2;
  if (base->_demension != base1->_demension || base->_demension != MATRIX_2D) {
    printf("matrix sub, the demension should be the same\n");
    return MATRIX_DEMENSION_NOT_MATCH;
  }

  Matrix2D * m1 = (Matrix2D*) matrix1;
  Matrix2D *m2 = (Matrix2D*) matrix2;
  
  int m1Row = m1->_row;
  int m1Col = m1->_col;
  int m2Row = m2->_row;
  int m2Col = m2->_col;
  if (m1Row != m2Row || m2Col != m1Col) {
    printf("both matrix should be same size\n");
    return MATRIX_SIZE_FAILED;
  }
  double ** m1Array = m1->_array;
  double ** m2Array = m2->_array;
  Matrix2D * result = M_create2D(m1Row, m1Col, 0.0);
  double ** rArray = result->_array;
  for (int i = 0; i < m1Row; i++) {
    for (int j = 0; j < m1Col; j++) {
      rArray[i][j] = m1Array[i][j] - m2Array[i][j];
    }
  }
  *matrixResult = result;
  return MATRIX_2D_SUB_OK;
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

int M_tranpose(void * matrix1, void ** matrixResult) 
{
  if (matrix1 == NULL) {
    printf("matrix should not be null\n");
    return MATRIX_NULL_PTR;
  }
  Matrix_base * base = (Matrix_base*) matrix1;
  if (base->_demension == MATRIX_2D) {
    Matrix2D * m = (Matrix2D*) matrix1;
    int row = m->_row;
    int col = m->_col;
    Matrix2D * result = M_create2D(col,row, 0.0);
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < row; j++) {
       result->_array[i][j] = m->_array[j][i];
      }
    }
    *matrixResult = result;
    return MATRIX_TRANPOSE_OK;
  }
  return MATRIX_TRANPOSE_FAILED;
}

void M_save(void * matrix, const char* filePath)
{
  if (matrix == NULL) {
    printf("matrix should not be null\n");
    return;
  }
  FILE * fp;
  if ((fp = fopen(filePath, "w")) != NULL) {
    
  }
  else {
    printf("cant create file to write\n");
  }
  Matrix_base * base = (Matrix_base*) matrix;
  // write demension
  fprintf(fp, "%d\t", base->_demension);
  if (base->_demension == MATRIX_2D){
    Matrix2D * m = (Matrix2D*) matrix;
    int row = m->_row;
    int col = m->_col;
  fprintf(fp, "%d\t%d\n", row,col);
    double ** array = m->_array;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        double val = array[i][j];
        fprintf(fp,"%lf", val);
        if (j != col - 1) 
          fprintf(fp,"\t");
        else 
          fprintf(fp,"\n");
      }
    }
  }

  fclose(fp);
}

void * M_load(const char* filePath) 
{
  FILE * fp;
  if((fp = fopen(filePath,"r")) != NULL) {
    int demension = 0;
    fscanf(fp,"%d\t", &demension);
    int row = -1;
    int col = -1;
    fscanf(fp,"%d\t", &row);
    fscanf(fp, "%d", &col);
    if (row == -1 || col == -1) {
      printf("file is not in correct format\n");
      fclose(fp);
      return NULL;
    }
    double num = 0.0;
    Matrix2D * m = M_create2D(row,col, 0.0);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        fscanf(fp,"%lf", &num);
        m->_array[i][j] = num;
      }
    }
    fclose(fp);
    return m;
  }
  else {
    printf("file is not exist\n");
    return NULL;
  }
  return NULL;
}
