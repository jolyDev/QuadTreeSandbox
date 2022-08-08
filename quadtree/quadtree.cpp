#include "quadtree/quadtree.h"

#include <cassert>

QuadTree::QuadTree(BBox<float> bbox)
    : bbox(bbox)
{
}

QuadTree::~QuadTree()
{

}

bool QuadTree::Insert(std::unique_ptr<Object>&& obj) {
    if (!bbox.Contains(obj->bbox.center))
        return false;

    // Directly insert into this node if room and if there are no children
    if (obj_count < CAPACITY && nw == nullptr) {
        nw = std::make_unique<QuadTree>(obj->bbox);
        obj_count++;
        return true;
    }
    else {
        if (obj_count >= CAPACITY)
            Split();

        if (nw->Insert(std::move(obj)))
            return true;

        if (ne->Insert(std::move(obj)))
            return true;

        if (se->Insert(std::move(obj)))
            return true;

        if (sw->Insert(std::move(obj)))
            return true;
    }

    assert(false && "Should not reach here");
    return false;
}

void QuadTree::Split() {
    assert(!nw && !ne && !se && !sw && "all nodes should be nullyfied");
    auto center = bbox.center;
    auto new_size = bbox.size / 2;

    // Split the current tree into 4 by creating 4 children nodes
    nw = std::make_unique<QuadTree>(BBox<float>(center - new_size, new_size));
    nw = std::make_unique<QuadTree>(BBox<float>(center - new_size, new_size));
    nw = std::make_unique<QuadTree>(BBox<float>(center - new_size, new_size));
    nw = std::make_unique<QuadTree>(BBox<float>(center + new_size, new_size));

    for (int i = 0; i < CAPACITY; i++)
    {
        // Get current particle
        // auto p = std::make_unique<Object>(objects[i].get());

        // Try to add to each child (skip the loop iteration once added)

        if (nw->bbox.Contains(objects[i]->bbox.center))
            if (nw->Insert(std::move(objects[i])))
                continue;
            else
                assert(false);

        if (ne->bbox.Contains(objects[i]->bbox.center))
            if (ne->Insert(std::move(objects[i])))
                continue;
            else
                assert(false);

        if (se->bbox.Contains(objects[i]->bbox.center))
            if (se->Insert(std::move(objects[i])))
                continue;
            else
                assert(false);

        if (sw->bbox.Contains(objects[i]->bbox.center))
            if (sw->Insert(std::move(objects[i])))
                continue;
            else
                assert(false);
    }
    this->obj_count = 0; // This is fine, because insert checks for children
    return;
}

void QuadTree::Query(const std::unique_ptr<BBox<float>>& range, std::vector<const Object*>& out) {
    if (!range->Intersects(range))
        return;

    for (int i = 0; i < obj_count; i++) {
        if (range->center.x == objects[i]->bbox.center.x &&
            range->center.x == objects[i]->bbox.center.x) {
            continue;
        }

        if (range->Contains(objects[i]->bbox.center))
            out.push_back(objects[i].get());
    }

    if (!this->nw)
        return;

    nw->Query(range, out);
    ne->Query(range, out);
    se->Query(range, out);
    sw->Query(range, out);
}
