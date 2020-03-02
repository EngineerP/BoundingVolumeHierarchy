#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
	const std::shared_ptr<AABBTree>& rootA,
	const std::shared_ptr<AABBTree>& rootB,
	std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > >&
	leaf_pairs)
{
	////////////////////////////////////////////////////////////////////////////
	// Add your code here
	//  // initialize list of candidate leaf pairs
	std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> queue;
	// Check top level root
	if (box_box_intersect(rootA->box, rootB->box)) {
		queue.push_back(std::make_pair(rootA, rootB));
	}
	while (!queue.empty()) {
		std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> nodes = queue.front();
		queue.pop_front();
		std::shared_ptr<AABBTree> nodeA = std::dynamic_pointer_cast<AABBTree>(nodes.first);
		std::shared_ptr<AABBTree> nodeB = std::dynamic_pointer_cast<AABBTree>(nodes.second);
		if (nodeA == NULL && nodeB == NULL) //A AND B are leaves
			leaf_pairs.emplace_back(nodes);
		else if (nodeA == NULL) { //only A is a leaf
			if (nodeB->left != NULL && box_box_intersect(nodeB->left->box, nodes.first->box)) {
				queue.push_back(std::make_pair(nodes.first, nodeB->left));
			}
			if (nodeB->right != NULL && box_box_intersect(nodeB->right->box, nodes.first->box)) {
				queue.push_back(std::make_pair(nodes.first, nodeB->right));
			}
		}
		else if (nodeB == NULL) { //only B is a Leaf
			if (nodeA->left != NULL && box_box_intersect(nodeA->left->box, nodes.second->box)) {
				queue.push_back(std::make_pair(nodeA->left, nodes.second));
			}
			if (nodeA->right != NULL && box_box_intersect(nodeA->right->box, nodes.second->box)) {
				queue.push_back(std::make_pair(nodeA->right, nodes.second));
			}
		}
		else { // Neither are leaves
			if (nodeA->left && nodeB->left && box_box_intersect(nodeA->left->box, nodeB->left->box))
				queue.push_back(std::make_pair(nodeA->left, nodeB->left));
			if (nodeA->left && nodeB->right && box_box_intersect(nodeA->left->box, nodeB->right->box))
				queue.push_back(std::make_pair(nodeA->left, nodeB->right));
			if (nodeA->right && nodeB->right && box_box_intersect(nodeA->right->box, nodeB->right->box))
				queue.push_back(std::make_pair(nodeA->right, nodeB->right));
			if (nodeA->right && nodeB->left && box_box_intersect(nodeA->right->box, nodeB->left->box))
				queue.push_back(std::make_pair(nodeA->right, nodeB->left));
		}
	}
	////////////////////////////////////////////////////////////////////////////
}
