#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
	const Ray& ray,
	const BoundingBox& box,
	const double min_t,
	const double max_t)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	double a = 1 / (ray.direction[0]);
	double b = 1 / (ray.direction[1]);
	double c = 1 / (ray.direction[2]);
	
	//Calculate intersectional ranges
	double tXMin = std::numeric_limits<double>::infinity();
	double tXMax = -std::numeric_limits<double>::infinity();
	if (a >= 0) {
		tXMin = a * (box.min_corner[0] - ray.origin[0]);
		tXMax = a * (box.max_corner[0] - ray.origin[0]);
	}
	else {
		tXMax = a * (box.min_corner[0] - ray.origin[0]);
		tXMin = a * (box.max_corner[0] - ray.origin[0]);
	}

	double tYMin = std::numeric_limits<double>::infinity();
	double tYMax = -std::numeric_limits<double>::infinity();
	if (b >= 0) {
		tYMin = b * (box.min_corner[1] - ray.origin[1]);
		tYMax = b * (box.max_corner[1] - ray.origin[1]);
	}
	else {
		tYMax = b * (box.min_corner[1] - ray.origin[1]);
		tYMin = b * (box.max_corner[1] - ray.origin[1]);
	}

	double tZMin = std::numeric_limits<double>::infinity();
	double tZMax = -std::numeric_limits<double>::infinity();
	if (c >= 0) {
		tZMin = c * (box.min_corner[2] - ray.origin[2]);
		tZMax = c * (box.max_corner[2] - ray.origin[2]);
	}
	else {
		tZMax = c * (box.min_corner[2] - ray.origin[2]);
		tZMin = c * (box.max_corner[2] - ray.origin[2]);
	}

	double tParaMax = std::fmin(tXMax, std::fmin(tYMax, tZMax));
	double tParaMin = std::fmax(tXMin, std::fmax(tYMin, tZMin));

	//If the intersectional ranges for each dimension do not intersect, there is no intersection
	if (tParaMax < tParaMin) return false;

	//If the intersectional range is outside of the tmin-tmax range, there is no intersection
	if ((min_t > tParaMax) || (max_t < tParaMin)) return false;
	
	return true;
	////////////////////////////////////////////////////////////////////////////
}
