Matrix.h:
 
// before including user defined MATRIX_PREFIX and MATRIX_T
 
#define MATRIX_NAME(name) MATRIX_PREFIX##name // concatenate
 
typedef struct MATRIX_NAME(Matrix) {
  MATRIX_T v[3][3];
};
 
MATRIX_NAME(Matrix) MATRIX_NAME(MatrixAdd) (MATRIX_NAME(Matrix) a, MATRIX_NAME(Matrix) b)
{
  MATRIX_NAME(Matrix) result;
  // compute it...
  return result;
}
 
#undef MATRIX_PREFIX
#undef MATRIX_
#undef MATRIX_NAME
 
test.h:
 
#define MATRIX_PREFIX Int_
#define MATRIX_T int
#include "Matrix.h"
 
void func (void)
{
  IntMatrix a;
  IntMatrix b;
    ...
    IntMatrix c = IntMatrixAdd(a, b);
}
