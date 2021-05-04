#include <gtest/gtest.h>
#include "montecarlopi.h"

TEST(RandomNumberGenerator, ProducesCoordinatesOneAndZero) {
    RandomNumberGenerator<float> numberGenerator;
    std::pair<float, float> coords = numberGenerator.create_random_number();
    EXPECT_LT(coords.first, 1);
    EXPECT_GT(coords.first, 0);
    EXPECT_LT(coords.second, 1);
    EXPECT_GT(coords.second, 0);
}

TEST(DistanceCalculator, GivesValidDistanceForCirclePoints) {
    DistanceCalculator<float> distanceCalculator;
    std::pair<float, float> coords{1, 0};
    EXPECT_FLOAT_EQ(distanceCalculator.distance(coords), 1);
    coords = {0, 1};
    EXPECT_FLOAT_EQ(distanceCalculator.distance(coords), 1);
}

TEST(DistanceCalculator, GivesValidDistanceForPointInTheCircle) {
    DistanceCalculator<float> distanceCalculator;
    std::pair<float, float> coords{0.5, 0.5};
    double distance = distanceCalculator.distance(coords);
    EXPECT_LT(distance, 1);
}

TEST(DistanceCalculator, GivesValidDistanceForMaxPoint) {
    DistanceCalculator<float> distanceCalculator;
    std::pair<float, float> coords{0.8, 0.8};
    double distance = distanceCalculator.distance(coords);
    EXPECT_GT(distance, 1);
}

TEST(PiApprox, Converges) {
    PiApprox<long double> piApprox;
    piApprox.approx();
    EXPECT_GT(piApprox.retrieveLastResult(), 3);
    EXPECT_LT(piApprox.retrieveLastResult(), 4);
}

//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
