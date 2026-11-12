#pragma once
#include <raylib.h>

#include <unordered_map>
#include <vector>

#include "tiny_math.hpp"

struct draggable_point_3d;
struct experiment_context;

class tiny_app
{
public:
    tiny_app();
    virtual ~tiny_app() = default;

    virtual void update_camera() = 0;
    virtual void update(experiment_context& context) = 0;
    virtual void draw(experiment_context& context) = 0;
    virtual void draw_ui(experiment_context* context);

protected:
    virtual void draw_main_menu_items() {}
    virtual void draw_grid() = 0;

    std::vector<std::string> categories;
    std::unordered_map<std::string, std::vector<std::string>> experiment_map;
};

class tiny_app_2d : public tiny_app
{
public:
    tiny_app_2d();
    ~tiny_app_2d() override = default;
    void update_camera() override;
    void update(experiment_context& context) override;
    void draw(experiment_context& context) override;
    void draw_ui(experiment_context* context) override;

protected:
    void draw_grid() override;

private:
    Camera2D m_camera{};
    int m_point_index = -1;
    bool m_dragging = false;
};

class tiny_app_3d : public tiny_app
{
public:
    tiny_app_3d();
    ~tiny_app_3d() override = default;
    void update_camera() override;
    void update(experiment_context& context) override;
    void draw(experiment_context& context) override;
    void draw_ui(experiment_context* context) override;

protected:
    void draw_main_menu_items() override;
    void draw_grid() override;

private:
    void draw_inspector();
    void draw_grid_labels() const;
    void draw_point_labels(experiment_context& context) const;

    Transform m_transform{};
    Camera3D m_camera{};
    Vector2 look_rotation{};
    Vector2 sensitivity{.001f, .001f};
    int m_point_index = -1;
    bool m_is_camera_active = false;
    bool m_draw_vertical_grid = false;
    bool m_show_inspector = false;
    const float sphere_radius = .15f;
    const int spacing = 1;
    const int extent = 50;
};
