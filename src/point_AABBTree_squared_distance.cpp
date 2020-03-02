#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
// Compute the distrance from a query point to the objects stored in a AABBTree
// using a priority queue. **_note:** this function is _not_ meant to be called
// recursively._
//
// Inputs:
//   query  3D query point
//   root  pointer to root of an AABB tree 
//   min_sqrd  minimum squared distance to consider (often 0)
//   max_sqrd  maximum squared distance to consider (often infinity)
// Outputs
//   sqrd  squared distance 
//   descendant  if minimal distance was found at a descendant, pass along a
//     pointer to that descendant (only necessary for hierarchical Objects)
/*// initialize a queue prioritized by minimum distance
d_r ← distance to root's box
Q.insert(d_r, root)
// initialize minimum distance seen so far
d ← ∞
while Q not empty
  // d_s: distance from query to subtree's bounding box
  (d_s, subtree) ← Q.pop
  if d_s < d
	if subtree is a leaf
	  d ← min[ d , distance from query to leaf object ]
	else
	  d_l ← distance to left's box
	  Q.insert(d_l ,subtree.left)
	  d_r ← distance to right's box
	  Q.insert(d_r ,subtree.right)*/
bool point_AABBTree_squared_distance(
	const Eigen::RowVector3d& query,
	const std::shared_ptr<AABBTree>& root,
	const double min_sqrd,
	const double max_sqrd,
	double& sqrd,
	std::shared_ptr<Object>& descendant)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code here
	typedef std::pair<double, std::shared_ptr<Object>> distPair;
	std::priority_queue<distPair, std::vector<distPair>, std::greater<distPair>> distQ;
	//Put in the distance to the root
	distQ.push(std::make_pair(point_box_squared_distance(query, root->box), std::dynamic_pointer_cast<AABBTree>(root)));
	double minDist = std::numeric_limits<double>::infinity();
	while (!distQ.empty()) {
		distPair subTree = distQ.top();
		distQ.pop();
		if (subTree.first < minDist) {
			std::shared_ptr<AABBTree> aabb = std::dynamic_pointer_cast<AABBTree>(subTree.second);
			if (aabb) {
				if (aabb->left != NULL)
					distQ.push(std::make_pair(point_box_squared_distance(query, aabb->left->box), aabb->left));
				if (aabb->right != NULL)
					distQ.push(std::make_pair(point_box_squared_distance(query, aabb->right->box),aabb->right));
			}
			else {
				double objDist = std::numeric_limits<double>::infinity();
				std::shared_ptr<Object> tempObject;
				if (subTree.second->point_squared_distance(query, min_sqrd, max_sqrd, objDist, tempObject))
					if (objDist < minDist) {
						minDist = objDist;
						descendant = subTree.second;
					}
			}
		}
	}

	if (descendant != NULL) {
		sqrd = minDist;
		return true;
	}
	else return false;
	////////////////////////////////////////////////////////////////////////////
}