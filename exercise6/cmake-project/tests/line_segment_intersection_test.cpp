#include <iostream>
#include <line_segment_intersection.h>

/**
 * This is the main function to test whether the algorithm is
 * working well.
 */
int main() {
    geometry::lsi::SegmentIntersection segment;
    Point first_point{}, second_point{}, third_point{}, forth_point{};

    std::cin >> first_point.x >> first_point.y;
    std::cin >> second_point.x >> second_point.y;
    std::cin >> third_point.x >> third_point.y;
    std::cin >> forth_point.x >> forth_point.y;

    printf("%d", segment.intersect(first_point, second_point, third_point,
                                   forth_point));
    std::cout << std::endl;
}
