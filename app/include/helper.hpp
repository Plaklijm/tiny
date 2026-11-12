#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include "tiny_math.hpp"

inline Font s_font{0};

inline void InitFont()
{
    s_font = LoadFontEx("resources/dejavu-sans.book.ttf", 32, NULL, 0);
}

inline void UnloadFont() { UnloadFont(s_font); }

inline Vector2 to_raylib(const tiny::math::vector2d& v) { return Vector2{v.x, v.y}; }
inline Vector3 to_raylib(const tiny::math::vector3d& v) { return Vector3{v.x, v.y, v.z}; }
inline tiny::math::vector2d to_tiny(const Vector2& v) { return {v.x, v.y}; }
inline tiny::math::vector3d to_tiny(const Vector3& v) { return {v.x, v.y, v.z}; }
inline Vector2 to_world(Vector2 p) { return {p.x, -p.y}; }
inline Vector2 to_math(Vector2 p) { return {p.x, -p.y}; }

inline bool is_in_front(const tiny::math::vector3d& point, const Camera3D& camera)
{
    const tiny::math::vector3d forward = to_tiny(Vector3Normalize(camera.target - camera.position));
    const tiny::math::vector3d to_point = point - to_tiny(camera.position);
    return tiny::math::dot(forward, to_point) > 0;
}

inline void draw_line_2d(const tiny::math::vector2d& from, const tiny::math::vector2d& to, Color color)
{
    DrawLineV(to_world(to_raylib(from)), to_world(to_raylib(to)), color);
}

inline void draw_dotted_2d(const tiny::math::vector2d& from, const tiny::math::vector2d& to, Color color)
{
    tiny::math::vector2d delta = {to - from};
    float length = tiny::math::length(delta);

    if (length <= 0.0001f) return;

    tiny::math::vector2d dir = delta / length;

    static float dash_length = .1f, gap_length = .1f;
    float pattern_length = dash_length + gap_length;

    for (float d = 0.f; d < length; d += pattern_length)
    {
        float segment_end = fminf(d + dash_length, length);

        Vector2 p1 = {from.x + dir.x * d, from.y + dir.y * d};
        Vector2 p2 = {from.x + dir.x * segment_end, from.y + dir.y * segment_end};
        DrawLineV(to_world(p1), to_world(p2), color);
    }
}

inline void draw_vector_2d(const tiny::math::vector2d& from, const tiny::math::vector2d& to, Color color)
{
    static float size = .5f;

    DrawLineV(to_world(to_raylib(from)), to_world(to_raylib(to)), color);

    tiny::math::vector2d dir = tiny::math::vector2d(to - from);
    float len = tiny::math::length(dir);

    if (len <= 0.0001f) return;

    dir = dir * (1.0f / len);
    tiny::math::vector2d perp = size * tiny::math::normalize(tiny::math::perp(dir));
    const auto left = to - dir * size + perp * size;
    const auto right = to - dir * size - perp * size;

    DrawLineV(to_world(to_raylib(left)), to_world(to_raylib(to)), color);
    DrawLineV(to_world(to_raylib(right)), to_world(to_raylib(to)), color);
}

inline void draw_cirlce(const tiny::math::vector2d& v, float r, Color color, bool fill = true)
{
    if (fill)
        DrawCircleV(to_raylib(v), r, color);
    else
        DrawCircleLinesV(to_raylib(v), r, color);
}

inline void draw_text_2d(const char* text, const tiny::math::vector2d& pos, Color color)
{
    DrawTextEx(s_font, text, to_world(to_raylib(pos)), .4f, .1f, color);
}

constexpr float RADIUS_3D = .05f;
constexpr int SIDES_3D = 6;

inline void draw_line_3d(const tiny::math::vector3d& from, const tiny::math::vector3d& to, Color color)
{
    DrawCylinderEx(to_raylib(from), to_raylib(to), RADIUS_3D, RADIUS_3D, SIDES_3D, color);
}

inline void draw_dotted_3d(const tiny::math::vector3d& from, const tiny::math::vector3d& to, Color color)
{
    tiny::math::vector3d delta = {to - from};
    float length = tiny::math::length(delta);

    if (length <= 0.0001f) return;

    tiny::math::vector3d dir = delta / length;

    static float dash_length = .25f, gap_length = .25f;
    float pattern_length = dash_length + gap_length;

    for (float d = 0.f; d < length; d += pattern_length)
    {
        float segment_end = fminf(d + dash_length, length);

        Vector3 p1 = {from.x + dir.x * d, from.y + dir.y * d, from.z + dir.z * d};
        Vector3 p2 = {from.x + dir.x * segment_end, from.y + dir.y * segment_end, from.z + dir.z * segment_end};
        DrawCylinderEx(p1, p2, RADIUS_3D, RADIUS_3D, SIDES_3D, color);
    }
}

inline void draw_vector_3d(const tiny::math::vector3d& from, const tiny::math::vector3d& to, Color color)
{
    static float size = .5f;

    DrawCylinderEx(to_raylib(from), to_raylib(to), RADIUS_3D, RADIUS_3D, SIDES_3D, color);

    tiny::math::vector3d dir = tiny::math::vector3d(to - from);
    float len = tiny::math::length(dir);

    if (len <= 0.0001f) return;

    dir = dir * (1.0f / len);

    tiny::math::vector3d axis = std::abs(dir.x) < std::abs(dir.y)
                                    ? tiny::math::vector3d{1.0f, 0.0f, 0.0f}
                                    : tiny::math::vector3d{0.0f, 1.0f, 0.0f};

    tiny::math::vector3d perp = size * tiny::math::normalize(tiny::math::cross(dir, axis));
    const auto left = to - dir * size + perp * size;
    const auto right = to - dir * size - perp * size;

    DrawCylinderEx(to_raylib(left), to_raylib(to), RADIUS_3D * .25f, RADIUS_3D, SIDES_3D, color);
    DrawCylinderEx(to_raylib(right), to_raylib(to), RADIUS_3D * .25f, RADIUS_3D, SIDES_3D, color);
}

inline void draw_text_3d(const char* text, const tiny::math::vector3d& pos, const Camera& camera, Color color,
                         float scale = 1.f)
{
    if (is_in_front(pos, camera))
    {
        Vector2 pos2d = GetWorldToScreen(to_raylib(pos), camera);
        DrawTextEx(s_font, text, pos2d, 16.f * scale, 1.f * scale, color);
    }
}
