#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <assert.h>

void testMulScalar2DNoReturn() {
  //printf("creating matrix");
  // MUL
  Matrix2D * m = M_create2D(10,200,2.1);
  int status = M_mul_2d_scalar(m, 2.15,MATRIX_NO_RETURN,NULL);
  assert(status > 0);
  M_print(m);
  M_cleanup(m);

}
void testMulScalar2DReturn(){
  Matrix2D * mm = M_create2D(10,200,2.1);
  Matrix2D * rt = NULL;
  int s = M_mul_2d_scalar(mm, 2.15,MATRIX_RETURN,(void**)&rt);
  assert(s > 0);
  assert(rt != mm);
  assert(rt != NULL);
 // M_print(mm);
  M_print(rt);
  M_cleanup(mm);
  M_cleanup(rt);
}
void testDivScalar2DNoReturn() {
  Matrix2D * m = M_create2D(10,300,40.0);
  int s = M_div_2d_scalar(m, 2.0, MATRIX_NO_RETURN, NULL);
  assert(s > 0);
  M_print(m);
  M_cleanup(m);
}
void testDivScalar2Return() {
  Matrix2D * m = M_create2D(10,300,40.0);
  Matrix2D * rt = NULL;
  int s = M_div_2d_scalar(m, 2.0, MATRIX_RETURN, (void**)&rt);
  assert(s > 0);
  assert(rt != NULL);
  assert(rt->_row == 10);
  assert(rt->_col == 300);
  //M_print(m);
  M_print(rt);
  M_cleanup(m);
  M_cleanup(rt);

}
void testAddScalar2NoReturn() {
  Matrix2D * m = M_create2D(10,300,30.0);
  int s = M_add_2d_scalar(m, 5.5, MATRIX_NO_RETURN, NULL);
  assert(s > 0);
  M_print(m);
  M_cleanup(m);
}

void testAddScalar2Return(){
  Matrix2D * m = M_create2D(10,10, 30.2);
  Matrix2D * rt = NULL;
  int s = M_add_2d_scalar(m, 1.2, MATRIX_RETURN, (void**)&rt);
  assert(rt != NULL);
  assert(s > 0);
  assert(m->_row == rt->_row);
  assert(m->_col == rt->_col);
  M_print(rt);
  M_cleanup(rt);
  M_cleanup(m);
}
void testSubScalar2Return() {
  Matrix2D * m = M_create2D(10,10, 30.2);
  Matrix2D * rt = NULL;
  int s = M_sub_2d_scalar(m, 1.2, MATRIX_RETURN, (void**)&rt);
  assert(rt != NULL);
  assert(s > 0);
  assert(m->_row == rt->_row);
  assert(m->_col == rt->_col);
  M_print(rt);
  M_cleanup(rt);
  M_cleanup(m);
}
void testSubScalar2NoReturn() {
  Matrix2D * m = M_create2D(10,300,30.0);
  int s = M_sub_2d_scalar(m, 5.5, MATRIX_NO_RETURN, NULL);
  assert(s > 0);
  M_print(m);
  M_cleanup(m);
}
void testMatrixCopy() {
  Matrix2D * mm = M_create2D(10,200,2.1);
  Matrix2D * m = (Matrix2D*)M_copy(mm);
  //M_print(m);
  assert(mm != m);
  M_cleanup(mm);
  M_cleanup(m);
  
  Matrix1D * d = M_create1D(100, MATRIX_1D_H,2.1);
  Matrix1D * dcp = (Matrix1D*)M_copy(d);

  assert(d != dcp);
  M_cleanup(d);
  M_cleanup(dcp);
}
void testMatrixMul() {
  Matrix2D * m1 = M_create2D(2,3,0.0);
  Matrix2D * m2 = M_create2D(3,4,0.0);
  m1->_array[0][0] = 2;
  m1->_array[0][1] = 1;
  m1->_array[0][2] = 4; 
  m1->_array[1][0] = 0;
  m1->_array[1][1] = 1;
  m1->_array[1][2] = 1;

  m2->_array[0][0] = 6;
  m2->_array[0][1] = 3;
  m2->_array[0][2] = -1;
  m2->_array[0][3] = 0;
  m2->_array[1][0] = 1;
  m2->_array[1][1] = 1;
  m2->_array[1][2] = 0;
  m2->_array[1][3] = 4;
  m2->_array[2][0] = -2;
  m2->_array[2][1] = 5;
  m2->_array[2][2] = 0;
  m2->_array[2][3] = 2;
  Matrix2D * result = NULL;

  int status=  M_mul_2d(m1,m2,(void**)&result);
  assert(status > 0);
  assert(result != NULL);
  M_print(result);
  M_save(result,"output.txt");
  M_cleanup(m1);
  M_cleanup(result);
  M_cleanup(m2);
  Matrix2D * load = NULL;
  load = (Matrix2D*)M_load("output.txt");
  M_print(load);
  M_cleanup(load);
}
void testAddMatrix() {
  Matrix2D * m1 = M_create2D(2,3,0.0);
  Matrix2D * m2 = M_create2D(2,3,0.0);
  m1->_array[0][0] = 2;
  m1->_array[0][1] = 1;
  m1->_array[0][2] = 4; 
  m1->_array[1][0] = 0;
  m1->_array[1][1] = 1;
  m1->_array[1][2] = 1;

  m2->_array[0][0] = 3;
  m2->_array[0][1] = 4;
  m2->_array[0][2] = 3; 
  m2->_array[1][0] = 2;
  m2->_array[1][1] = 1;
  m2->_array[1][2] = 23.3;

  Matrix2D * result = NULL;
  int status = M_add_2d(m1,m2,(void**)&result);
  assert(status > 0);
  assert(result != NULL);
  printf("matrix1:\n");
  M_print(m1);
  printf("matrix2:\n");
  M_print(m2);
  printf("matrix result:\n");
  M_print(result);
  M_save(result,"output.txt");
  M_cleanup(m1);
  M_cleanup(m2);
  M_cleanup(result);
  Matrix2D * load = NULL;
  load = (Matrix2D*)M_load("output1.txt");
  if (load != NULL) {
    M_print(load);
    M_cleanup(load);
  }
}
void testTranpose() {
  Matrix2D * m = M_create2D(11,2,0.0);
  m->_array[0][0] = 1;
  m->_array[2][0] = 2;
  m->_array[3][0] = 3;
  m->_array[4][0] = 4;
  m->_array[5][0] = 5;
  m->_array[6][0] = 6;
  m->_array[7][0] = 7;
  m->_array[8][0] = 8;
  m->_array[9][0] = 9;
  m->_array[10][0] = 10;


  m->_array[0][1] = 3;
  m->_array[2][1] = 4;
  m->_array[3][1] = 5;
  m->_array[4][1] = 2;
  m->_array[5][1] = 1;
  m->_array[6][1] = 2.3;
  m->_array[7][1] = 4.1;
  m->_array[8][1] = 2;
  m->_array[9][1] = 77;
  m->_array[10][1] = 0;
  printf("before:\n");
  M_print(m);

  Matrix2D * r  = NULL; 
  int status = M_tranpose(m,(void**)&r);
  assert(status > 0);
  assert(r != NULL);
  printf("after:\n");
  M_print(r);

  M_cleanup(m);
  M_cleanup(r);

}


int main() {
  //testMulScalar2DNoReturn();
  //testMulScalar2DReturn();
  //testMatrixCopy();
  //testDivScalar2DNoReturn();
  //testDivScalar2Return();
  //testAddScalar2NoReturn();
  //testAddScalar2Return();
  
  //testSubScalar2Return();
  //testSubScalar2NoReturn();
  //testMatrixMul();
  testAddMatrix();
  //testTranpose();
  
  return 0;
}

