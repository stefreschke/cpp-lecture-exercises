
#include <fstream>
#include <iostream>
#include <string>
#include <array>

#include "CubicBezierCurve.h"


void draw(const CubicBezierCurve & curve, const std::string & filename)
{
    auto output = std::ofstream{ filename };
    if (!output)
    {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    auto image = std::array<std::array<char, 100>, 50>{};
    for (auto & line : image)
    {
        std::fill(line.begin(), line.end(), ' ');
    }

    for (auto t = 0.0; t <= 1.0; t += 1.0 / 256.0)
    {
        const auto point = curve(t);

        // TODO: update these to use your class interface
        const auto x = std::lround(point[0]);
        const auto y = std::lround(point[1]);

        image[y][x] = 'X';
    }

    for (const auto & line : image)
    {
        output.write(line.data(), line.size());
        output.put('\n');
    }
}


CubicBezierCurve createTestCurve()
{
    // TODO: update this to use your class interface
    auto c1 = CubicBezierCurve{
        {  0.0,  0.0, 0.0 },
        { 15.0, 48.0, 0.4 },
        { 73.0,  7.0, 0.8 },
        { 99.0, 49.0, 0.0 }
    };

    return c1;
}


int main(int argc, char * argv[])
{
    auto c1 = createTestCurve();
    auto c2 = c1;

    // TODO: update these to use your class interface
    c1.setControlPoint(0, { 99.0, 49.0, 0.0 });
    c1.setControlPoint(3, {  0.0,  0.0, 0.0 });

    draw(c1, "c1.txt");
    draw(c2, "c2.txt");
}
