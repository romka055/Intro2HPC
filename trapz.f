      PROGRAM trapz
          IMPLICIT none
          CHARACTER(100) :: num1char
          INTEGER :: n
          REAL :: myfunn, myfunn1, trap, nreal
          INTEGER  :: i
 
        IF(COMMAND_ARGUMENT_COUNT().NE.1) THEN
           WRITE(*,*)'ERROR, Enter N'
           STOP
        ENDIF

          CALL GET_COMMAND_ARGUMENT(1,num1char)   !get N
        READ(num1char,*)nreal                     !then, convert them to REALs
        IF ((nreal .NE. floor(nreal)).OR.(nreal.LT.1)) THEN
          WRITE(*,*)'ERROR, Enter N as a positive integer'
          STOP
        ENDIF

        !WRITE(*,*)'N is ',nreal

        trap = 0.0
        n = INT(nreal)
        myfunn=evalmyfun(0.0)
        DO i= 1,n
           myfunn1=evalmyfun(REAL(i)/REAL(n))
           trap = trap + (myfunn+myfunn1)/2.0/n
           myfunn=myfunn1
        ENDDO 

        WRITE(*,*)'The result is:',trap

        CONTAINS

           REAL FUNCTION evalmyfun(x)
                IMPLICIT none
                REAL :: x
                evalmyfun = 4.0/(1+x*x)
           END FUNCTION evalmyfun
        
      END PROGRAM trapz
