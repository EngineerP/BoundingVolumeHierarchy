#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <iostream>
AABBTree::AABBTree(
	const std::vector<std::shared_ptr<Object> >& objects,
	int a_depth) :
	depth(std::move(a_depth)),
	num_leaves(objects.size())
{
	////////////////////////////////////////////////////////////////////////////
	// Add your code here
	// Add all objects to the box
	//Check to see if the array has 1 or 2 objects and construct accordingly
	int n = objects.size();
	if (n == 0) {
		this->left = NULL;
		this->right = NULL;
	}
	else if (n == 1) {
		this->left = objects[0];
		this->right = NULL;
		insert_box_into_box(objects[0]->box, this->box);
	}
	else if (n == 2) {
		this->left = objects[0];
		this->right = objects[1];
		insert_box_into_box(objects[0]->box, this->box);
		insert_box_into_box(objects[1]->box, this->box);
	}
	else {
		// Add all objects to the box
		for (int i=0; i < objects.size(); i++) {
			insert_box_into_box(objects[i]->box, this->box);
		}
		// Determine which is the longest axis
		double xRange = std::fabs(this->box.max_corner[0] - this->box.min_corner[0]);
		double yRange = std::fabs(this->box.max_corner[1] - this->box.min_corner[1]);
		double zRange = std::fabs(this->box.max_corner[2] - this->box.min_corner[2]);
		//std::cout << "Depth: " << depth << "\n";
		//std::cout << "xRange: " << xRange << ", yRange:" << yRange << ", zRange: " << zRange << "\n";
		int axis = -1;
		if (xRange > std::fmax(yRange, zRange)) axis = 0;
		else if (yRange > std::fmax(xRange, zRange)) axis = 1;
		else axis = 2;

		//Partition Objects into two arrays, based on the whether they are one the right of left of the split axis
		std::vector<std::shared_ptr<Object>> leftObjects;
		std::vector<std::shared_ptr<Object>> rightObjects;
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->box.center()[axis] > this->box.center()[axis]) leftObjects.emplace_back(objects[i]);
			else rightObjects.emplace_back(objects[i]);
		}

		// ***** CATCH EDGE CASE IF ALL OBJECTS ARE IN ONE LEFT/RIGHT TREE******
		if (rightObjects.size() == 0) {
			rightObjects.emplace_back(leftObjects.back());
			leftObjects.pop_back();
		}
		else if (leftObjects.size() == 0) {
			leftObjects.emplace_back(rightObjects.back());
			rightObjects.pop_back();
		}

		//Create the Left and Right Sub-AABB Trees
		if (leftObjects.size() != 0) {
			this->left = std::make_shared<AABBTree>(leftObjects, this->depth + 1);
			insert_box_into_box(this->left->box, this->box);
		}
		else this->left = NULL;

		if (rightObjects.size() != 0) {
			this->right = std::make_shared<AABBTree>(rightObjects, this->depth + 1);
			insert_box_into_box(this->right->box, this->box);
		}
		else this->right = NULL;
	}
	////////////////////////////////////////////////////////////////////////////
}
