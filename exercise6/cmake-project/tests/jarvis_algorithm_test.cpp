#include <vector>
#include <cassert>
#include <iostream>
#include <jarvis_algorithm.h>

static void test() {
    std::vector<Point> points = {{0, 3},
                                                   {2, 2},
                                                   {1, 1},
                                                   {2, 1},
                                                   {3, 0},
                                                   {0, 0},
                                                   {3, 3}
    };
    geometry::jarvis::Convexhull hull(points);
    std::vector<Point> actualPoint;
    actualPoint = hull.getConvexHull();

    std::vector<Point> expectedPoint = {{0, 3},
                                                          {0, 0},
                                                          {3, 0},
                                                          {3, 3}};
    for (int i = 0; i < expectedPoint.size(); i++) {
        assert(actualPoint[i].x == expectedPoint[i].x);
        assert(actualPoint[i].y == expectedPoint[i].y);
    }
    std::cout << "Test implementations passed!\n";
}

int main() {
    test();
    return 0;
}
