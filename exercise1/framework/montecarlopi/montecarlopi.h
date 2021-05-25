
#ifndef EXERCISE_1_1_MONTECARLO_PI_MONTECARLOPI_H
#define EXERCISE_1_1_MONTECARLO_PI_MONTECARLOPI_H

template<typename T> struct RandomNumberGenerator {
    std::pair<T, T> create_random_number();
};

template<typename T> struct DistanceCalculator {
    T distance(std::pair<T, T> coords);
};

template<typename T> struct PiApprox {
    T approx();
    T retrieveLastResult();
    long retrieveGeneratedPoints();
};

#endif //EXERCISE_1_1_MONTECARLO_PI_MONTECARLOPI_H
