#include <raylib.h>
#include <stdio.h>

#define DrawGrid ERROR("DrawGrid is raylib's weird thing. Use drawGrid instead.")
#define ERROR(x) 😔

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 450;

void drawGrid(
    int left, int top,
    unsigned int x_shift, unsigned int y_shift,
    unsigned int cell_width, unsigned int cell_height,
    unsigned int grid_width, unsigned int grid_height
) {
    BeginScissorMode(left, top, grid_width, grid_height);

    for (int row = 0; row <= grid_height/cell_height + 1; row++) {
        int y = top - y_shift%cell_height + row*cell_height;
        DrawLine(left, y, left+grid_width, y, BLACK);

        for (int col = 0; col <= grid_width/cell_width + 1; col++) {
            int x = left - x_shift%cell_width + col*cell_width;
            if (row == 0) DrawLine(x, top, x, top+grid_height, BLACK);

            int actual_col = x_shift/cell_width + col;
            int actual_row = y_shift/cell_height + row;
            DrawText(
                TextFormat("%d,%d", actual_col, actual_row),
                x+3, y+3,
                20, BLACK
            );
        }
    }

    EndScissorMode();
}

int imax(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int x_shift = 0, y_shift = 0;
    double cell_width = 50, cell_height = 50;
    int grid_left = WINDOW_WIDTH/5, grid_top = WINDOW_HEIGHT/5;
    int grid_width = WINDOW_WIDTH*4/5, grid_height = WINDOW_HEIGHT*4/5;
    const double SCALE_FACTOR = 1.2;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "hi");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        const int x_shift_speed = (WINDOW_WIDTH / 200) + 1;
        const int y_shift_speed = (WINDOW_WIDTH / 200) + 1;
        if (IsKeyDown(KEY_RIGHT)) {
            x_shift += x_shift_speed;
        } else if (IsKeyDown(KEY_LEFT)) {
            x_shift = imax(x_shift - x_shift_speed, 0);
        }
        if (IsKeyDown(KEY_UP)) {
            y_shift = imax(y_shift - y_shift_speed, 0);
        } else if (IsKeyDown(KEY_DOWN)) {
            y_shift += y_shift_speed;
        }
        // Zoom
        if (IsKeyPressed(KEY_EQUAL)) {
            cell_width *= SCALE_FACTOR;
            cell_height *= SCALE_FACTOR;
        } else if (IsKeyPressed(KEY_MINUS)) {
            cell_width /= SCALE_FACTOR;
            cell_height /= SCALE_FACTOR;
        }
        // Reset
        if (IsKeyDown(KEY_SPACE)) {
            x_shift = 0, y_shift = 0, cell_width = 50, cell_height = 50;
            grid_left = WINDOW_WIDTH/5, grid_top = WINDOW_HEIGHT/5;
            grid_width = WINDOW_WIDTH*4/5, grid_height = WINDOW_HEIGHT*4/5;
        }
        // Move grid location
        if (IsKeyDown(KEY_D)) {
            grid_left += x_shift_speed;
        } else if (IsKeyDown(KEY_A)) {
            grid_left -= x_shift_speed;
        }
        if (IsKeyDown(KEY_W)) {
            grid_top -= y_shift_speed;
        } else if (IsKeyDown(KEY_S)) {
            grid_top += y_shift_speed;
        }
        // Change grid size
        if (IsKeyDown(KEY_E)) {
            grid_width = imax(grid_width/SCALE_FACTOR, WINDOW_WIDTH/10);
        } else if (IsKeyDown(KEY_R)) {
            grid_width = grid_width*SCALE_FACTOR + 1;
        }
        if (IsKeyDown(KEY_T)) {
            grid_height = imax(grid_height/SCALE_FACTOR, WINDOW_WIDTH/10);
        } else if (IsKeyDown(KEY_G)) {
            grid_height = grid_height*SCALE_FACTOR + 1;
        }
        Vector2 scroll = GetMouseWheelMoveV();
        x_shift = imax(x_shift - 2*scroll.x, 0);
        y_shift = imax(y_shift - 2*scroll.y, 0);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawGrid(grid_left, grid_top,
                x_shift, y_shift,
                cell_width, cell_height,
                grid_width, grid_height);
            DrawLine(grid_left, grid_top, grid_left, grid_top+grid_height, RED);
            DrawLine(grid_left, grid_top, grid_left+grid_width, grid_top, RED);
            DrawLine(grid_left+grid_width, grid_top, grid_left+grid_width, grid_top+grid_height, RED);
            DrawLine(grid_left, grid_top+grid_height, grid_left+grid_width, grid_top+grid_height, RED);
        EndDrawing();
    }
    CloseWindow();
}
