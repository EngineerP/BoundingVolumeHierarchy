#include "point_box_squared_distance.h"

double point_box_squared_distance(
	const Eigen::RowVector3d& query,
	const BoundingBox& box)
{
	////////////////////////////////////////////////////////////////////////////
	double dSqr = 0;
	Eigen::RowVector3d dVect = { 0.0,0.0,0.0 };
	//Loop through the Axis
	for (int i = 0; i < 3; i++) {
		//If the point for any given axis lies between the interval of min and max
		if ((query(i) <= box.max_corner(i) && query(i) >= box.min_corner(i)) || (query(i) >= box.max_corner(i) && query(i) <= box.min_corner(i))) {
			//Vector component to the box for that axis is 0
			dVect(i) = 0.0;
		}
		//If not between interval, the vector component to box is the lower of the |point - min/max|
		else if(fabs(query(i) - box.max_corner(i)) < fabs(query(i) - box.min_corner(i))) dVect(i) = query(i) - box.max_corner(i);
		else dVect(i) = query(i) - box.min_corner(i);
	}
	//Square norm to get distance
	return dVect.squaredNorm();
	////////////////////////////////////////////////////////////////////////////
}
