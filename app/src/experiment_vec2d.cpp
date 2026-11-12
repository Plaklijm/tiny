#include "helper.hpp"
#include "tiny_experiment.hpp"

using namespace tiny;

class vector2_addition_experiment : public tiny_experiment
{
    draggable_point& a;
    draggable_point& b;

public:
    explicit vector2_addition_experiment(experiment_context* context) : tiny_experiment(context),
                                                                        a(add_point({5.f, 5.f})),
                                                                        b(add_point({8.f, 6.f}))
    {
    }

    void draw() override
    {
        // Get some wrapper functions that do the conversion themselves, from tiny math to actual, and from math to world
        const auto result = a.position + b.position;

        // Vector Af
        draw_vector_2d(m_origin_zero, a.position, GREEN);
        draw_text_2d("Va", a.position * .5f, RAYWHITE);

        draw_vector_2d(m_origin_zero, b.position, BLUE);
        draw_text_2d("Vb", b.position * 0.5f, RAYWHITE);

        draw_dotted_2d(a.position, result, YELLOW);
        draw_dotted_2d(b.position, result, YELLOW);

        draw_vector_2d(m_origin_zero, result, RED);
        draw_text_2d("Va + Vb", result * .5f, RAYWHITE);
        draw_text_2d(to_string(result).c_str(), result, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_addition_experiment(context);
    }
};

static int vector2d_addition = register_experiment("vector2d", "vector2 addition",
                                                   experiment_type::TWO_DIMENSIONAL,
                                                   vector2_addition_experiment::create);

class vector2_subtraction_experiment : public tiny_experiment
{
    draggable_point& a;
    draggable_point& b;

public:
    explicit vector2_subtraction_experiment(experiment_context* context) : tiny_experiment(context),
                                                                           a(add_point({5.f, 5.f})),
                                                                           b(add_point({8.f, 6.f}))
    {
    }

    void draw() override
    {
        // Get some wrapper functions that do the conversion themselves, from tiny math to actual, and from math to world
        const auto result = a.position - b.position;

        draw_vector_2d(m_origin_zero, a.position, GREEN);
        draw_text_2d("Va", a.position * .5f, RAYWHITE);

        draw_vector_2d(m_origin_zero, result, RED);
        draw_text_2d("Va - Vb", result * 0.5f, RAYWHITE);
        draw_text_2d(to_string(result).c_str(), result, RAYWHITE);

        draw_dotted_2d(b.position, a.position, YELLOW);
        draw_dotted_2d(a.position, result, YELLOW);

        draw_vector_2d(m_origin_zero, b.position, BLUE);
        draw_text_2d("Vb", b.position * .5f, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_subtraction_experiment(context);
    }
};

static int vector2_subtraction = register_experiment("vector2d", "vector2d subtraction",
                                                     experiment_type::TWO_DIMENSIONAL,
                                                     vector2_subtraction_experiment::create);

class vector2_multiplication_experiment : public tiny_experiment
{
    draggable_point& a;
    float b;

public:
    explicit vector2_multiplication_experiment(experiment_context* context) : tiny_experiment(context),
                                                                              a(add_point({5.f, 5.f})),
                                                                              b(2.f)
    {
    }

    void draw() override
    {
        const auto result = a.position * b;
        draw_vector_2d(m_origin_zero, a.position, BLUE);
        draw_text_2d("Va", a.position * .5f, RAYWHITE);
        draw_vector_2d(a.position, result, RED);
        draw_text_2d("Va * s", (result + a.position) * .5f, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_multiplication_experiment(context);
    }
};

static int vector2_multiplication = register_experiment("vector2d", "vector2d multiplication",
                                                        experiment_type::TWO_DIMENSIONAL,
                                                        vector2_multiplication_experiment::create);

class vector2_division_experiment : public tiny_experiment
{
    draggable_point& a;
    float b;

public:
    explicit vector2_division_experiment(experiment_context* context) : tiny_experiment(context),
                                                                        a(add_point({5.f, 5.f})),
                                                                        b(2.f)
    {
    }

    void draw() override
    {
        const auto result = a.position / b;
        draw_vector_2d(m_origin_zero, a.position, BLUE);
        draw_text_2d("Va", (a.position + result) * .5f, RAYWHITE);
        draw_vector_2d(m_origin_zero, result, RED);
        draw_text_2d("Va / s", result * .5f, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_division_experiment(context);
    }
};

static int vector2_division = register_experiment("vector2d", "vector2d division",
                                                  experiment_type::TWO_DIMENSIONAL,
                                                  vector2_division_experiment::create);

class vector2_length_experiment : public tiny_experiment
{
    draggable_point& a;
    draggable_point& b;

public:
    explicit vector2_length_experiment(experiment_context* context) : tiny_experiment(context),
                                                                      a(add_point({1.f, 1.f})),
                                                                      b(add_point({5.f, 5.f}))
    {
    }

    void draw() override
    {
        const auto result = math::length(b.position - a.position);
        draw_vector_2d(a.position, b.position, BLUE);

        const auto offset = math::vector2d(0.f, 1.f);
        draw_line_2d(a.position + offset, b.position + offset, PURPLE);
        draw_line_2d(b.position + (offset * .75f), b.position + (offset * 1.25f), PURPLE);
        draw_line_2d(a.position + (offset * .75f), a.position + (offset * 1.25f), PURPLE);
        draw_text_2d(std::format("{:.2f}", result).c_str(), (a.position + b.position) * .5f + offset * 1.5f, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_length_experiment(context);
    }
};

static int vector2_length = register_experiment("vector2d", "vector2 length",
                                                experiment_type::TWO_DIMENSIONAL,
                                                vector2_length_experiment::create);

class vector2_length2_experiment : public tiny_experiment
{
    draggable_point& a;
    draggable_point& b;

public:
    explicit vector2_length2_experiment(experiment_context* context) : tiny_experiment(context),
                                                                       a(add_point({1.f, 1.f})),
                                                                       b(add_point({5.f, 5.f}))
    {
    }

    void draw() override
    {
        const auto result = math::length_squared(b.position - a.position);
        draw_vector_2d(a.position, b.position, BLUE);

        const auto offset = math::vector2d(0.f, 1.f);

        const auto dir = math::normalize(b.position - a.position);
        draw_line_2d(a.position + offset, (a.position + dir * result) + offset, PURPLE);
        draw_line_2d(a.position + (offset * .75f), a.position + (offset * 1.25f), PURPLE);
        draw_line_2d((a.position + dir * result) + (offset * .75f), (a.position + dir * result) + (offset * 1.25f),
                     PURPLE);
        draw_text_2d(std::format("{:.2f}", result).c_str(), (a.position + b.position) * .5f + offset * 1.5f, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_length2_experiment(context);
    }
};

static int vector2_length2 = register_experiment("vector2d", "vector2 length2",
                                                 experiment_type::TWO_DIMENSIONAL,
                                                 vector2_length2_experiment::create);

class vector2_normalize_experiment : public tiny_experiment
{
    draggable_point& a;

public:
    explicit vector2_normalize_experiment(experiment_context* context) : tiny_experiment(context),
                                                                         a(add_point({1.f, 1.f}))
    {
    }

    void draw() override
    {
        const auto result = math::safe_normalize(a.position);
        draw_vector_2d(m_origin_zero, a.position, BLUE);
        draw_vector_2d(m_origin_zero, result, GREEN);

        draw_cirlce(m_origin_zero, 1.f, ColorAlpha(RED, .75f), false);

        draw_text_2d("v", result * .5f, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_normalize_experiment(context);
    }
};

static int vector2_normalize = register_experiment("vector2d", "vector2 normalize",
                                                   experiment_type::TWO_DIMENSIONAL,
                                                   vector2_normalize_experiment::create);

class vector2_distance_experiment : public tiny_experiment
{
    draggable_point& a;
    draggable_point& b;

public:
    explicit vector2_distance_experiment(experiment_context* context) : tiny_experiment(context),
                                                                        a(add_point({-1.5f, -1.5f})),
                                                                        b(add_point({7.5f, 7.5f}))
    {
    }

    void draw() override
    {
        const auto result = math::distance(a.position, b.position);
        draw_line_2d(a.position, b.position, BLUE);
        const math::vector2d c{a.position.x, b.position.y};
        draw_dotted_2d(a.position, c, YELLOW);
        draw_dotted_2d(b.position, c, YELLOW);
        draw_text_2d(std::format("d:{:.2f}", result).c_str(), (a.position + b.position) * .5f, RAYWHITE);
        draw_text_2d("x2 - x1", (c + a.position) * .5f, RAYWHITE);
        draw_text_2d("y2 - y1", (c + b.position) * .5f, RAYWHITE);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector2_distance_experiment(context);
    }
};

static int vector2_distance = register_experiment("vector2d", "vector2 distance",
                                                  experiment_type::TWO_DIMENSIONAL,
                                                  vector2_distance_experiment::create);
