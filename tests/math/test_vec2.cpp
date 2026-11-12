#include <catch2/catch_test_macros.hpp>
#include "tiny_math.hpp"

using namespace tiny;

constexpr float EPSILON = 0.0001f;

TEST_CASE("Vec2 Nearly equal")
{
    constexpr math::vector2d a{1.f, 2.f};

    REQUIRE(math::nearly_equal(a, math::vector2d{1.f, 2.00001f}, EPSILON));
    REQUIRE_FALSE(math::nearly_equal(a, math::vector2d{1.f, 3.f}, EPSILON));
    REQUIRE_FALSE(math::nearly_equal(a, math::vector2d{5.f, 2.f}, EPSILON));
}

TEST_CASE("Absolute")
{
    constexpr math::vector2d a{-1.f, -2.f};
    constexpr math::vector3d b{-1.f, -2.f, 3.f};
    auto tempA = math::abs(a);
    auto tempB = math::abs(b);

    REQUIRE(tempA == math::vector2d{1.f, 2.f});

    REQUIRE(tempB == math::vector3d{1.f, 2.f, 3.f});
}

TEST_CASE("Vec2 Addition")
{
    constexpr math::vector2d a{1.f, 3.f};
    constexpr math::vector2d b{1.f, 5.3f};
    constexpr math::vector2d outcome{2.f, 8.3f};

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

TEST_CASE("Vec2 Subtraction")
{
    constexpr math::vector2d a{1.f, 2.f};
    constexpr math::vector2d b{1.f, 5.3f};
    constexpr math::vector2d outcome{0.f, -3.3f};

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

TEST_CASE("Vec2 Multiplication")
{
    constexpr math::vector2d a{1.f, 2.f};
    constexpr float b{5.3f};
    constexpr math::vector2d outcome{5.3f, 10.6f};

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

TEST_CASE("Vec2 Division")
{
    constexpr math::vector2d a{1.f, 2.f};
    constexpr float b{4.f};
    constexpr math::vector2d outcome{.25f, .5f};

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

TEST_CASE("Vec2 Negation")
{
    SECTION("Negate")
    {
        constexpr math::vector2d a{-1.f, 2.f};
        constexpr math::vector2d b{1.f, -2.f};

        REQUIRE(-a == b);
    }
}

TEST_CASE("Vec2 length")
{
    constexpr math::vector2d a{3.f, 4.f};
    constexpr float length = 5.f;
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

TEST_CASE("Vec2 distance")
{
    constexpr math::vector2d a{5.f, 0.f};
    constexpr math::vector2d b{-1.f, 8.f};
    constexpr float distance = 10.f;
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

TEST_CASE("Vec2 normalize")
{
    constexpr math::vector2d a{12.f, -5.f};
    constexpr math::vector2d unit{.923f, -.385f};

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
        math::vector2d zero{0.f,0.f};
        REQUIRE(math::nearly_equal(math::safe_normalize(zero), zero, EPSILON));
    }
}