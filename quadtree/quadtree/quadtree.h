#pragma once

#include "export.h"
#include "objects.h"

#include <array>
#include <vector>

class DLIB_EXPORT QuadTree {
public:
	QuadTree(BBox<float> bbox);
	~QuadTree();

	static constexpr int CAPACITY = 4;

	int obj_count = 0;

	BBox<float> bbox;

	std::array<std::unique_ptr<Object>, 4> objects = {nullptr, nullptr, nullptr, nullptr};

	std::unique_ptr<QuadTree> nw = nullptr; // North West
	std::unique_ptr<QuadTree> ne = nullptr; // North East
	std::unique_ptr<QuadTree> se = nullptr; // South East
	std::unique_ptr<QuadTree> sw = nullptr; // South West

	bool Insert(std::unique_ptr<Object>&& obj);
	void Query(const std::unique_ptr<BBox<float>>& range, std::vector<const Object*>& out);

private:
	void Split();
};
