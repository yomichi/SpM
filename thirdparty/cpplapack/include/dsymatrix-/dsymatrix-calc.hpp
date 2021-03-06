//=============================================================================
/*! return transposed dgematrix */
inline _dsymatrix t(const dsymatrix& mat)
{CPPL_VERBOSE_REPORT;
#ifdef  CPPL_DEBUG
  WARNING_REPORT;
  std::cerr << "This function call has no effect since the matrix is symmetric." << std::endl;
#endif//CPPL_DEBUG
  
  dsymatrix newmat(mat);
  return _(newmat);
}

//=============================================================================
/*! return its inverse matrix */
inline _dsymatrix i(const dsymatrix& mat)
{CPPL_VERBOSE_REPORT;
  dsymatrix mat_cp =mat;
  dsymatrix mat_inv(mat.n);
  mat_inv.identity();
  mat_inv.complete();
  
  char UPLO('l');
  CPPL_INT NRHS(mat.n), LDA(mat.n), *IPIV(new CPPL_INT[mat.n]), LDB(mat.n), LWORK(-1), INFO(1);
  double *WORK( new double[1] );
  dsysv_(&UPLO, &mat.n, &NRHS, mat_cp.array, &LDA, IPIV, mat_inv.array, &LDB, WORK, &LWORK, &INFO);
  
  LWORK = CPPL_INT(WORK[0]);
  delete [] WORK;
  WORK = new double[LWORK];
  dsysv_(&UPLO, &mat.n, &NRHS, mat_cp.array, &LDA, IPIV, mat_inv.array, &LDB, WORK, &LWORK, &INFO);
  
  delete [] WORK;
  delete [] IPIV;
  if(INFO!=0){
    WARNING_REPORT;
    std::cerr << "Serious trouble happend. INFO = " << INFO << "." << std::endl;
  }
  
  return _(mat_inv);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! search the index of element having the largest absolute value in 0-based numbering system */
inline void idamax(CPPL_INT& i, CPPL_INT& j, const dsymatrix& mat)
{CPPL_VERBOSE_REPORT;
  i=j=0;
  double val =0.;
  
  for(CPPL_INT J=0; J<mat.n; J++){
    for(CPPL_INT I=J; I<mat.n; I++){
      if(val<fabs(mat.darray[J][I]) ){
        val =fabs(mat.darray[J][I]);
        i=I;
        j=J;
      }
    }
  }
}

//=============================================================================
/*! return its largest absolute value */
inline double damax(const dsymatrix& mat)
{CPPL_VERBOSE_REPORT;
  CPPL_INT i,j;
  idamax(i, j, mat);
  return mat(i,j);
}
