#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
	const Eigen::RowVector3d& a,
	const Eigen::RowVector3d& b,
	const Eigen::RowVector3d& c,
	BoundingBox& B)
{
	////////////////////////////////////////////////////////////////////////////
	// Add your code here
	//Check the min value of the three vertices and make sure the bounding box's min corner is less than them
	double minXVertex = std::fmin(a[0], std::fmin(b[0], c[0]));
	double minYVertex = std::fmin(a[1], std::fmin(b[1], c[1]));
	double minZVertex = std::fmin(a[2], std::fmin(b[2], c[2]));

	if (B.min_corner[0] > minXVertex) B.min_corner[0] = minXVertex;
	if (B.min_corner[1] > minYVertex) B.min_corner[1] = minYVertex;
	if (B.min_corner[2] > minZVertex) B.min_corner[2] = minZVertex;

	//Check the max value of the three vertices and make sure the bounding box's max corner is more than them
	double maxXVertex = std::fmax(a[0], std::fmax(b[0], c[0]));
	double maxYVertex = std::fmax(a[1], std::fmax(b[1], c[1]));
	double maxZVertex = std::fmax(a[2], std::fmax(b[2], c[2]));

	if (B.max_corner[0] < maxXVertex) B.max_corner[0] = maxXVertex;
	if (B.max_corner[1] < maxYVertex) B.max_corner[1] = maxYVertex;
	if (B.max_corner[2] < maxZVertex) B.max_corner[2] = maxZVertex;
	
	////////////////////////////////////////////////////////////////////////////
}


