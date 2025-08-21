#define CATCH_CONFIG_MAIN  // provides main()
#include "catch_amalgamated.hpp"
#include "globals.h" // or wherever your Vec3 is
#include <iostream>
#include "engine/backend/cpu/transformations.h"

#include "engine/window.h"

using namespace Catch;

using namespace std;


TEST_CASE("vertexWorldToScreen") {

    Window window(640, 480);
    float fov = 90;
    Camera camera(Vec3{0, 0, -3}, fov);

    SECTION("Basic test") {
        Vec3 coords = {0, 0, 0};

        
        Point point = vertexWorldToScreen(&window, &camera, &coords);


        REQUIRE(point.x == -1);
        REQUIRE(point.y == 240);

        
    }

}

TEST_CASE("Vec3 basic operations") {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);

    SECTION("Addition works") {
        Vec3 c = a + b;
        REQUIRE(c.x == Approx(5));
        REQUIRE(c.y == Approx(7));
        REQUIRE(c.z == Approx(9));
    }

    SECTION("Dot product works") {
        REQUIRE(a.dot(b) == Approx(32)); // 1*4 + 2*5 + 3*6
    }

    SECTION("Cross product works") {
        Vec3 c = a.cross(b);
        REQUIRE(c.x == Approx(-3));
        REQUIRE(c.y == Approx(6));
        REQUIRE(c.z == Approx(-3));
    }
}