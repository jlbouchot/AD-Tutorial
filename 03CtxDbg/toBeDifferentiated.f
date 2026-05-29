
      PROGRAM MAIN 
        IMPLICIT NONE
        REAL*8 innum, outcos, outsin, rad 

        REAL*8 getprodsum

        rad = GETPRODSUM(innum, outcos, outsin)

        print *, "Radius = ", rad, " -- cos = ", outcos,  
     + " - sin = ", outsin
      END PROGRAM MAIN

      FUNCTION GETPRODSUM(in, outcos, outsin)
        IMPLICIT NONE
        REAL*8 in, outcos, outsin
        REAL*8 tmp 
        
        REAL*8 getprodsum
        REAL*8 GETSOMETMPVALUE

        in = 1.23

        tmp = GETSOMETMPVALUE(in)

        outcos = cos(tmp);
        outsin = sin(tmp);

        getprodsum = outcos*outcos+outsin*outsin
      END FUNCTION GETPRODSUM

      FUNCTION GETSOMETMPVALUE(in)
        IMPLICIT NONE
        REAL*8 in
        REAL*8 getsometmpvalue

        getsometmpvalue = in*in/2.0+in+1.0

      END FUNCTION GETSOMETMPVALUE