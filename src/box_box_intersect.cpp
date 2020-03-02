#include "box_box_intersect.h"

bool box_box_intersect(
	const BoundingBox& A,
	const BoundingBox& B)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	// For the boxes to intersect, the min-max intervals for all axes must overlap
	for (int i = 0; i < 3; i++) {
		// If any axis interval does not over lap. the boxes do not intersect
		if (!(A.max_corner[i] >= B.min_corner[i] && B.max_corner[i] >= A.min_corner[i])) return false;
	}
	return true;
		////////////////////////////////////////////////////////////////////////////
}

