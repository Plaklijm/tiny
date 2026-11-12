#include "tiny_experiment.hpp"
#include <raymath.h>
#include <rlgl.h>

#include "helper.hpp"
#include "tiny_app.h"

#include "imgui.h"
#include "rlImGui.h"

using namespace tiny;

static experiment_context s_context{};

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(s_context.screen_width, s_context.screen_height, s_context.title.c_str());
    rlDisableBackfaceCulling();
    rlImGuiSetup(true);
    ChangeDirectory(GetApplicationDirectory());
    InitFont();
    
    select_experiment(&s_context, s_context.experiment_index);
    
    tiny_app_2d app_2d;
    tiny_app_3d app_3d;

    while (!WindowShouldClose())
    {
        if (s_context.should_switch)
        {
            select_experiment(&s_context, s_context.new_experiment_index);
            s_context.should_switch = false;
        }

        tiny_app* app = s_context.type == experiment_type::TWO_DIMENSIONAL
                            ? static_cast<tiny_app*>(&app_2d)
                            : static_cast<tiny_app*>(&app_3d);
        app->update_camera();

        app->update(s_context);

        BeginDrawing();
        ClearBackground(BLACK);

        app->draw(s_context);

        rlImGuiBegin();
        app->draw_ui(&s_context);
        rlImGuiEnd();
        
        EndDrawing();
    }
    
    UnloadFont();
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
