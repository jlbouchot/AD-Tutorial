      MODULE mymod
        IMPLICIT NONE
        TYPE pt
           INTEGER nb_neighbours
           REAL x,y,z, aff
        END TYPE pt

        TYPE connection
            INTEGER idx1, idx2
            REAL d
            TYPE(connection), POINTER :: next
        END TYPE connection

        contains 

        REAL FUNCTION norm_pts(pt1, pt2) 
          TYPE(pt) pt1, pt2

          norm_pts = (pt1%x-pt2%x)*(pt1%x-pt2%x) + (pt1%y-pt2%y)*(pt1%y-pt2%y) + (pt1%z-pt2%z)*(pt1%z-pt2%z)
        END FUNCTION norm_pts

        REAL FUNCTION compute_matrices(n, sigma, max_val, pts, cnts, A, S)
          INTEGER n
          REAL sigma, max_val

          TYPE(pt), DIMENSION(n) :: pts
          TYPE(connection), POINTER :: cnts
          REAL, DIMENSION(n,n) :: A, S

          INTEGER i, j

          DO i = 1,n
            DO j = i+1,n
              A(i,j) = norm_pts(pts(i), pts(j))
              A(j,i) = A(i,j)
              S(i,j) = EXP(-A(i,j)/sigma)
              S(j,i) = S(i,j)
            END DO
          END DO

          DO WHILE (ASSOCIATED(cnts))
            cnts%d = A(cnts%idx1, cnts%idx2)
            pts(cnts%idx1)%aff = pts(cnts%idx1)%aff*S(cnts%idx1, cnts%idx2)
            pts(cnts%idx2)%aff = pts(cnts%idx1)%aff*S(cnts%idx1, cnts%idx2)
            pts(cnts%idx1)%nb_neighbours = pts(cnts%idx1)%nb_neighbours+1
            pts(cnts%idx2)%nb_neighbours = pts(cnts%idx2)%nb_neighbours+1
            cnts => cnts%next
          END DO

          compute_matrices = 0.0
          DO i=1,n
            compute_matrices = compute_matrices + pts(i)%aff*pts(i)%aff
          END DO

        END FUNCTION compute_matrices
      END MODULE mymod


      PROGRAM MAIN 
      USE mymod 
      IMPLICIT NONE
      
      INTEGER n
      REAL sigma, max_val
      REAL, DIMENSION(5,5) :: A, S
      TYPE(pt), DIMENSION(5) :: pts
      TYPE(connection), POINTER :: cnts, next

      INTEGER i,j
      REAL total_affinity

      sigma = 20.0
      max_val = 10.0
      n = 5

      pts(1)%x = 1.0
      pts(1)%y = 1.0
      pts(1)%z = 1.0
      pts(1)%aff = 1.0
      pts(1)%nb_neighbours = 0

      pts(2)%x = 0.0
      pts(2)%y = 1.0
      pts(2)%z = 1.0
      pts(2)%aff = 1.0
      pts(2)%nb_neighbours = 0

      pts(3)%x = 0.0
      pts(3)%y = 0.0
      pts(3)%z = 1.0
      pts(3)%aff = 1.0
      pts(3)%nb_neighbours = 0

      pts(4)%x = -1.0
      pts(4)%y = -1.0
      pts(4)%z = 1.0
      pts(4)%aff = 1.0
      pts(4)%nb_neighbours = 0

      pts(5)%x = -1.0
      pts(5)%y = -1.0
      pts(5)%z = -1.0
      pts(5)%aff = 1.0
      pts(5)%nb_neighbours = 0

      DO i=1,n
        DO j=1,n
          A(i,j) = 0.0
          S(i,j) = 0.0
        END DO
      END DO

      NULLIFY(cnts)
      NULLIFY(next)

      DO i=1,n
        DO j=i+1,n,i
          ALLOCATE(cnts)
          cnts%idx1 = i
          cnts%idx2 = j
          cnts%d = -1.0
          cnts%next => next
          next => cnts
        END DO
      END DO

      total_affinity = compute_matrices(n, sigma, max_val, pts, cnts, A, S)
      print *, "Total affinity = ", total_affinity

      END PROGRAM MAIN