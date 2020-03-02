#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <iostream>

bool ray_intersect_triangle_mesh_brute_force(
	const Ray& ray,
	const Eigen::MatrixXd& V,
	const Eigen::MatrixXi& F,
	const double min_t,
	const double max_t,
	double& hit_t,
	int& hit_f)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	hit_t = std::numeric_limits<double>::infinity();
	hit_f = 0;
	bool hit = false;
	// Loop through the faces to see if they intersect
	for (int i = 0; i < F.rows(); i++) {
		//Construct and Eigen:Vector3d for the vertices A, B and C
		Eigen::Vector3d A = V.row(F(i, 0));
		Eigen::Vector3d B = V.row(F(i, 1));
		Eigen::Vector3d C = V.row(F(i, 2));
		double temp_t = std::numeric_limits<double>::infinity();
		//Call ray_intersect_triangle to see if this face intersects
		if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, temp_t)) {
			//If it is the closest one so far, log it
			if (temp_t < hit_t) {
				hit_t = temp_t;
				hit_f = i;
				hit = true;
			}
		}
	}
	return hit;
	////////////////////////////////////////////////////////////////////////////
}
