//
// File: G3D.cpp
//
// MATLAB Coder version            : 4.0
// C/C++ source code generated on  : 20-Nov-2019 22:35:27
//

// Include Files
#include <cmath>
#include <math.h>
#include "rt_nonfinite.h"
#include "G3D.h"

// Function Declarations
static double rt_powd_snf(double u0, double u1);
static double taunum3D(double x, double y, double z, double x0, double b_y0,
  double z0);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = 1.0;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// TAUNUM3D
//     TAU = TAUNUM3D(X,Y,Z,X0,Y0,Z0)
// Arguments    : double x
//                double y
//                double z
//                double x0
//                double b_y0
//                double z0
// Return Type  : double
//
static double taunum3D(double x, double y, double z, double x0, double b_y0,
  double z0)
{
  double t2;
  double t3;
  double t4;

  //     This function was generated by the Symbolic Math Toolbox version 8.1.
  //     20-Nov-2019 22:09:24
  t2 = x - x0;
  t3 = y - b_y0;
  t4 = z - z0;
  return std::sqrt((t2 * t2 + t3 * t3) + t4 * t4) * 2.0;
}

//
// G3D
//   #D Green function-based Taylor expansions
// Arguments    : const double z[3]
//                const double z0[3]
//                double w
// Return Type  : creal_T
//
creal_T G3D(const double z[3], const double z0[3], double w)
{
  creal_T out;
  double tau;
  double b_z;
  double y_re;
  double r;
  double y_im;
  double b_tau;
  double c_z;
  double b_y_re;
  double b_y_im;
  double re;
  double im;
  double b_re;
  tau = taunum3D(z[0], z[1], z[2], z0[0], z0[1], z0[2]);
  b_z = w * tau;

  //  define hankel function using besselj and besselh and bessely are not supported in Matlab Coder 
  //  v=0.5
  y_re = b_z * 0.0;
  if (b_z == 0.0) {
    y_re = std::exp(y_re);
    y_im = 0.0;
  } else {
    r = std::exp(y_re / 2.0);
    y_re = r * (r * std::cos(b_z));
    y_im = r * (r * std::sin(b_z));
  }

  b_tau = taunum3D(z[0], z[1], z[2], z0[0], z0[1], z0[2]);
  c_z = w * b_tau;

  //  define hankel function using besselj and besselh and bessely are not supported in Matlab Coder 
  //  v=0.5
  b_y_re = c_z * 0.0;
  if (c_z == 0.0) {
    b_y_re = std::exp(b_y_re);
    b_y_im = 0.0;
  } else {
    r = std::exp(b_y_re / 2.0);
    b_y_re = r * (r * std::cos(c_z));
    b_y_im = r * (r * std::sin(c_z));
  }

  re = std::sqrt(2.0 / (3.1415926535897931 * b_z)) * 0.0;
  im = -std::sqrt(2.0 / (3.1415926535897931 * b_z));
  b_re = re * y_re - im * y_im;
  im = re * y_im + im * y_re;
  re = b_re * 6.123233995736766E-17 - im;
  im = b_re + im * 6.123233995736766E-17;
  b_re = rt_powd_snf(2.0 * tau / w, -0.5) * 0.88622692545275794;
  y_re = rt_powd_snf(2.0 * tau / w, -0.5) * 5.4265748378696E-17;
  y_im = std::sqrt(2.0 / (3.1415926535897931 * c_z)) * 0.0;
  b_z = -std::sqrt(2.0 / (3.1415926535897931 * c_z));
  tau = y_im * b_y_re - b_z * b_y_im;
  b_z = y_im * b_y_im + b_z * b_y_re;
  y_im = std::sqrt(2.0 * b_tau / w) * -0.88622692545275794;
  r = std::sqrt(2.0 * b_tau / w) * 5.4265748378696E-17;
  out.re = 0.31830988618379069 * (b_re * re - y_re * im) + 0.0 * (y_im * tau - r
    * b_z);
  out.im = 0.31830988618379069 * (b_re * im + y_re * re) + 0.0 * (y_im * b_z + r
    * tau);
  return out;
}

//
// Arguments    : void
// Return Type  : void
//
void G3D_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void G3D_terminate()
{
  // (no terminate code required)
}

//
// File trailer for G3D.cpp
//
// [EOF]
//
