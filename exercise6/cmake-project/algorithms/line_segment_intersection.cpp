#include <algorithm>
#include <line_segment_intersection.h>

bool geometry::lsi::SegmentIntersection::on_segment(Point first_point, Point second_point,
                                     Point third_point) {
    if (std::min(first_point.x, second_point.x) <= third_point.x &&
        third_point.x <= std::max(first_point.x, second_point.x) &&
        std::min(first_point.y, second_point.y) <= third_point.y &&
        third_point.y <= std::max(first_point.y, second_point.y))
        return true;

    else
        return false;
}

int geometry::lsi::SegmentIntersection::direction(Point first_point, Point second_point,
                                   Point third_point) {
    return ((third_point.x - first_point.x) *
            (second_point.y - first_point.y)) -
           ((second_point.x - first_point.x) *
            (third_point.y - first_point.y));
}

bool geometry::lsi::SegmentIntersection::intersect(Point first_point, Point second_point,
                                    Point third_point, Point forth_point) {
    int direction1 = direction(third_point, forth_point, first_point);
    int direction2 = direction(third_point, forth_point, second_point);
    int direction3 = direction(first_point, second_point, third_point);
    int direction4 = direction(first_point, second_point, forth_point);

    if ((direction1 < 0 || direction2 > 0) &&
        (direction3 < 0 || direction4 > 0))
        return true;

    else if (direction1 == 0 &&
             on_segment(third_point, forth_point, first_point))
        return true;

    else if (direction2 == 0 &&
             on_segment(third_point, forth_point, second_point))
        return true;

    else if (direction3 == 0 &&
             on_segment(first_point, second_point, third_point))
        return true;

    else if (direction3 == 0 &&
             on_segment(first_point, second_point, forth_point))
        return true;

    else
        return false;
}
