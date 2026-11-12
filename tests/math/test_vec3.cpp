#include <catch2/catch_test_macros.hpp>
#include "tiny_math.hpp"

using namespace tiny;

constexpr float EPSILON = 0.0001f;

TEST_CASE("Vec3 Nearly equal")
{
    const math::vector3d a{1.f, 2.f, 3.f};

    REQUIRE(math::nearly_equal(a, math::vector3d{1.f, 2.00001f, 3.f}, EPSILON));
    REQUIRE_FALSE(math::nearly_equal(a, math::vector3d{1.f, 3.f, 3.f}, EPSILON));
    REQUIRE_FALSE(math::nearly_equal(a, math::vector3d{5.f, 2.f, 3.f}, EPSILON));
}

TEST_CASE("Vec3 Addition")
{
    constexpr math::vector3d a{1.f, 3.f, 3.42f};
    constexpr math::vector3d b{1.f, 5.3f, 10.3f};
    constexpr math::vector3d outcome {2.f, 8.3f, 13.72f};

    SECTION("operator+")
    {
        constexpr auto result = a + b;

        CAPTURE(result);
        REQUIRE(math::nearly_equal(result, outcome, EPSILON));
    }
    SECTION("operator+=")
    {
        auto result = a;

        result += b;

        CAPTURE(result);
        REQUIRE(math::nearly_equal(result, outcome, EPSILON));
    }
}

TEST_CASE("Vec3 Subtraction")
{
    constexpr math::vector3d a{1.f, 2.f, 5.f};
    constexpr math::vector3d b{1.f, 5.3f, 3.f};
    constexpr math::vector3d outcome {0.f, -3.3f, 2.f};

    SECTION("operator-")
    {
        constexpr auto result = a - b;

        CAPTURE(result);
        REQUIRE(math::nearly_equal(result, outcome, EPSILON));
    }
    SECTION("operator-=")
    {
        auto result = a;

        result -= b;

        CAPTURE(result);
        REQUIRE(math::nearly_equal(result, outcome, EPSILON));
    }
}

TEST_CASE("Vec3 Multiplication")
{
    constexpr math::vector3d a{1.f, 2.f, 3.3f};
    constexpr float b{5.3f};
    constexpr math::vector3d outcome{5.3f, 10.6f, 17.49f};

    SECTION("operator*")
    {
        SECTION("vec * scalar")
        {
            constexpr auto result = a * b;

            CAPTURE(result);
            REQUIRE(math::nearly_equal(result, outcome, EPSILON));
        }

        SECTION("scalar * vec")
        {
            constexpr auto result = b * a;

            CAPTURE(result);
            REQUIRE(math::nearly_equal(result, outcome, EPSILON));
        }
    }
    SECTION("operator*=")
    {
        auto result = a;

        result *= b;

        CAPTURE(result);
        REQUIRE(math::nearly_equal(result, outcome, EPSILON));
    }
}

TEST_CASE("Vec3 Division")
{
    constexpr math::vector3d a{1.f, 2.f, 10.4f};
    constexpr float b{4.f};
    constexpr math::vector3d outcome{0.25f, .5f, 2.6f};

    SECTION("operator/")
    {
        constexpr auto result = a / b;

        CAPTURE(result);
        REQUIRE(math::nearly_equal(result, outcome, EPSILON));
    }
    SECTION("operator/=")
    {
        auto result = a;

        result /= b;

        CAPTURE(result);
        REQUIRE(math::nearly_equal(result, outcome, EPSILON));
    }
}

TEST_CASE("Vec3 Negation")
{
    SECTION("Negate")
    {
        constexpr math::vector3d a{-1.f, 2.f, 3.21f};
        constexpr math::vector3d b{1.f, -2.f,-3.21f};

        REQUIRE(-a == b);
    }
}

TEST_CASE("Vec3 length")
{
    constexpr math::vector3d a{2.f, 3.f, 6.f};
    constexpr float length = 7;
    constexpr float length2 = length * length;

    SECTION("length squared")
    {
        REQUIRE(math::nearly_equal(math::length_squared(a), length2, EPSILON));
    }

    SECTION("length")
    {
        REQUIRE(math::nearly_equal(math::length(a), length, EPSILON));
    }
}

TEST_CASE("Vec3 distance")
{
    constexpr math::vector3d a{4.f, 6.f, 3.f};
    constexpr math::vector3d b{1.f, 2.f, 3.f};
    constexpr float distance = 5.f;
    constexpr float distance2 = distance * distance;

    SECTION("distance squared")
    {
        REQUIRE(math::nearly_equal(math::distance_squared(a, b), distance2, EPSILON));
    }

    SECTION("distance")
    {
        REQUIRE(math::nearly_equal(math::distance(a, b), distance, EPSILON));
    }
}

TEST_CASE("Vec3 normalize")
{
    constexpr math::vector3d a{2.f, 3.f, 6.f};
    constexpr math::vector3d unit{.2857f, .4285f, .8571f};

    SECTION("normalize")
    {
        REQUIRE(math::nearly_equal(math::normalize(a), unit, 0.001f));
    }

    SECTION("safe normalize")
    {
        REQUIRE(math::nearly_equal(math::safe_normalize(a), unit, 0.001f));
    }

    SECTION("safe normalize 0 guard")
    {
        math::vector3d zero{0.f};
        REQUIRE(math::nearly_equal(math::safe_normalize(zero), zero, EPSILON));
    }
}