C Small example to differentiate many dependent variables
C  with respect to a single independent variable. 
C  i.e. f: R^1 \to R^n 

      PROGRAM MAIN 
        IMPLICIT NONE
        REAL*8 innum, outcos, outsin, rad 

        REAL*8 getprodsum

        innum = 1.23

        rad = GETPRODSUM(innum, outcos, outsin)

        print *, "Radius = ", rad, " -- cos = ", outcos,  
     + " - sin = ", outsin
      END PROGRAM MAIN

      FUNCTION GETPRODSUM(in, outcos, outsin)
        IMPLICIT NONE
        REAL*8 in, outcos, outsin
        REAL*8 tmp 
        
        REAL*8 getprodsum

        tmp = in*in/2.0+in+1.0

        outcos = cos(tmp);
        outsin = sin(tmp);

        getprodsum = outcos*outcos+outsin*outsin
      END FUNCTION GETPRODSUM
