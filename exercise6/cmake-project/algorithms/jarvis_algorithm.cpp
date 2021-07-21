#include <vector>
#include "jarvis_algorithm.h"


std::vector<Point> geometry::jarvis::Convexhull::getConvexHull() const {
    std::vector<Point> hull;
    int leftmost_point = 0;
    for (int i = 1; i < size; i++) {
        if (points[i].x < points[leftmost_point].x) {
            leftmost_point = i;
        }
    }
    int p = leftmost_point, q = 0;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % size;
        for (int i = 0; i < size; i++) {
            // If i is more counterclockwise than current q, then
            // update q
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }
        p = q;

    } while (p != leftmost_point);
    return hull;
}

int geometry::jarvis::Convexhull::orientation(const Point &p, const Point &q,
                                              const Point &r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) {
        return 0;
    }
    return (val > 0) ? 1 : 2;
}

