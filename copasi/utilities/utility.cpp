#include <math.h>
#include <stdio.h>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utility.h"

std::string StringPrint(const char * format, ...)
{
  C_INT32 TextSize = INITIALTEXTSIZE;
  C_INT32 Printed = 0;

  char *Text = NULL;

  va_list Arguments = NULL;
  va_start(Arguments, format);

  Text = new char[TextSize + 1];

  Printed = vsnprintf(Text, TextSize + 1, format, Arguments);

  while (Printed < 0 || TextSize < Printed)
    {
      delete [] Text;

      (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
      Text = new char[TextSize + 1];

      Printed = vsnprintf(Text, TextSize, format, Arguments);
    }
  va_end(Arguments);

  std::string Result = Text;

  delete [] Text;
  return Result;
}

C_FLOAT64 ddot(C_INT32 n,
               C_FLOAT64 * dx,
               C_INT32 incx,
               C_FLOAT64 * dy,
               C_INT32 incy)
/*
  Purpose : Inner product dx . dy
 
  --- Input ---
 
  n    : number of elements in input vector(s)
  dx   : C_FLOAT64 vector with n+1 elements, dx[0] is not used
  incx : storage spacing between elements of dx
  dy   : C_FLOAT64 vector with n+1 elements, dy[0] is not used
  incy : storage spacing between elements of dy
 
  --- Output ---
 
  ddot : dot product dx . dy, 0 if n <= 0
 
  ddot = sum for i = 0 to n-1 of
  dx[lx+i*incx] * dy[ly+i*incy] where lx = 1 if
  incx >= 0, else lx = (-incx)*(n-1)+1, and ly
  is defined in a similar way using incy.
 */
{
  C_FLOAT64 dotprod;
  C_INT32 ix, iy, i, m;

  dotprod = 0.0;
  if (n <= 0)
    return dotprod;

  /* Code for unequal or nonpositive increments.  */

  if (incx != incy || incx < 1)
    {
      ix = 1;
      iy = 1;
      if (incx < 0)
        ix = (-n + 1) * incx + 1;
      if (incy < 0)
        iy = (-n + 1) * incy + 1;
      for (i = 1; i <= n; i++)
        {
          dotprod = dotprod + dx[ix] * dy[iy];
          ix = ix + incx;
          iy = iy + incy;
        }
      return dotprod;
    }

  /* Code for both increments equal to 1.  */

  /* Clean-up loop so remaining vector length is a multiple of 5.  */

  if (incx == 1)
    {
      m = n % 5;
      if (m != 0)
        {
          for (i = 1; i <= m; i++)
            dotprod = dotprod + dx[i] * dy[i];
          if (n < 5)
            return dotprod;
        }
      for (i = m + 1; i <= n; i = i + 5)
        dotprod = dotprod + dx[i] * dy[i] + dx[i + 1] * dy[i + 1] +
                  dx[i + 2] * dy[i + 2] + dx[i + 3] * dy[i + 3] +
                  dx[i + 4] * dy[i + 4];
      return dotprod;
    }

  /* Code for positive equal nonunit increments.   */

  for (i = 1; i <= n * incx; i = i + incx)
    dotprod = dotprod + dx[i] * dy[i];
  return dotprod;
}

void dscal(C_INT32 n,
           C_FLOAT64 da,
           C_FLOAT64 * dx,
           C_INT32 incx)
/* Purpose : scalar vector multiplication
 
dx = da * dx
 
--- Input ---
 
n    : number of elements in input vector
da   : C_FLOAT64 scale factor
dx   : C_FLOAT64 vector with n+1 elements, dx[0] is not used
incx : storage spacing between elements of dx
 
--- Output ---
 
dx = da * dx, unchanged if n <= 0
 
For i = 0 to n-1, replace dx[1+i*incx] with
da * dx[1+i*incx].
 
 */
{
  C_INT32 m, i;

  if (n <= 0)
    return;

  /* Code for increments not equal to 1.  */

  if (incx != 1)
    {
      for (i = 1; i <= n * incx; i = i + incx)
        dx[i] = da * dx[i];
      return;
    }

  /* Code for increments equal to 1.  */

  /* Clean-up loop so remaining vector length is a multiple of 5.  */

  m = n % 5;
  if (m != 0)
    {
      for (i = 1; i <= m; i++)
        dx[i] = da * dx[i];
      if (n < 5)
        return;
    }
  for (i = m + 1; i <= n; i = i + 5)
    {
      dx[i] = da * dx[i];
      dx[i + 1] = da * dx[i + 1];
      dx[i + 2] = da * dx[i + 2];
      dx[i + 3] = da * dx[i + 3];
      dx[i + 4] = da * dx[i + 4];
    }
  return;
}

void daxpy(C_INT32 n,
           C_FLOAT64 da,
           C_FLOAT64 * dx,
           C_INT32 incx,
           C_FLOAT64 * dy,
           C_INT32 incy)
/*
  Purpose : To compute
 
  dy = da * dx + dy
 
  --- Input ---
 
  n    : number of elements in input vector(s)
  da   : C_FLOAT64 scalar multiplier
  dx   : C_FLOAT64 vector with n+1 elements, dx[0] is not used
  incx : storage spacing between elements of dx
  dy   : C_FLOAT64 vector with n+1 elements, dy[0] is not used
  incy : storage spacing between elements of dy
 
  --- Output ---
 
  dy = da * dx + dy, unchanged if n <= 0
 
  For i = 0 to n-1, replace dy[ly+i*incy] with
  da*dx[lx+i*incx] + dy[ly+i*incy], where lx = 1
  if  incx >= 0, else lx = (-incx)*(n-1)+1 and ly is
  defined in a similar way using incy.
 
 */
{
  C_INT32 ix, iy, i, m;

  if (n < 0 || da == 0.)
    return;

  /* Code for nonequal or nonpositive increments.  */

  if (incx != incy || incx < 1)
    {
      ix = 1;
      iy = 1;
      if (incx < 0)
        ix = (-n + 1) * incx + 1;
      if (incy < 0)
        iy = (-n + 1) * incy + 1;
      for (i = 1; i <= n; i++)
        {
          dy[iy] = dy[iy] + da * dx[ix];
          ix = ix + incx;
          iy = iy + incy;
        }
      return;
    }

  /* Code for both increments equal to 1.   */

  /* Clean-up loop so remaining vector length is a multiple of 4.  */

  if (incx == 1)
    {
      m = n % 4;
      if (m != 0)
        {
          for (i = 1; i <= m; i++)
            dy[i] = dy[i] + da * dx[i];
          if (n < 4)
            return;
        }
      for (i = m + 1; i <= n; i = i + 4)
        {
          dy[i] = dy[i] + da * dx[i];
          dy[i + 1] = dy[i + 1] + da * dx[i + 1];
          dy[i + 2] = dy[i + 2] + da * dx[i + 2];
          dy[i + 3] = dy[i + 3] + da * dx[i + 3];
        }
      return;
    }

  /* Code for equal, positive, nonunit increments.   */

  for (i = 1; i <= n * incx; i = i + incx)
    dy[i] = da * dx[i] + dy[i];
  return;
}

/* :TODO: replace with dgetrs_ form clapack */
void dgesl(C_FLOAT64 ** a,
           C_INT32 n,
           C_INT32 * ipvt,
           C_FLOAT64 * b,
           C_INT32 job)
/*
  Purpose : dgesl solves the linear system
  a * x = b or Transpose(a) * x = b
  using the factors computed by dgeco or degfa.
 
  On Entry :
 
  a    : C_FLOAT64 matrix of dimension (n+1, n+1),
  the output from dgeco or dgefa.
  The 0-th row and column are not used.
  n    : the row dimension of a.
  ipvt : the pivot vector from degco or dgefa.
  b    : the right hand side vector.
  job  : = 0       to solve a * x = b,
  = nonzero to solve Transpose(a) * x = b.
 
  On Return :
 
  b : the solution vector x.
 
  Error Condition :
 
  A division by zero will occur if the input factor contains
  a zero on the diagonal.  Technically this indicates
  singularity but it is often caused by improper argments or
  improper setting of the pointers of a.  It will not occur
  if the subroutines are called correctly and if dgeco has
  set rcond > 0 or dgefa has set info = 0.
 
  BLAS : daxpy, ddot
 */
{
  C_INT32 nm1, k, j;
  C_FLOAT64 t;

  nm1 = n - 1;

  /*
    Job = 0, solve a * x = b.
  */
  if (job == 0)
    {
      /*
        First solve L * y = b.
      */
      for (k = 1; k <= n; k++)
        {
          t = ddot(k - 1, a[k], 1, b, 1);
          b[k] = (b[k] - t) / a[k][k];
        }
      /*
        Now solve U * x = y.
      */
      for (k = n - 1; k >= 1; k--)
        {
          b[k] = b[k] + ddot(n - k, a[k] + k, 1, b + k, 1);
          j = ipvt[k];
          if (j != k)
            {
              t = b[j];
              b[j] = b[k];
              b[k] = t;
            }
        }
      return;
    }

  /*
    Job = nonzero, solve Transpose(a) * x = b.

    First solve Transpose(U) * y = b.
  */
  for (k = 1; k <= n - 1; k++)
    {
      j = ipvt[k];
      t = b[j];
      if (j != k)
        {
          b[j] = b[k];
          b[k] = t;
        }
      daxpy(n - k, t, a[k] + k, 1, b + k, 1);
    }
  /*
    Now solve Transpose(L) * x = y.
  */
  for (k = n; k >= 1; k--)
    {
      b[k] = b[k] / a[k][k];
      t = -b[k];
      daxpy(k - 1, t, a[k], 1, b, 1);
    }
}

C_INT32 idamax(C_INT32 n,
               C_FLOAT64 * dx,
               C_INT32 incx)
/* Purpose : Find largest component of C_FLOAT64 vector dx
 
--- Input ---
 
n    : number of elements in input vector
dx   : C_FLOAT64 vector with n+1 elements, dx[0] is not used
incx : storage spacing between elements of dx
 
--- Output ---
 
idamax : smallest index, 0 if n <= 0
 
Find smallest index of maximum magnitude of dx.
idamax = first i, i=1 to n, to minimize fabs(dx[1-incx+i*incx]).
 
 */
{
  C_FLOAT64 dmax, xmag;
  C_INT32 i, ii, xindex;

  xindex = 0;
  if (n <= 0)
    return xindex;
  xindex = 1;
  if (n <= 1 || incx <= 0)
    return xindex;

  /* Code for increments not equal to 1.   */

  if (incx != 1)
    {
      dmax = fabs(dx[1]);
      ii = 2;
      for (i = 1 + incx; i <= n * incx; i = i + incx)
        {
          xmag = fabs(dx[i]);
          if (xmag > dmax)
            {
              xindex = ii;
              dmax = xmag;
            }
          ii++;
        }
      return xindex;
    }

  /* Code for increments equal to 1.  */

  dmax = fabs(dx[1]);
  for (i = 2; i <= n; i++)
    {
      xmag = fabs(dx[i]);
      if (xmag > dmax)
        {
          xindex = i;
          dmax = xmag;
        }
    }
  return xindex;
}

C_FLOAT64 xNorm(C_INT32 n, C_FLOAT64 * x, C_INT32 i)
{
  return fabs(x[idamax(n, x, i)]);
}

/* :TODO: replace with dgetrf_ from clapack */
void dgefa(C_FLOAT64 ** a,
           C_INT32 n,
           C_INT32 * ipvt,
           C_INT32 * info)
/*
  Purpose : dgefa factors a C_FLOAT64 matrix by Gaussian elimination.
 
  dgefa is usually called by dgeco, but it can be called directly
  with a saving in time if rcond is not needed.
  (Time for dgeco) = (1+9/n)*(time for dgefa).
 
  This c version uses algorithm kji rather than the kij in dgefa.f.
  Note that the fortran version input variable lda is not needed.
 
  On Entry :
 
  a   : C_FLOAT64 matrix of dimension (n+1, n+1),
  the 0-th row and column are not used.
  a is created using NewDoubleMatrix, hence
  lda is unnecessary.
  n   : the row dimension of a.
 
  On Return :
 
  a     : a lower triangular matrix and the multipliers
  which were used to obtain it.  The factorization
  can be written a = L * U where U is a product of
  permutation and unit upper triangular matrices
  and L is lower triangular.
  ipvt  : an n+1 integer vector of pivot indices.
  *info : = 0 normal value,
  = k if U[k][k] == 0.  This is not an error
  condition for this subroutine, but it does
  indicate that dgesl or dgedi will divide by
  zero if called.  Use rcond in dgeco for
  a reliable indication of singularity.
 
  Notice that the calling program must use &info.
 
  BLAS : daxpy, dscal, idamax
 */
{
  C_INT32 j, k, i;
  C_FLOAT64 t;

  /* Gaussian elimination with partial pivoting.   */

  *info = 0;
  for (k = 1; k <= n - 1; k++)
    {
      /*
        Find j = pivot index.  Note that a[k]+k-1 is the address of
        the 0-th element of the row vector whose 1st element is a[k][k].
      */
      j = idamax(n - k + 1, a[k] + k - 1, 1) + k - 1;
      ipvt[k] = j;
      /*
        Zero pivot implies this row already triangularized.
      */
      if (a[k][j] == 0.)
        {
          *info = k;
          continue;
        }
      /*
        Interchange if necessary.
      */
      if (j != k)
        {
          t = a[k][j];
          a[k][j] = a[k][k];
          a[k][k] = t;
        }
      /*
        Compute multipliers.
      */
      t = -1. / a[k][k];
      dscal(n - k, t, a[k] + k, 1);
      /*
        Column elimination with row indexing.
      */
      for (i = k + 1; i <= n; i++)
        {
          t = a[i][j];
          if (j != k)
            {
              a[i][j] = a[i][k];
              a[i][k] = t;
            }
          daxpy(n - k, t, a[k] + k, 1, a[i] + k, 1);
        }
    }                     /*  end k-loop  */

  ipvt[n] = n;
  if (a[n][n] == 0.)
    *info = n;
}

/*
 * Fixes a string to be a SName element from SBML
 * (this is a destructive function, some changes are irreversible)
 *
 */

void FixSName(const std::string &original, std::string &fixed)
{
  int i, len;
  // check reserved names
  if (original == "abs") {fixed = "_abs"; return;}
  if (original == "acos") {fixed = "_acos"; return;}
  if (original == "and") {fixed = "_and"; return;}
  if (original == "asin") {fixed = "_asin"; return;}
  if (original == "atan") {fixed = "_atan"; return;}
  if (original == "ceil") {fixed = "_ceil"; return;}
  if (original == "cos") {fixed = "_cos"; return;}
  if (original == "exp") {fixed = "_exp"; return;}
  if (original == "floor") {fixed = "_floor"; return;}
  if (original == "hilli") {fixed = "_hilli"; return;}
  if (original == "hillmmr") {fixed = "_hillmmr"; return;}
  if (original == "hillmr") {fixed = "_hillmr"; return;}
  if (original == "hillr") {fixed = "_hillr"; return;}
  if (original == "isouur") {fixed = "_isouur"; return;}
  if (original == "log") {fixed = "_log"; return;}
  if (original == "log10") {fixed = "_log10"; return;}
  if (original == "massi") {fixed = "_massi"; return;}
  if (original == "massr") {fixed = "_massr"; return;}
  if (original == "not") {fixed = "_not"; return;}
  if (original == "or") {fixed = "_or"; return;}
  if (original == "ordbbr") {fixed = "_ordbbr"; return;}
  if (original == "ordbur") {fixed = "_ordbur"; return;}
  if (original == "ordubr") {fixed = "_ordubr"; return;}
  if (original == "pow") {fixed = "_pow"; return;}
  if (original == "ppbr") {fixed = "_ppbr"; return;}
  if (original == "sin") {fixed = "_sin"; return;}
  if (original == "sqr") {fixed = "_sqr"; return;}
  if (original == "sqrt") {fixed = "_sqrt"; return;}
  if (original == "substance") {fixed = "_substance"; return;}
  if (original == "time") {fixed = "_time"; return;}
  if (original == "tan") {fixed = "_tan"; return;}
  if (original == "umai") {fixed = "_umai"; return;}
  if (original == "umar") {fixed = "_umar"; return;}
  if (original == "uai") {fixed = "_uai"; return;}
  if (original == "ualii") {fixed = "_ualii"; return;}
  if (original == "uar") {fixed = "_uar"; return;}
  if (original == "ucii") {fixed = "_ucii"; return;}
  if (original == "ucir") {fixed = "_ucir"; return;}
  if (original == "ucti") {fixed = "_ucti"; return;}
  if (original == "uctr") {fixed = "_uctr"; return;}
  if (original == "uhmi") {fixed = "_uhmi"; return;}
  if (original == "uhmr") {fixed = "_uhmr"; return;}
  if (original == "umi") {fixed = "_umi"; return;}
  if (original == "unii") {fixed = "_unii"; return;}
  if (original == "unir") {fixed = "_unir"; return;}
  if (original == "uuhr") {fixed = "_uuhr"; return;}
  if (original == "umr") {fixed = "_umr"; return;}
  if (original == "usii") {fixed = "_usii"; return;}
  if (original == "usir") {fixed = "_usir"; return;}
  if (original == "uuci") {fixed = "_uuci"; return;}
  if (original == "uucr") {fixed = "_uucr"; return;}
  if (original == "uui") {fixed = "_uui"; return;}
  if (original == "uur") {fixed = "_uur"; return;}
  if (original == "volume") {fixed = "_volume"; return;}
  if (original == "xor") {fixed = "_xor"; return;}
  len = original.length();
  // check rule for initial characters
  // if first not a letter...
  if (((original[0] < 'A') || (original[0] > 'z')) && (original[0] != '_'))
    {
      if ((original[0] >= '0') && (original[0] <= '9'))
        fixed = "_" + original;
      else
      {fixed = original; fixed [0] = '_';}
    }
  else
    fixed = original;
  len = fixed.length();

  for (i = 1; i < len; i++)
    if ((fixed [i] != '_') && ((fixed [i] < 'A') || (fixed [i] > 'z')) &&
        ((fixed [i] < '0') || (fixed [i] > '9')))
      fixed [i] = '_';
}

/*
 * Fixes a string to a XHTML valid equivalent
 */
void FixXHTML(const std::string &original, std::string &fixed)
{
  C_INT32 i, p, len;
  std::string Str;
  // find the next illegal character
  Str = original;
  fixed.erase();
  for (i = 0; i != -1;)
    {
      p = Str.find_first_of("&><\"¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ");
      fixed += Str.substr(0, p)
;
      len = Str.length();
      i = Str.find_first_of("&><\"¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ");
      if (i != -1)
        {
          switch (Str[i])
            {
            case '&':
              fixed += "&amp; ";
              break;
            case '>':
              fixed += "&gt; ";
              break;
            case '<':
              fixed += "&lt; ";
              break;
            case '"':
              fixed += "&quot; ";
              break;
            case '¡':
              fixed += "&#161; ";
              break;
            case '¢':
              fixed += "&#162; ";
              break;
            case '£':
              fixed += "&#163; ";
              break;
            case '¤':
              fixed += "&#164; ";
              break;
            case '¥':
              fixed += "&#165; ";
              break;
            case '¦':
              fixed += "&#166; ";
              break;
            case '§':
              fixed += "&#167; ";
              break;
            case '¨':
              fixed += "&#168; ";
              break;
            case '©':
              fixed += "&#169; ";
              break;
            case 'ª':
              fixed += "&#170; ";
              break;
            case '«':
              fixed += "&#171; ";
              break;
            case '¬':
              fixed += "&#172; ";
              break;
            case '­':
              fixed += "&#173; ";
              break;
            case '®':
              fixed += "&#174; ";
              break;
            case '¯':
              fixed += "&#175; ";
              break;
            case '°':
              fixed += "&#176; ";
              break;
            case '±':
              fixed += "&#177; ";
              break;
            case '²':
              fixed += "&#178; ";
              break;
            case '³':
              fixed += "&#179; ";
              break;
            case '´':
              fixed += "&#180; ";
              break;
            case 'µ':
              fixed += "&#181; ";
              break;
            case '¶':
              fixed += "&#182; ";
              break;
            case '·':
              fixed += "&#183; ";
              break;
            case '¸':
              fixed += "&#184; ";
              break;
            case '¹':
              fixed += "&#185; ";
              break;
            case 'º':
              fixed += "&#186; ";
              break;
            case '»':
              fixed += "&#187; ";
              break;
            case '¼':
              fixed += "&#188; ";
              break;
            case '½':
              fixed += "&#189; ";
              break;
            case '¾':
              fixed += "&#190; ";
              break;
            case '¿':
              fixed += "&#191; ";
              break;
            case 'À':
              fixed += "&#192; ";
              break;
            case 'Á':
              fixed += "&#193; ";
              break;
            case 'Â':
              fixed += "&#194; ";
              break;
            case 'Ã':
              fixed += "&#195; ";
              break;
            case 'Ä':
              fixed += "&#196; ";
              break;
            case 'Å':
              fixed += "&#197; ";
              break;
            case 'Æ':
              fixed += "&#198; ";
              break;
            case 'Ç':
              fixed += "&#199; ";
              break;
            case 'È':
              fixed += "&#200; ";
              break;
            case 'É':
              fixed += "&#201; ";
              break;
            case 'Ê':
              fixed += "&#202; ";
              break;
            case 'Ë':
              fixed += "&#203; ";
              break;
            case 'Ì':
              fixed += "&#204; ";
              break;
            case 'Í':
              fixed += "&#205; ";
              break;
            case 'Î':
              fixed += "&#206; ";
              break;
            case 'Ï':
              fixed += "&#207; ";
              break;
            case 'Ð':
              fixed += "&#208; ";
              break;
            case 'Ñ':
              fixed += "&#209; ";
              break;
            case 'Ò':
              fixed += "&#210; ";
              break;
            case 'Ó':
              fixed += "&#211; ";
              break;
            case 'Ô':
              fixed += "&#212; ";
              break;
            case 'Õ':
              fixed += "&#213; ";
              break;
            case 'Ö':
              fixed += "&#214; ";
              break;
            case '×':
              fixed += "&#215; ";
              break;
            case 'Ø':
              fixed += "&#216; ";
              break;
            case 'Ù':
              fixed += "&#217; ";
              break;
            case 'Ú':
              fixed += "&#218; ";
              break;
            case 'Û':
              fixed += "&#219; ";
              break;
            case 'Ü':
              fixed += "&#220; ";
              break;
            case 'Ý':
              fixed += "&#221; ";
              break;
            case 'Þ':
              fixed += "&#222; ";
              break;
            case 'ß':
              fixed += "&#223; ";
              break;
            case 'à':
              fixed += "&#224; ";
              break;
            case 'á':
              fixed += "&#225; ";
              break;
            case 'â':
              fixed += "&#226; ";
              break;
            case 'ã':
              fixed += "&#227; ";
              break;
            case 'ä':
              fixed += "&#228; ";
              break;
            case 'å':
              fixed += "&#229; ";
              break;
            case 'æ':
              fixed += "&#230; ";
              break;
            case 'ç':
              fixed += "&#231; ";
              break;
            case 'è':
              fixed += "&#232; ";
              break;
            case 'é':
              fixed += "&#233; ";
              break;
            case 'ê':
              fixed += "&#234; ";
              break;
            case 'ë':
              fixed += "&#235; ";
              break;
            case 'ì':
              fixed += "&#236; ";
              break;
            case 'í':
              fixed += "&#237; ";
              break;
            case 'î':
              fixed += "&#238; ";
              break;
            case 'ï':
              fixed += "&#239; ";
              break;
            case 'ð':
              fixed += "&#240; ";
              break;
            case 'ñ':
              fixed += "&#241; ";
              break;
            case 'ò':
              fixed += "&#242; ";
              break;
            case 'ó':
              fixed += "&#243; ";
              break;
            case 'ô':
              fixed += "&#244; ";
              break;
            case 'õ':
              fixed += "&#245; ";
              break;
            case 'ö':
              fixed += "&#246; ";
              break;
            case '÷':
              fixed += "&#247; ";
              break;
            case 'ø':
              fixed += "&#248; ";
              break;
            case 'ù':
              fixed += "&#249; ";
              break;
            case 'ú':
              fixed += "&#250; ";
              break;
            case 'û':
              fixed += "&#251; ";
              break;
            case 'ü':
              fixed += "&#252; ";
              break;
            case 'ý':
              fixed += "&#253; ";
              break;
            case 'þ':
              fixed += "&#254; ";
              break;
            case 'ÿ':
              fixed += "&#255; ";
              break;
            }
        }
      Str = Str.substr(len - i - 1);
    }
}
