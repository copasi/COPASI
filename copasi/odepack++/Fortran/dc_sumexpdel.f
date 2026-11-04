C ******************************************
C     VERSION OF March 5, 2024     
C ******************************************
C
      SUBROUTINE DECOMR(N,FJAC,LDJAC,FMAS,LDMAS,MLMAS,MUMAS,
     &            M1,M2,NM1,FAC1,E1,LDE1,IP1,IER,IJOB,CALHES,IPHES)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION FJAC(LDJAC,N),FMAS(LDMAS,NM1),E1(LDE1,NM1),
     &          IP1(NM1),IPHES(N)
      LOGICAL CALHES
      COMMON/LINAL/MLE,MUE,MBJAC,MBB,MDIAG,MDIFF,MBDIAG
C
      GOTO (1,2,3,2,55,55,55,55,55,55,2,2,55,55,55), IJOB
C
C -----------------------------------------------------------
C
   1  CONTINUE
C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
      DO J=1,N
         DO  I=1,N
            E1(I,J)=-FJAC(I,J)
         END DO
         E1(J,J)=E1(J,J)+FAC1
      END DO
      CALL DEC (N,LDE1,E1,IP1,IER)
      RETURN
C
C -----------------------------------------------------------
C
   3  CONTINUE
C ---  B IS A DIAGONAL MATRIX, JACOBIAN A FULL MATRIX
      DO J=1,N
         DO I=1,N
            E1(I,J)=-FJAC(I,J)
         END DO
         E1(J,J)=E1(J,J)+FAC1*FMAS(MBDIAG,J)
      END DO
      CALL DEC (N,LDE1,E1,IP1,IER)
      RETURN
C
C -----------------------------------------------------------
C
   2  CONTINUE
C ---  B = IDENTITY OR DIAGONAL, SUMEXP LINEAR ALGEBRA
      ND=MUE+1
      TERM = FAC1
      DO J=1,ND
         DO  I=1,ND
            E1(I,J)=-FJAC(I,J)
         END DO
         IF (IJOB.EQ.4) TERM = FAC1*FMAS(MBDIAG,J)
         E1(J,J)=E1(J,J)+TERM
      END DO
      SUM=0.0D0
      LEXP=N-ND-2
      II=ND+2
      DO I=1,LEXP
         FACT=FJAC(3,II)
         II=II+1
         IF (I.EQ.1.OR.FACT.EQ.0.0D0) THEN
            CC=1.0D0
         ELSE
            CC=FACT*U1
         END IF
         U1=CC/(FAC1-FJAC(2,II))
         SUM=SUM+FJAC(1,II)*U1
      END DO
      DO J=1,ND
         DO  I=1,ND
            E1(I,J)=E1(I,J)-SUM*FJAC(I,ND+1)*FJAC(J,ND+2)
         END DO
      END DO
      CALL DEC (ND,LDE1,E1,IP1,IER)
      RETURN
C
C -----------------------------------------------------------
C
  55  CONTINUE
      RETURN
      END
C
C     END OF SUBROUTINE DECOMR
C
C ***********************************************************
C
      SUBROUTINE DECOMC(N,FJAC,LDJAC,FMAS,LDMAS,MLMAS,MUMAS,
     &            M1,M2,NM1,ALPHN,BETAN,E2R,E2I,LDE1,IP2,IER,IJOB)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION FJAC(LDJAC,N),FMAS(LDMAS,NM1),
     &          E2R(LDE1,NM1),E2I(LDE1,NM1),IP2(NM1)
      COMMON/LINAL/MLE,MUE,MBJAC,MBB,MDIAG,MDIFF,MBDIAG
C
      GOTO (1,2,3,2,55,55,55,55,55,55,2,2,55,55,55), IJOB
C
C -----------------------------------------------------------
C
   1  CONTINUE
C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
      DO J=1,N
         DO I=1,N
            E2R(I,J)=-FJAC(I,J)
            E2I(I,J)=0.D0
         END DO
         E2R(J,J)=E2R(J,J)+ALPHN
         E2I(J,J)=BETAN
      END DO
      CALL DECC (N,LDE1,E2R,E2I,IP2,IER)
      RETURN
C
C -----------------------------------------------------------
C
   3  CONTINUE
C ---  B IS A DIAGONAL MATRIX, JACOBIAN A FULL MATRIX
      DO  J=1,N
         DO  I=1,N
            E2R(I,J)=-FJAC(I,J)
            E2I(I,J)=0.D0
         END DO
         BB=FMAS(MBDIAG,J)
         E2R(J,J)=E2R(J,J)+ALPHN*BB
         E2I(J,J)=BETAN*BB
      END DO
      CALL DECC(N,LDE1,E2R,E2I,IP2,IER)
      RETURN
C
C -----------------------------------------------------------
C
   2  CONTINUE
C ---  B = IDENTITY OR DIAGONAL, SUMEXP LINEAR ALGEBRA
      ND=MUE+1
      BB=1.0D0
      DO J=1,ND
         DO  I=1,ND
            E2R(I,J)=-FJAC(I,J)
            E2I(I,J)=0.D0
         END DO
         IF (IJOB.EQ.4) BB = FMAS(MBDIAG,J)
         E2R(J,J)=E2R(J,J)+ALPHN*BB
         E2I(J,J)=BETAN*BB
      END DO
      LEXP=N-ND-2
      SUMR=0.0D0
      SUMI=0.0D0
      II=ND+2
      DO I=1,LEXP
         II=II+1
         FACT=FJAC(3,II-1)
         IF (I.EQ.1.OR.FACT.EQ.0.0D0) THEN
            ALGAM=ALPHN-FJAC(2,II)
            DENOM=ALGAM**2+BETAN**2
            UR=ALGAM/DENOM
            UI=-BETAN/DENOM
         ELSE
            USAVE=(UR*ALGAM+UI*BETAN)/DENOM
            UI=FACT*(UI*ALGAM-UR*BETAN)/DENOM
            UR=FACT*USAVE
         END IF
         SUMR=SUMR+FJAC(1,II)*UR
         SUMI=SUMI+FJAC(1,II)*UI
      END DO
      DO J=1,ND
         DO  I=1,ND
            PROD=FJAC(I,ND+1)*FJAC(J,ND+2)
            E2R(I,J)=E2R(I,J)-SUMR*PROD
            E2I(I,J)=E2I(I,J)-SUMI*PROD
         END DO
      END DO
      CALL DECC (ND,LDE1,E2R,E2I,IP2,IER)
      RETURN
C
C -----------------------------------------------------------
C
  55  CONTINUE
      RETURN
      END
C
C     END OF SUBROUTINE DECOMC
C
C ***********************************************************
C
      SUBROUTINE SLVRAD(N,FJAC,LDJAC,MLJAC,MUJAC,FMAS,LDMAS,MLMAS,MUMAS,
     &          M1,M2,NM1,FAC1,ALPHN,BETAN,E1,E2R,E2I,LDE1,Z1,Z2,Z3,
     &          F1,F2,F3,CONT,IP1,IP2,IPHES,IER,IJOB)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION FJAC(LDJAC,N),FMAS(LDMAS,NM1),E1(LDE1,NM1),
     &          E2R(LDE1,NM1),E2I(LDE1,NM1),IP1(NM1),IP2(NM1),
     &          IPHES(N),Z1(N),Z2(N),Z3(N),F1(N),F2(N),F3(N)
      DIMENSION CONT(4*N)
      COMMON/LINAL/MLE,MUE,MBJAC,MBB,MDIAG,MDIFF,MBDIAG
C
      GOTO (1,2,3,2,55,55,55,55,55,55,2,2,55,55,55), IJOB
C
C -----------------------------------------------------------
C
   1  CONTINUE
C ---  B = IDENTITY, JACOBIAN A FULL MATRIX
      DO I=1,N
         S2=-F2(I)
         S3=-F3(I)
         Z1(I)=Z1(I)-F1(I)*FAC1
         Z2(I)=Z2(I)+S2*ALPHN-S3*BETAN
         Z3(I)=Z3(I)+S3*ALPHN+S2*BETAN
      END DO
      CALL SOL (N,LDE1,E1,Z1,IP1)
      CALL SOLC (N,LDE1,E2R,E2I,Z2,Z3,IP2)
      RETURN
C
C -----------------------------------------------------------
C
   3  CONTINUE
C ---  B IS A DIAGONAL MATRIX, JACOBIAN A FULL MATRIX
      DO I=1,N
         BB=FMAS(MBDIAG,I)
         S2=-BB*F2(I)
         S3=-BB*F3(I)
         Z1(I)=Z1(I)-BB*F1(I)*FAC1
         Z2(I)=Z2(I)+S2*ALPHN-S3*BETAN
         Z3(I)=Z3(I)+S3*ALPHN+S2*BETAN
      END DO
      CALL SOL (N,LDE1,E1,Z1,IP1)
      CALL SOLC(N,LDE1,E2R,E2I,Z2,Z3,IP2)
      RETURN
C
C -----------------------------------------------------------
C
   2  CONTINUE
C ---  B = IDENTITY, SUMEXP LINEAR ALGEBRA
      BB=1.0D0
      DO I=1,N
         IF (IJOB.EQ.4) BB=FMAS(MBDIAG,I)
         S2=-BB*F2(I)
         S3=-BB*F3(I)
         Z1(I)=Z1(I)-BB*F1(I)*FAC1
         Z2(I)=Z2(I)+S2*ALPHN-S3*BETAN
         Z3(I)=Z3(I)+S3*ALPHN+S2*BETAN
      END DO
      CALL SOLEXP(N,FJAC,LDJAC,MUE,NM1,LDE1,E1,Z1,IP1,FAC1,IJOB)
      CALL SOLEXPC(N,FJAC,LDJAC,MUE,NM1,LDE1,E2R,E2I,Z2,Z3,
     &             IP1,IP2,ALPHN,BETAN,IJOB)
      RETURN
C
C -----------------------------------------------------------
C
  55  CONTINUE
      RETURN
      END
C
C     END OF SUBROUTINE SLVRAD
C
C ***********************************************************
C
      SUBROUTINE SOLEXP(N,FJAC,LDJAC,MUJAC,NM1,LDE1,E1,Z1,IP1,
     *                  FAC1,IJOB)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION FJAC(LDJAC,N),E1(LDE1,NM1),IP1(NM1),Z1(N)
      ND=MUJAC+1
      LEXP=N-ND-2
      SUM=0.0D0
      II=ND+1
      DO I=1,LEXP  
         FACT=FJAC(3,II+1)
         IF (I.EQ.1.OR.FACT.EQ.0.0D0) THEN
            FJINV=1.0D0/(FAC1-FJAC(2,II+2))
            U1=Z1(II)*FJINV
         ELSE
            U1=(Z1(II)+FACT*U1)*FJINV
         END IF
         SUM=SUM+FJAC(1,II+2)*U1
         II=II+1
      END DO
      ND1=ND+1
      DO I=1,ND
         Z1(I)=Z1(I)+SUM*FJAC(I,ND1)
      END DO
      CALL SOL (ND,LDE1,E1,Z1,IP1)
      ND2=ND+2
      PROD=0.0D0
      DO IPRO=1,ND
         PROD=PROD+FJAC(IPRO,ND2)*Z1(IPRO)
      END DO
      II=ND+1
      DO I=1,LEXP  
         FACT=FJAC(3,II+1)
         IF (I.EQ.1.OR.FACT.EQ.0.0D0) THEN
            FJINV=1.0D0/(FAC1-FJAC(2,II+2))
            Z1(II)=(Z1(II)+PROD)*FJINV
         ELSE
            Z1(II)=(Z1(II)+FACT*Z1(II-1))*FJINV
         END IF
         II=II+1
      END DO
      Z1(N-1)=0.0D0
      Z1(N)=0.0D0
      RETURN
      END
C
C     END OF SUBROUTINE SOLEXP
C
C ***********************************************************
C
      SUBROUTINE SOLEXPC(N,FJAC,LDJAC,MUJAC,NM1,LDE1,E2R,E2I,Z2,Z3,
     &             IP1,IP2,ALPHN,BETAN,IJOB)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION FJAC(LDJAC,N),E2R(LDE1,NM1),E2I(LDE1,NM1)
      DIMENSION IP1(NM1),IP2(NM1),Z2(N),Z3(N)
      ND=MUJAC+1
      LEXP=N-ND-2
      II=ND+1
      SUMR=0.0D0
      SUMI=0.0D0
      DO I=1,LEXP
         FACT=FJAC(3,II+1)
         IF (I.EQ.1.OR.FACT.EQ.0.0D0) THEN
            ALGAM=ALPHN-FJAC(2,II+2)
            DENOM=ALGAM**2+BETAN**2
            UR=(Z2(II)*ALGAM+Z3(II)*BETAN)/DENOM
            UI=(Z3(II)*ALGAM-Z2(II)*BETAN)/DENOM
         ELSE
            UR=FACT*UR
            UI=FACT*UI
            USAVE=((Z2(II)+UR)*ALGAM+(Z3(II)+UI)*BETAN)/DENOM
            UI=((Z3(II)+UI)*ALGAM-(Z2(II)+UR)*BETAN)/DENOM
            UR=USAVE
         END IF
         SUMR=SUMR+FJAC(1,II+2)*UR
         SUMI=SUMI+FJAC(1,II+2)*UI
         II=II+1
      END DO
      DO I=1,ND
         Z2(I)=Z2(I)+SUMR*FJAC(I,ND+1)
         Z3(I)=Z3(I)+SUMI*FJAC(I,ND+1)
      END DO
      CALL SOLC (ND,LDE1,E2R,E2I,Z2,Z3,IP2)
      ND2=ND+2
      PRODR=0.0D0
      PRODI=0.0D0
      DO IPRO=1,ND
         PRODR=PRODR+FJAC(IPRO,ND2)*Z2(IPRO)
         PRODI=PRODI+FJAC(IPRO,ND2)*Z3(IPRO)
      END DO
      II=ND+1
      DO I=1,LEXP
         FACT=FJAC(3,II+1)
         IF (I.EQ.1.OR.FACT.EQ.0.0D0) THEN
            ALGAM=ALPHN-FJAC(2,II+2)
            DENOM=ALGAM**2+BETAN**2
            UR=((Z2(II)+PRODR)*ALGAM+(Z3(II)+PRODI)*BETAN)/DENOM
            UI=((Z3(II)+PRODI)*ALGAM-(Z2(II)+PRODR)*BETAN)/DENOM
         ELSE
            UR=FACT*UR
            UI=FACT*UI
            USAVE=((Z2(II)+UR)*ALGAM+(Z3(II)+UI)*BETAN)/DENOM
            UI=((Z3(II)+UI)*ALGAM-(Z2(II)+UR)*BETAN)/DENOM
            UR=USAVE
         END IF
         Z2(II)=UR
         Z3(II)=UI
         II=II+1
      END DO
      Z2(N-1)=0.0D0
      Z2(N)=0.0D0
      Z3(N-1)=0.0D0
      Z3(N)=0.0D0
      RETURN
      END
C
C     END OF SUBROUTINE SOLEXPC
C
C ***********************************************************
C

      SUBROUTINE ESTRAD(N,FJAC,LDJAC,MLJAC,MUJAC,FMAS,LDMAS,MLMAS,MUMAS,
     &                  H,G0,DD1,DD2,DD3,CL1,CL3,CQ1,CQ2,CQ3,CERLQ,
     &                  FCN,NFCN,Y0,Y,IJOB,X,M1,M2,NM1,E1,LDE1,ALPHA,
     &                  Z1,Z2,Z3,CONT,F1,F2,F3,IP1,IPHES,SCAL,ERR,CERR,
     &                  FIRST,REJECT,FAC1,ARGLAG,PHI,RPAR,IPAR,
     &                  IOUT,PAST,IPAST,NRDS,JEFLAG,IEFLAG)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION FJAC(LDJAC,N),FMAS(LDMAS,NM1),E1(LDE1,NM1),IP1(NM1)
      DIMENSION IPHES(N),Z1(N),Z2(N),Z3(N),Y0(N),Y(N),F1(N),F2(N),F3(N)
      DIMENSION CONT(N),SCAL(N),RPAR(1),IPAR(1)
      DIMENSION PAST(1),IPAST(1)
      REAL*8, DIMENSION(:), allocatable :: W1,W2,Q1,Q2,YCONT,YAPP
      LOGICAL FIRST,REJECT,LEFT
      COMMON/LINAL/MLE,MUE,MBJAC,MBB,MDIAG,MDIFF,MBDIAG
      EXTERNAL ARGLAG,PHI
      ALLOCATE (W1(N),W2(N),Q1(N),Q2(N))
      W1(1)=1.0D0
      W2(1)=1.0D0
      Q1(1)=1.0D0
      Q2(1)=1.0D0
      HEE1=DD1/H
      HEE2=DD2/H
      HEE3=DD3/H 
      GOTO (1,2,3,2,55,55,55,55,55,55,2,2,55,55,55), IJOB
C
   1  CONTINUE
C ------  B=IDENTITY, JACOBIAN A FULL MATRIX
      NL=N
      DO  I=1,NL
         F2(I)=HEE1*Z1(I)+HEE2*Z2(I)+HEE3*Z3(I)
         CONT(I)=F2(I)+Y0(I)
         W1(I)=CL1*Z1(I)+CL3*Z3(I)
         Q1(I)=CQ1*Z1(I)+CQ2*Z2(I)+CQ3*Z3(I)
      END DO
      F3=G0*H*CONT
      IF (ALPHA.NE.0.D0) THEN
         W2=W1/(G0*H)
         Q2=Q1/(G0*H)
         CALL SOL (NL,LDE1,E1,W2,IP1) 
         CALL SOL (NL,LDE1,E1,Q2,IP1) 
      END IF
      CALL SOL (NL,LDE1,E1,CONT,IP1) 
      GOTO 77
C
   2  CONTINUE
C ------  B IS DIAGONAL, JACOBIAN A BANDED MATRIX
      NL=N-2
      BB=1.0D0
      DO I=1,NL
         IF (IJOB.EQ.4) BB=FMAS(MBDIAG,I)
         F2(I)=BB*(HEE1*Z1(I)+HEE2*Z2(I)+HEE3*Z3(I))
         CONT(I)=F2(I)+Y0(I)
         W1(I)=BB*(CL1*Z1(I)+CL3*Z3(I))
         Q1(I)=BB*(CQ1*Z1(I)+CQ2*Z2(I)+CQ3*Z3(I))
      END DO
      F3=G0*H*CONT
      IF (ALPHA.NE.0.D0) THEN
         W2=W1/(G0*H)
         Q2=Q1/(G0*H)
         CALL SOLEXP(N,FJAC,LDJAC,MUJAC,NM1,LDE1,E1,W2,IP1,FAC1,IJOB)
         CALL SOLEXP(N,FJAC,LDJAC,MUJAC,NM1,LDE1,E1,Q2,IP1,FAC1,IJOB)
      END IF
      CALL SOLEXP(N,FJAC,LDJAC,MUJAC,NM1,LDE1,E1,CONT,IP1,FAC1,IJOB)
      GOTO 77
C
   3  CONTINUE
C ------  B IS DIAGONAL, JACOBIAN A FULL MATRIX
      NL=N
      DO I=1,NL
         BB=FMAS(MBDIAG,I)
         F2(I)=BB*(HEE1*Z1(I)+HEE2*Z2(I)+HEE3*Z3(I))
         W1(I)=BB*(CL1*Z1(I)+CL3*Z3(I))
         Q1(I)=BB*(CQ1*Z1(I)+CQ2*Z2(I)+CQ3*Z3(I))
         CONT(I)=F2(I)+Y0(I)
      END DO
      F3=G0*H*CONT
      IF (ALPHA.NE.0.D0) THEN
         W2=W1/(G0*H)
         Q2=Q1/(G0*H)
         CALL SOL (NL,LDE1,E1,W2,IP1) 
         CALL SOL (NL,LDE1,E1,Q2,IP1) 
      END IF
      CALL SOL (NL,LDE1,E1,CONT,IP1) 
      GOTO 77
C
C --------------------------------------
C
  77  CONTINUE
C ********************
C --- ERROR ESTIMATION
C ********************
      ERRB=0.D0
      DO I=1,NL
         ERRB=ERRB+(W1(I)/SCAL(I))**2
      END DO
      ERRLB=MAX(SQRT(ERRB/NL),1.D-10)
      IF (ALPHA.NE.0.D0) THEN
         ERR=0.D0
         DO  I=1,NL
            ERR=ERR+(W2(I)/SCAL(I))**2
         END DO
         ERRL=MAX(SQRT(ERR/NL),1.D-10)
      ELSE
         ERRL=0.D0
      END IF
      ERRB=0.D0
      DO  I=1,NL
         ERRB=ERRB+(Q1(I)/SCAL(I))**2
      END DO
      ERRQB=MAX(SQRT(ERRB/NL),1.D-10)
      IF (ALPHA.NE.0.D0) THEN
         ERR=0.D0
         DO  I=1,NL
            ERR=ERR+(Q2(I)/SCAL(I))**2
         END DO
         ERRQ=MAX(SQRT(ERR/NL),1.D-10)
      ELSE
         ERRQ=0.D0
      END IF
      CERRB=ERRQB*(ERRQB/SQRT(ERRQB*ERRQB+
     &             CERLQ*CERLQ*MIN(ERRLB,ERRQB/CERLQ)**2))
      IF (ALPHA.NE.0.D0) THEN
         CERR=ERRQ*(ERRQ/SQRT(ERRQ*ERRQ+
     &            CERLQ*CERLQ*MIN(ERRL,ERRQ/CERLQ)**2))
      ELSE
         CERR=0.D0
      END IF
      CERR=ALPHA*CERR+(1.D0-ALPHA)*CERRB
      ERRB=0.D0
      DO  I=1,NL
         ERRB=ERRB+(F3(I)/SCAL(I))**2
      END DO
      ERRB=MAX(SQRT(ERRB/NL),1.D-10)
      ERR=0.D0
      DO  I=1,NL
         ERR=ERR+(CONT(I)/SCAL(I))**2
      END DO
      ERR=MAX(SQRT(ERR/NL),1.D-10)
      ERR=MIN(ERRB,ERR)
      IF (ERR.LT.1.D0.OR.JEFLAG.GT.0) THEN 
        DEALLOCATE (W1,W2,Q1,Q2)
        RETURN
      ELSE IF (FIRST.OR.REJECT) THEN
        DO I=1,NL
           CONT(I)=Y(I)+CONT(I)
        END DO
C ---
        XX=X
        CALL FCN(N,XX,CONT,F1,ARGLAG,PHI,RPAR,IPAR,
     &           PAST,IPAST,NRDS)
        NFCN=NFCN+1
        DO I=1,NL
           CONT(I)=F1(I)+F2(I)
        END DO
        GOTO (31,32,31,32,31,32,55,55,55,55,32,32,31,32,31), IJOB
C ----- FULL MATRIX OPTION
  31    CONTINUE
        CALL SOL(NL,LDE1,E1,CONT,IP1) 
        GOTO 88
C ----- BANDED MATRIX OPTION
  32    CONTINUE
        CALL SOLEXP(N,FJAC,LDJAC,MUJAC,NM1,LDE1,E1,CONT,IP1,
     &                 FAC1,IJOB)
        GOTO 88
C -----------------------------------
   88   CONTINUE
        SERR=ERR
        ERR=0.D0 
        DO I=1,NL
           ERR=ERR+(CONT(I)/SCAL(I))**2
        END DO
        ERR=MAX(SQRT(ERR/NL),1.D-10)
        ERR=MIN(SERR,ERR)
      END IF
      DEALLOCATE (W1,W2,Q1,Q2)
      RETURN
C -----------------------------------------------------------
  55  CONTINUE
      DEALLOCATE (W1,W2,Q1,Q2)
      RETURN
      END
C
C     END OF SUBROUTINE ESTRAD
C
C ***********************************************************
