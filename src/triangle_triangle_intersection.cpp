#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
	const Eigen::RowVector3d& A0,
	const Eigen::RowVector3d& A1,
	const Eigen::RowVector3d& A2,
	const Eigen::RowVector3d& B0,
	const Eigen::RowVector3d& B1,
	const Eigen::RowVector3d& B2)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	//Create "Rays" using the vertex to vertex direction vectors as the ray directions, 1 "ray" for each side
	Ray A0to1(A0, A1 - A0);
	Ray A1to2(A1, A2 - A1);
	Ray A2to0(A2, A0 - A2);
	Ray B0to1(B0, B1 - B0);
	Ray B1to2(B1, B2 - B1);
	Ray B2to0(B2, B0 - B2);
	//Check if the rays intersect the triangle
	// if any ray intersects the triangle, the triangles intersect
	double tTemp = 0;
	if (ray_intersect_triangle(A0to1, B0, B1, B2, 0, 1, tTemp) ||
		ray_intersect_triangle(A1to2, B0, B1, B2, 0, 1, tTemp) ||
		ray_intersect_triangle(A2to0, B0, B1, B2, 0, 1, tTemp) ||
		ray_intersect_triangle(B0to1, A0, A1, A2, 0, 1, tTemp) ||
		ray_intersect_triangle(B1to2, A0, A1, A2, 0, 1, tTemp) ||
		ray_intersect_triangle(B2to0, A0, A1, A2, 0, 1, tTemp))
		return true;
	else
		return false;
	////////////////////////////////////////////////////////////////////////////
}
