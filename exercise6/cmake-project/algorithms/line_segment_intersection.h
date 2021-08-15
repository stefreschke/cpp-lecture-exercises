
#include <algorithm>
#include <iostream>
#include <geometries.h>

namespace geometry {
    namespace lsi {
        struct SegmentIntersection {
        public:
            inline bool intersect(Point first_point, Point second_point,
                                  Point third_point, Point forth_point);
            inline int direction(Point first_point, Point second_point,
                                 Point third_point);
            inline bool on_segment(Point first_point, Point second_point,
                                   Point third_point);
        };
    }
}

