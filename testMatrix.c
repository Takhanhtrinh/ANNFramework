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


int main() {
  //testMulScalar2DNoReturn();
  //testMulScalar2DReturn();
  //testMatrixCopy();
  //testDivScalar2DNoReturn();
  //testDivScalar2Return();
  //testAddScalar2NoReturn();
  //testAddScalar2Return();
  
  //testSubScalar2Return();
  testSubScalar2NoReturn();
  
  return 0;
}

