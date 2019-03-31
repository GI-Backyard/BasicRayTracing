//
//  bvhNode.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/31.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "bvhNode.hpp"

int boxXCompare(const void* b0, const void* b1) {
    AABB boxB0, boxB1;
    Hitable* hb0 = *(Hitable**) b0;
    Hitable* hb1 = *(Hitable**) b1;
    if(!hb0->bounding_box(0, 0, boxB0) || !hb1->bounding_box(0, 0, boxB1)) {
        std::cerr << "No Bounding Box in BVH constructor.";
    }
    
    if(boxB0.min().x() < boxB1.min().x()) return -1;
    return 1;
}

int boxYCompare(const void* b0, const void* b1) {
    AABB boxB0, boxB1;
    Hitable* hb0 = *(Hitable**) b0;
    Hitable* hb1 = *(Hitable**) b1;
    if(!hb0->bounding_box(0, 0, boxB0) || !hb1->bounding_box(0, 0, boxB1)) {
        std::cerr << "No Bounding Box in BVH constructor.";
    }
    
    if(boxB0.min().y() < boxB1.min().y()) return -1;
    return 1;
}

int boxZCompare(const void* b0, const void* b1) {
    AABB boxB0, boxB1;
    Hitable* hb0 = *(Hitable**) b0;
    Hitable* hb1 = *(Hitable**) b1;
    if(!hb0->bounding_box(0, 0, boxB0) || !hb1->bounding_box(0, 0, boxB1)) {
        std::cerr << "No Bounding Box in BVH constructor.";
    }
    
    if(boxB0.min().z() < boxB1.min().z()) return -1;
    return 1;
}

BVHNode::BVHNode(Hitable** ll, int n, float t0, float t1) {
    int axis = int(3* drand48());
    if (axis == 0) {
        qsort(ll, n, sizeof(Hitable*), boxXCompare);
    } else if(axis ==1) {
        qsort(ll, n, sizeof(Hitable*), boxYCompare);
    } else {
        qsort(ll, n, sizeof(Hitable*), boxZCompare);
    }
    if(n == 1) {
        left = right = ll[0];
    } else if( n == 2) {
        left = ll[0];
        right = ll[1];
    } else {
        left = new BVHNode(ll, n / 2, t0, t1);
        right = new BVHNode( ll + n / 2, n - n / 2, t0, t1);
    }
    
    AABB boxLeft, boxRight;
    if(!left->bounding_box(t0, t1, boxLeft) || !right->bounding_box(t0, t1, boxRight)) {
        std::cerr << "No Bounding Box in BVH constructor.";
    }
    box = AABB::surroundingBox(boxLeft, boxRight);
}

bool BVHNode::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    if(!box.hit(r, tMin, tMax)) return false;
    HitRecord leftRec, rightRec;
    bool hitLeft = left->hit(r, tMin, tMax, leftRec);
    bool hitRight = right->hit(r, tMin, tMax, rightRec);
    if(hitLeft && hitRight) {
        if(leftRec.t < rightRec.t) rec = leftRec;
        else rec = rightRec;
        return true;
    } else if(hitLeft) {
        rec = leftRec;
        return true;
    } else if( hitRight) {
        rec = rightRec;
        return true;
    } else return false;
}

bool BVHNode::bounding_box(float t0, float t1, AABB& bb) const {
    bb = box;
    return true;
}
