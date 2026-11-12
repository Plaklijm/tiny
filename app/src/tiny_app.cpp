#define _CRT_SECURE_NO_WARNINGS

#include "tiny_app.h"

#include <raymath.h>
#include <rlgl.h>
#include <raygizmo.h>
#include <utility>

#include "imgui.h"

#include "tiny_experiment.hpp"
#include "helper.hpp"

using namespace tiny;

tiny_app::tiny_app()
{
    const auto& experiments = get_experiments();
    for (const auto& experiment : experiments)
    {
        const auto cat = experiment.category;
        const auto name = experiment.name;
        experiment_map[cat].push_back(name);

        if (std::ranges::find(categories, cat) == categories.end())
        {
            categories.push_back(cat);
        }
    }
}

void tiny_app::draw_ui(experiment_context* context)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Experiments"))
        {
            for (const auto& category : categories)
            {
                if (ImGui::BeginMenu(category.c_str()))
                {
                    for (const auto& name : experiment_map[category])
                    {
                        if (ImGui::MenuItem(name.c_str()))
                        {
                            context->new_experiment_index = get_experiment_index(name);
                            context->should_switch = true;
                        }
                    }
                    ImGui::EndMenu();
                }
            }
            ImGui::EndMenu();
        }

        draw_main_menu_items();
        ImGui::EndMainMenuBar();
    }
}

tiny_app_2d::tiny_app_2d()
{
    m_camera.zoom = 40.f;
    m_camera.target = {0.f, 0.f};
    m_camera.offset = {static_cast<float>(GetScreenWidth()) * .5f, static_cast<float>(GetScreenHeight()) * .5f};
}

void tiny_app_2d::update_camera()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        Vector2 delta = GetMouseDelta();
        m_camera.target.x -= delta.x / m_camera.zoom;
        m_camera.target.y -= delta.y / m_camera.zoom;
    }

    float wheel = GetMouseWheelMove();

    if (wheel != 0.0f)
    {
        Vector2 mouse = GetMousePosition();
        Vector2 before = GetScreenToWorld2D(mouse, m_camera);

        m_camera.zoom = Clamp(
            m_camera.zoom * powf(1.2f, wheel),
            25.f,
            64.0f
        );

        Vector2 after = GetScreenToWorld2D(mouse, m_camera);

        m_camera.target.x += before.x - after.x;
        m_camera.target.y += before.y - after.y;
    }

    // Clamp the camera to world boundaries.
    constexpr float min_world_x = -50.0f;
    constexpr float max_world_x = 50.0f;
    constexpr float min_world_y = -50.0f;
    constexpr float max_world_y = 50.0f;

    const float halfWidth = static_cast<float>(GetScreenWidth()) / (2.0f * m_camera.zoom);
    const float halfHeight = static_cast<float>(GetScreenHeight()) / (2.0f * m_camera.zoom);

    const float min_x = min_world_x + halfWidth;
    const float max_x = max_world_x - halfWidth;
    const float min_y = min_world_y + halfHeight;
    const float max_y = max_world_y - halfHeight;

    // If the visible area is larger than the world, center it.
    m_camera.target.x = min_x <= max_x
                            ? Clamp(m_camera.target.x, min_x, max_x)
                            : (min_world_x + max_world_x) / 2.0f;

    m_camera.target.y = min_y <= max_y
                            ? Clamp(m_camera.target.y, min_y, max_y)
                            : (min_world_y + max_world_y) / 2.0f;
}

void tiny_app_2d::update(experiment_context& context)
{
    context.experiment->step();
}

void tiny_app_2d::draw(experiment_context& context)
{
    BeginMode2D(m_camera);

    draw_grid();

    context.experiment->draw();

    Vector2 mouse_position = to_math(GetScreenToWorld2D(GetMousePosition(), m_camera));

    auto& points = context.experiment->get_points();
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        if (CheckCollisionPointCircle(mouse_position, to_raylib(points[i].position), .25f) &&
            IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !m_dragging)
        {
            m_point_index = i;
            m_dragging = true;
            break;
        }
    }

    if (m_point_index >= 0)
    {
        math::vector2d* position = &points[m_point_index].position;
        Vector2 mouse_delta = GetMouseDelta();
        position->x += mouse_delta.x / m_camera.zoom;
        position->y -= mouse_delta.y / m_camera.zoom;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        m_point_index = -1;
        m_dragging = false;
    }

    for (unsigned int i = 0; i < points.size(); ++i)
    {
        const auto pos = points[i].position;
        const Vector2 draw_pos = to_world(to_raylib(pos));
        if (CheckCollisionPointCircle(mouse_position, to_raylib(pos), .25f))
            DrawCircleV(draw_pos, .25f, ColorAlpha(DARKGRAY, .5f));

        if (std::cmp_equal(i, m_point_index)) DrawCircleV(draw_pos, .25f, DARKGRAY);

        DrawCircleLinesV(draw_pos, .25f, RAYWHITE);

        DrawTextEx(s_font, math::to_string(pos).c_str(), draw_pos, .4f, .1f, RAYWHITE);
    }

    EndMode2D();
}

void tiny_app_2d::draw_ui(experiment_context* context)
{
    tiny_app::draw_ui(context);
    context->experiment->draw_screen(m_camera);
}

void tiny_app_2d::draw_grid()
{
    static int spacing = 1;
    static int extent = 250;

    for (int x = -extent; x <= extent; x += spacing)
    {
        DrawLineEx(Vector2{static_cast<float>(x), static_cast<float>(-extent)},
                   Vector2{static_cast<float>(x), static_cast<float>(extent)}, x % 5 == 0 ? .05f : .01f, GRAY);

        if (x != 0)
        {
            DrawTextEx(s_font, std::format("{}", x).c_str(),
                       {static_cast<float>(x), .1f}, .4f, .1f, RAYWHITE);
        }
    }

    for (int y = -extent; y <= extent; y += spacing)
    {
        float screen_y = -static_cast<float>(y);

        DrawLineEx(Vector2{static_cast<float>(-extent), screen_y},
                   Vector2{static_cast<float>(extent), screen_y}, y % 5 == 0 ? .05f : .01f, GRAY);

        if (y != 0)
        {
            DrawTextEx(s_font, std::format("{}", y).c_str(),
                       {.1f, screen_y}, .4f, .1f, RAYWHITE);
        }
    }

    DrawLineEx({static_cast<float>(-extent), 0.f}, {static_cast<float>(extent), 0.f}, .1f, RED);
    DrawLineEx({0.f, static_cast<float>(-extent)}, {0.f, static_cast<float>(extent)}, .1f, BLUE);
}

tiny_app_3d::tiny_app_3d()
{
    m_camera.position = Vector3{20.f, 20.f, 20.f};
    m_camera.target = Vector3{0.f, 0.f, 0.f};
    m_camera.up = Vector3{0.f, 1.f, 0.f};
    m_camera.fovy = 45.f;
    m_camera.projection = CAMERA_PERSPECTIVE;

    SetGizmoSize(1.f);
    SetGizmoLineWidth(2.f);
}

void tiny_app_3d::update_camera()
{
    if (IsKeyPressed(KEY_C))
    {
        m_is_camera_active = !m_is_camera_active;
        m_is_camera_active ? DisableCursor() : EnableCursor();
    }

    if (!m_is_camera_active) return;

    Vector2 mouse_delta = GetMouseDelta();
    look_rotation.x += mouse_delta.x * sensitivity.x;
    look_rotation.y -= mouse_delta.y * sensitivity.y;
    look_rotation.y = Clamp(look_rotation.y, -PI / 2.0f + 0.01f,PI / 2.0f - 0.01f);

    float left_right = static_cast<float>(IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    float forward_back = static_cast<float>(IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
    float up_down = static_cast<float>(IsKeyDown(KEY_E) - IsKeyDown(KEY_Q));

    float speed = (IsKeyDown(KEY_LEFT_SHIFT) ? 15.f : 7.5f) * GetFrameTime();

    Vector3 forward = {sinf(look_rotation.x), 0.0f, -cosf(look_rotation.x)};
    Vector3 right = {cosf(look_rotation.x), 0.0f, sinf(look_rotation.x)};

    Vector2 movement = {left_right, forward_back};
    movement = Vector2Normalize(movement);

    m_camera.position.x += (right.x * movement.x + forward.x * movement.y) * speed;
    m_camera.position.y += up_down * speed;
    m_camera.position.z += (right.z * movement.x + forward.z * movement.y) * speed;

    m_camera.target = {
        m_camera.position.x + sinf(look_rotation.x) * cosf(look_rotation.y),
        m_camera.position.y + sinf(look_rotation.y),
        m_camera.position.z - cosf(look_rotation.x) * cosf(look_rotation.y)
    };
}

void tiny_app_3d::update(experiment_context& context)
{
    context.experiment->step();
}

void tiny_app_3d::draw(experiment_context& context)
{
    auto& points = context.experiment->get_points_3d();

    BeginMode3D(m_camera);
    context.experiment->draw();

    draw_grid();

    bool gizmo_active = false;
    if (m_point_index >= 0)
    {
        m_transform.translation = to_raylib(points[m_point_index].position);
        gizmo_active = DrawGizmo3D(GIZMO_TRANSLATE, &m_transform);
        rlDisableBackfaceCulling();
        points[m_point_index].position = to_tiny(m_transform.translation);
        DrawSphereEx(to_raylib(points[m_point_index].position), sphere_radius, 8, 8, DARKGRAY);
    }

    const Ray ray = GetScreenToWorldRay(GetMousePosition(), m_camera);
    for (auto& point : points)
    {
        DrawSphereWires(to_raylib(point.position), sphere_radius, 8, 8, ColorAlpha(RAYWHITE, .75f));

        const RayCollision c = GetRayCollisionSphere(ray, to_raylib(point.position), sphere_radius * 1.5f);
        if (c.hit && !gizmo_active)
        {
            DrawSphereEx(to_raylib(point.position), sphere_radius, 8, 8, ColorAlpha(DARKGRAY, .5f));
        }
    }

    EndMode3D();

    if (!gizmo_active && !m_is_camera_active && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        const Ray ray_click = GetScreenToWorldRay(GetMousePosition(), m_camera);
        m_point_index = -1;
        float closest = FLT_MAX;

        for (int i = 0; i < points.size(); i++)
        {
            const RayCollision c =
                GetRayCollisionSphere(ray_click, to_raylib(points[i].position), sphere_radius * 1.5f);
            if (c.hit && c.distance < closest)
            {
                closest = c.distance;
                m_point_index = i;
            }
        }
    }

    draw_grid_labels();
    draw_point_labels(context);
}

void tiny_app_3d::draw_ui(experiment_context* context)
{
    tiny_app::draw_ui(context);
    context->experiment->draw_screen(m_camera);

    if (IsKeyPressed(KEY_I))
        m_show_inspector = !m_show_inspector;
    
    if (m_show_inspector)
        draw_inspector();
}

void tiny_app_3d::draw_grid()
{
    for (int i = -extent; i <= extent; i += spacing)
    {
        const float p = static_cast<float>(i);

        if (i % 5 == 0 && i != 0)
        {
            static float r = .025f;

            // XZ plane
            DrawCylinderEx(Vector3{p, 0, static_cast<float>(-extent)},
                           Vector3{p, 0, static_cast<float>(extent)},
                           r, r, 6, GRAY);
            DrawCylinderEx(Vector3{static_cast<float>(-extent), 0, p},
                           Vector3{static_cast<float>(extent), 0, p},
                           r, r, 6, GRAY);
            if (m_draw_vertical_grid)
            {
                // XY plane
                DrawCylinderEx(Vector3{p, static_cast<float>(-extent), 0},
                               Vector3{p, static_cast<float>(extent), 0},
                               r, r, 6, GRAY);
                DrawCylinderEx(Vector3{static_cast<float>(-extent), p, 0},
                               Vector3{static_cast<float>(extent), p, 0},
                               r, r, 6, GRAY);

                // YZ plane
                DrawCylinderEx(Vector3{0, p, static_cast<float>(-extent)},
                               Vector3{0, p, static_cast<float>(extent)},
                               r, r, 6, GRAY);
                DrawCylinderEx(Vector3{0, static_cast<float>(-extent), p},
                               Vector3{0, static_cast<float>(extent), p},
                               r, r, 6, GRAY);
            }
        }
        else if (i != 0)
        {
            static float alpha = .25f;

            // XZ plane
            DrawLine3D(Vector3{p, 0, static_cast<float>(-extent)},
                       Vector3{p, 0, static_cast<float>(extent)},
                       ColorAlpha(GRAY, alpha));
            DrawLine3D(Vector3{static_cast<float>(-extent), 0, p},
                       Vector3{static_cast<float>(extent), 0, p},
                       ColorAlpha(GRAY, alpha));
            if (m_draw_vertical_grid)
            {
                // XY plane
                DrawLine3D(Vector3{p, static_cast<float>(-extent), 0},
                           Vector3{p, static_cast<float>(extent), 0},
                           ColorAlpha(GRAY, alpha));
                DrawLine3D(Vector3{static_cast<float>(-extent), p, 0},
                           Vector3{static_cast<float>(extent), p, 0},
                           ColorAlpha(GRAY, alpha));

                // YZ plane
                DrawLine3D(Vector3{0, p, static_cast<float>(-extent)},
                           Vector3{0, p, static_cast<float>(extent)},
                           ColorAlpha(GRAY, alpha));
                DrawLine3D(Vector3{0, static_cast<float>(-extent), p},
                           Vector3{0, static_cast<float>(extent), p},
                           ColorAlpha(GRAY, alpha));
            }
        }


        // Coordinate axes
        DrawCylinderEx(Vector3{static_cast<float>(-extent), 0, 0},
                       Vector3{static_cast<float>(extent), 0, 0},
                       .06f, .06f, 6, RED);
        DrawCylinderEx(Vector3{0, static_cast<float>(-extent), 0},
                       Vector3{0, static_cast<float>(extent), 0},
                       .06f, .06f, 6, m_draw_vertical_grid ? ColorAlpha(GREEN, .25f) : GREEN);
        DrawCylinderEx(Vector3{0, 0, static_cast<float>(-extent)},
                       Vector3{0, 0, static_cast<float>(extent)},
                       .06f, .06f, 6, BLUE);
    }
}

void tiny_app_3d::draw_main_menu_items()
{
    if (ImGui::BeginMenu("View"))
    {
        ImGui::MenuItem("Inspector", "I", &m_show_inspector);
        ImGui::EndMenu();
    }
}

void tiny_app_3d::draw_inspector()
{
    const ImGuiViewport* vp = ImGui::GetMainViewport();
    constexpr float width = 200.f;
    ImGui::SetNextWindowPos({vp->WorkPos.x, vp->WorkPos.y});
    ImGui::SetNextWindowSize({width, vp->WorkSize.y});

    constexpr ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

    // Passing &m_show_inspector adds a close (X) button that sets it to false
    if (ImGui::Begin("Inspector", &m_show_inspector, flags))
    {
        ImGui::Checkbox("Draw vertical grid", &m_draw_vertical_grid);
    }
    ImGui::End();
}

void tiny_app_3d::draw_grid_labels() const
{
    static float offset = .1f;

    for (int i = -extent; i <= extent; i += spacing)
    {
        if (i == 0) continue;

        const float p = static_cast<float>(i);
        const std::string label = std::format("{}", i);

        const math::vector3d world_x{p, -offset, 0};
        const math::vector3d world_y{offset, p, 0};
        const math::vector3d world_z{offset, 0, p};

        draw_text_3d(label.c_str(), world_x, m_camera, ColorAlpha(RAYWHITE, .75f));
        draw_text_3d(label.c_str(), world_y, m_camera, ColorAlpha(RAYWHITE, .75f));
        draw_text_3d(label.c_str(), world_z, m_camera, ColorAlpha(RAYWHITE, .75f));
    }
}

void tiny_app_3d::draw_point_labels(experiment_context& context) const
{
    for (const auto point : context.experiment->get_points_3d())
    {
        math::vector3d offset = math::vector3d{sphere_radius, 0.f, 0.f};
        draw_text_3d(math::to_string(point.position).c_str(), point.position + offset, m_camera, RAYWHITE, 1.25f);
    }
}
