#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = 0;
  //Seting up Columns in Matrix A
  Eigen::RowVector3d aMinusb = A - B;
  Eigen::RowVector3d aMinusc = A - C;
  Eigen::RowVector3d aMinuse = A - ray.origin.transpose();

  //Variables for Cramers Rule Solution of Triangle Intersection
  double a = aMinusb[0];
  double b = aMinusb[1];
  double c = aMinusb[2];
  double d = aMinusc[0];
  double e = aMinusc[1];
  double f = aMinusc[2];
  double g = ray.direction[0];
  double h = ray.direction[1];
  double i = ray.direction[2];
  double j = aMinuse[0];
  double k = aMinuse[1];
  double l = aMinuse[2];

  //Solving for M, beta, gamma and t
  double M = a * ((e * i) - (h * f)) + b * ((g * f) - (d * i)) + c * ((d * h) - (e * g));
  if (M == 0) return false;

  double tTemp = (-1.0) * (f * ((a * k) - (j * b)) + e * ((j * c) - (a * l)) + d * ((b * l) - (k * c))) / (M);
  if (tTemp < min_t || tTemp > max_t) return false;

  double gamma = (i * ((a * k) - (j * b)) + h * ((j * c) - (a * l)) + g * ((b * l) - (k * c))) / (M);
  if (gamma < 0 || gamma > 1) return false;

  double beta = (j * ((e * i) - (h * f)) + k * ((g * f) - (d * i)) + l * ((d * h) - (e * g))) / (M);
  if (beta < 0 || beta >(1 - gamma)) return false;

  t = tTemp;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

