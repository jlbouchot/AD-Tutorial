      PROGRAM MAIN
        IMPLICIT NONE 
        REAL*4 res,a,b,c
        REAL*4 x
        REAL quad_fun

C Some parameters, just because we can
        a = 2.0;
        b = -1.05;
        c = 0.5;

        x = 1.0;
        res = quad_fun(x, a, b, c);
        print *, "Res = ", res
      END PROGRAM MAIN

      FUNCTION QUAD_FUN(x, a, b, c)
        IMPLICIT NONE
        REAL x,a,b,c
        REAL quad_fun

        quad_fun = a*x*x+b*x+c
      END FUNCTION QUAD_FUN