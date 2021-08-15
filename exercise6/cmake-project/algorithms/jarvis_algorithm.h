


#include <geometries.h>

namespace geometry {
    namespace jarvis {
        class Convexhull {
            std::vector<Point> points;
            int size;
        public:
            explicit Convexhull(const std::vector<Point> &pointList) {
                points = pointList;
                size = points.size();
            }
            std::vector<Point> getConvexHull() const;
            static int orientation(const Point &p, const Point &q, const Point &r);
        };
    }
}
