#include "AABBTree.h"

bool AABBTree::ray_intersect(
	const Ray& ray,
	const double min_t,
	const double max_t,
	double& t,
	std::shared_ptr<Object>& descendant) const
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here:
	t = 0;

	if (ray_intersect_box(ray, this->box, min_t, max_t)) {
		double leftT = std::numeric_limits<double>::infinity();
		std::shared_ptr<Object> leftDescendant;
		bool leftHit = this->left != NULL && this->left->ray_intersect(ray, min_t, max_t, leftT, leftDescendant);
		if (leftHit && leftDescendant == NULL) leftDescendant = this->left;

		double rightT = std::numeric_limits<double>::infinity();
		std::shared_ptr<Object> rightDescendant;
		bool rightHit = this->right != NULL && this->right->ray_intersect(ray, min_t, max_t, rightT, rightDescendant);
		if (rightHit && rightDescendant == NULL) rightDescendant = this->right;
		if (leftHit && rightHit) {
			if (leftT < rightT) {
				t = leftT;
				descendant = leftDescendant;
			}
			else {
				t = rightT;
				descendant = rightDescendant;
			}
			return true;
		}
		else if (leftHit) {
			t = leftT;
			descendant = leftDescendant;
			return true;
		}
		else if (rightHit) {
			t = rightT;
			descendant = rightDescendant;
			return true;
		}
		else return false;
	}
	else return false;
	////////////////////////////////////////////////////////////////////////////
}

