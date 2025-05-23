#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "zoom.h"

void InitWindowWithZoom(int width, int height, const char *title) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE|FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, title);
    SetupTrackpadZoom();
}

static const int DEFAULT_WINDOW_WIDTH = 800;
static const int DEFAULT_WINDOW_HEIGHT = 450;
static const float DEFAULT_CELL_HEIGHT = 40.0;
static const float DEFAULT_CELL_WIDTH = 120.0;


Vector2 Vec2(float x, float y) {
    return (Vector2) { x, y };
}

float nonNegF(float f) {
    return fmaxf(f, 0.0f);
}

Vector2 nonNegV2(Vector2 v) {
    return Vec2(nonNegF(v.x), nonNegF(v.y));
}


void drawSheetGrid(
    Vector2 grid_top_left,
    Vector2 shift,
    float scale,
    float grid_width, float grid_height
) {
    float cell_height = scale * DEFAULT_CELL_HEIGHT, cell_width = scale * DEFAULT_CELL_WIDTH;

    float x_shift_pix = scale * shift.x, y_shift_pix = scale * shift.y;

    BeginScissorMode(grid_top_left.x, grid_top_left.y, grid_width, grid_height);

    for (int row = 0; row <= grid_height / (int)cell_height + 1; row++) {
        float y = grid_top_left.y - fmodf(y_shift_pix, cell_height) + row * cell_height;
        DrawLineV(Vec2(grid_top_left.x, y), Vec2(grid_top_left.x + grid_width, y), BLACK);

        for (int col = 0; col <= grid_width / (int)cell_width + 1; col++) {
            float x = grid_top_left.x - fmodf(x_shift_pix, cell_width) + col * cell_width;
            if (row == 0) {
                DrawLineV(Vec2(x, grid_top_left.y), Vec2(x, grid_top_left.y + grid_height), BLACK);
            }

            int actual_col = (int)(x_shift_pix / cell_width) + col;
            int actual_row = (int)(y_shift_pix / cell_height) + row;
            Vector2 text_pos = { x + cell_width/20.0, y + cell_height/20.0 };

            DrawTextEx(
                GetFontDefault(),
                TextFormat("%d,%d", actual_col, actual_row),
                text_pos,
                scale * DEFAULT_CELL_HEIGHT/2.0f,
                scale * DEFAULT_CELL_HEIGHT/20.0f,
                BLACK
            );
        }
    }

    EndScissorMode();
}

int main(void) {
    InitWindowWithZoom(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "simplesheet");
    SetTargetFPS(60);

    Vector2 shift = {0.0f, 0.0f};
    Vector2 grid_top_left = {DEFAULT_WINDOW_WIDTH / 5.0f, DEFAULT_WINDOW_HEIGHT / 5.0f};
    float grid_width = DEFAULT_WINDOW_WIDTH * 4.0f / 5.0f, grid_height = DEFAULT_WINDOW_HEIGHT * 4.0f / 5.0f;
    float scale = 1.0f;

    const float SCALE_FACTOR = 1.2f;

    Vector2 mouse_pos_in_grid = Vector2Subtract(GetMousePosition(), grid_top_left);
    Vector2 zoom_center_in_world = {
        shift.x + mouse_pos_in_grid.x / scale,
        shift.y + mouse_pos_in_grid.y / scale
    };
    int monitor = GetCurrentMonitor();
    int monitor_width = GetMonitorWidth(monitor), monitor_height = GetMonitorHeight(monitor);
    int monitor_max_dimension = monitor_width > monitor_height ? monitor_width : monitor_height;

    while (!WindowShouldClose()) {
        int window_width = GetScreenWidth();
        int window_height = GetScreenHeight();

        const float shift_speed = (0.5f * monitor_max_dimension / 60.0f) / scale; // 2 screen widths or heights per second

        if (IsKeyDown(KEY_RIGHT)) {
            shift.x += shift_speed;
        } else if (IsKeyDown(KEY_LEFT)) {
            shift.x = nonNegF(shift.x - shift_speed);
        }
        if (IsKeyDown(KEY_UP)) {
            shift.y = nonNegF(shift.y - shift_speed);
        } else if (IsKeyDown(KEY_DOWN)) {
            shift.y += shift_speed;
        }

        Vector2 mouse_pos_in_grid = Vector2Subtract(GetMousePosition(), grid_top_left);
        // TODO Make GetMousePosition recognize the mouse position immediately after the window is opened
        if (
            mouse_pos_in_grid.x >= 0.0f
            && mouse_pos_in_grid.x <= grid_width
            && mouse_pos_in_grid.y >= 0.0f
            && mouse_pos_in_grid.y <= grid_height
        ) {
            if (IsKeyPressed(KEY_EQUAL)) {
                scale *= SCALE_FACTOR;
            } else if (IsKeyPressed(KEY_MINUS)) {
                scale /= SCALE_FACTOR;
            } else {
                float old_scale = scale;
                ZoomInfo zoom_info = PollZoom();
                if (zoom_info.zooming) {
                    scale *= (1.0f + (float)zoom_info.zoom_delta);
                } else {
                    zoom_center_in_world = Vec2(
                        shift.x + mouse_pos_in_grid.x / scale,
                        shift.y + mouse_pos_in_grid.y / scale
                    );
                }
                float shift_factor = (1.0f / old_scale) - (1.0f / scale);
                shift = nonNegV2(Vec2(
                    zoom_center_in_world.x - (mouse_pos_in_grid.x / scale),
                    zoom_center_in_world.y - (mouse_pos_in_grid.y / scale)
                ));
                Vector2 scroll = GetMouseWheelMoveV();
                shift = nonNegV2(Vec2(
                    shift.x - shift_speed * scroll.x,
                    shift.y - shift_speed * scroll.y
                ));
            }
        } else {
            PollZoom(); // drain zoom delta when mouse is outside grid
        }

        if (IsKeyDown(KEY_SPACE)) {
            shift = Vec2(0.0f, 0.0f);
            grid_top_left = Vec2(window_width / 5.0f, window_height / 5.0f);
            grid_width = window_width * 4.0f / 5.0f;
            grid_height = window_height * 4.0f / 5.0f;
            scale = 1.0f;
        }

        if (IsKeyDown(KEY_D)) grid_top_left.x += shift_speed;
        else if (IsKeyDown(KEY_A)) grid_top_left.x -= shift_speed;
        if (IsKeyDown(KEY_W)) grid_top_left.y -= shift_speed;
        else if (IsKeyDown(KEY_S)) grid_top_left.y += shift_speed;

        if (IsKeyDown(KEY_E)) {
            grid_width = fmax(grid_width - shift_speed, monitor_width / 20.0f);
        } else if (IsKeyDown(KEY_R)) {
            grid_width += shift_speed;
        }
        if (IsKeyDown(KEY_T)) {
            grid_height = fmax(grid_height - shift_speed, monitor_width / 20.0f);
        } else if (IsKeyDown(KEY_G)) {
            grid_height += shift_speed;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawSheetGrid(
                grid_top_left,
                shift,
                scale,
                grid_width, grid_height
            );
            Vector2 grid_bottom_left = {grid_top_left.x, grid_top_left.y + grid_height};
            Vector2 grid_top_right = {grid_top_left.x + grid_width, grid_top_left.y};
            Vector2 grid_bottom_right = {grid_top_left.x + grid_width, grid_top_left.y + grid_height};
            DrawLineEx(grid_top_left, grid_bottom_left, 2.0, shift.x == 0.0f ? BLUE : GREEN);
            DrawLineEx(grid_top_left, grid_top_right, 2.0, shift.y == 0.0f ? BLUE : GREEN);
            DrawLineEx(grid_top_right, grid_bottom_right, 2.0, GREEN);
            DrawLineEx(grid_bottom_left, grid_bottom_right, 2.0, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
