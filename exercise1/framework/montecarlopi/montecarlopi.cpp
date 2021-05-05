
#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

constexpr int RANDOM_MIN = 0;
constexpr int RANDOM_MAX = 1;

using std::setprecision;

template<typename T> struct RandomNumberGenerator {
    std::pair<T, T> create_random_number() {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<T> distr(RANDOM_MIN, RANDOM_MAX);
        return std::pair<T, T>{ distr(eng),  distr(eng)};
    }
};


template<typename T> struct DistanceCalculator {
    T distance(std::pair<T, T> coords) {
        return sqrt(pow(coords.first, 2.0) + pow(coords.second, 2.0));
    }
};


template<typename T> class PiApprox {
public:
    T approx() {
        initializeNewApproximation();
        actuallyPerformApproximation();
    }
    T retrieveLastResult() {
        return approximationResult;
    }
    long retrieveGeneratedPoints() {
        return pointsGenerated;
    }
private:
    T approximationResult;
    long pointsGenerated;
    long pointsInCircle;
    long stableApproximationForRounds;
    DistanceCalculator<float> distanceCalculator;
    RandomNumberGenerator<float> randomNumberGenerator;
    bool nextPoint() {
        return (distanceCalculator.distance(randomNumberGenerator.create_random_number()) <= 1);
    }
    bool currentApproximationIsStable(T newResult) const {
        // return newResult == approximationResult;
        return newResult >= 3.1413 && newResult <= 3.1419;
    }
    void initializeNewApproximation() {
        approximationResult = 0;
        pointsGenerated = 0;
        pointsInCircle = 0;
        stableApproximationForRounds = 0;
    }
    T actuallyPerformApproximation() {
        while (stableApproximationForRounds < 10000) {
            ++pointsGenerated;
            if (nextPoint()) {
                ++pointsInCircle;
            }
            T newResult = (1.0 * pointsInCircle / pointsGenerated) * 4.0;
            if (currentApproximationIsStable(newResult)) {
                stableApproximationForRounds++;
            } else {
                stableApproximationForRounds = 0;
            }
            if (pointsGenerated > 10e8) {
                exit(1);
            }
            approximationResult = newResult;
        }
    }
};

template class PiApprox<float>;
template class PiApprox<double>;
template class PiApprox<long double>;


int monteCarlo_float() {
	PiApprox<float> piApprox;
	piApprox.approx();
	return piApprox.retrieveGeneratedPoints();
}

int monteCarlo_double() {
    PiApprox<double> piApprox;
    piApprox.approx();
    return piApprox.retrieveGeneratedPoints();
}

int monteCarlo_long_double() {
    PiApprox<long double> piApprox;
    piApprox.approx();
    return piApprox.retrieveGeneratedPoints();
}

#include <limits>

int main(int argc, char * argv[])
{
	std::cout << "Float Tries: " <<  monteCarlo_float() << std::endl;
	std::cout << "Double Tries: " << monteCarlo_double() << std::endl;
	std::cout << "Long Double Tries: " << monteCarlo_long_double() << std::endl;
	
    std::cout.precision(std::numeric_limits<float>::max_digits10);
	std::cout << "(in-) Exact Output of float Pi: " << E_PI << std::endl;

    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << "(in-) Exact Output of float Pi: " << E_PI << std::endl;

    std::cout.precision(std::numeric_limits<long double>::max_digits10);
    std::cout << "(in-) Exact Output of float Pi: " << E_PI << std::endl;
	return 0;
}
