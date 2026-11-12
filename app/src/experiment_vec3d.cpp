#include "helper.hpp"
#include "tiny_experiment.hpp"

using namespace tiny;

class vector3_addition_experiment : public tiny_experiment
{
    draggable_point_3d& a;
    draggable_point_3d& b;

    math::vector3d sum{};

public:
    explicit vector3_addition_experiment(experiment_context* context) : tiny_experiment(context),
                                                                        a(add_point_3d({6.f, 5.f, 8.f})),
                                                                        b(add_point_3d({5.f, 1.f, -8.f}))
    {
    }

    void step() override
    {
    }

    void draw() override
    {
        sum = a.position + b.position;

        draw_vector_3d(m_origin_zero_3d, a.position, GREEN);
        draw_vector_3d(m_origin_zero_3d, b.position, BLUE);

        draw_dotted_3d(a.position, sum, YELLOW);
        draw_dotted_3d(b.position, sum, YELLOW);

        draw_vector_3d(m_origin_zero_3d, sum, RED);
    }

    void draw_screen(std::variant<Camera2D, Camera3D> camera) override
    {
        const auto camera_3d = std::get<Camera3D>(camera);
        draw_text_3d("Va", a.position * .5f, camera_3d, RAYWHITE, 1.25f);
        draw_text_3d("Vb", b.position * 0.5f, camera_3d, RAYWHITE, 1.25f);

        draw_text_3d("Va + Vb", sum * .5f, camera_3d, RAYWHITE, 1.25f);
        draw_text_3d(to_string(sum).c_str(), sum, camera_3d, RAYWHITE, 1.25f);
    }

    static tiny_experiment* create(experiment_context* context)
    {
        return new vector3_addition_experiment(context);
    }
};

static int vector3d_addition = register_experiment("vector3d", "vector3d addition",
                                                   experiment_type::THREE_DIMENSIONAL,
                                                   vector3_addition_experiment::create);
