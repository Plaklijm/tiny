#pragma once

#include <string>
#include <vector>
#include <deque>
#include <variant>

#include <raylib.h>
#include <raymath.h>

#include "tiny_math.hpp"

enum class experiment_type : int8_t
{
    TWO_DIMENSIONAL,
    THREE_DIMENSIONAL
};

struct draggable_point
{
    tiny::math::vector2d position;
};

struct draggable_point_3d
{
    tiny::math::vector3d position;
};

struct experiment_context
{
    class tiny_experiment* experiment = nullptr;

    experiment_type type;

    int screen_width = 1280;
    int screen_height = 720;
    std::string title{};

    bool restart = false;
    int experiment_index = 0;

    bool should_switch = false;
    int new_experiment_index = 0;
};

class tiny_experiment
{
public:
    explicit tiny_experiment(experiment_context* context);
    virtual ~tiny_experiment() = default;

    virtual void step()
    {
    }

    virtual void draw()
    {
    }

    virtual void draw_screen(std::variant<Camera2D, Camera3D> camera)
    {
    }

    std::deque<draggable_point>& get_points() { return m_points; }
    std::deque<draggable_point_3d>& get_points_3d() { return m_points_3d; }

protected:
    experiment_context* m_context;
    std::deque<draggable_point> m_points {};
    std::deque<draggable_point_3d> m_points_3d {};

    draggable_point& add_point(tiny::math::vector2d position)
    {
        m_points.push_back({position});
        return m_points.back();
    }
    
    draggable_point_3d& add_point_3d(tiny::math::vector3d position)
    {
        m_points_3d.push_back({position});
        return m_points_3d.back();
    }

    tiny::math::vector2d m_origin_zero{0.f, 0.f};
    tiny::math::vector3d m_origin_zero_3d{0.f, 0.f, 0.f};
};

typedef tiny_experiment* experiment_create_function(experiment_context* context);

struct experiment_entry
{
    std::string category;
    std::string name;
    experiment_type type;
    experiment_create_function* create_function;
};

std::vector<experiment_entry>& get_experiments();

int register_experiment(const std::string& category, const std::string& name, const experiment_type type,
                        experiment_create_function* function);

void select_experiment(experiment_context* context, int selection);

int get_experiment_index(const std::string& name);
