#include <raylib.h>
#include <stdio.h>

#define DrawGrid ERROR("DrawGrid is raylib's weird thing. Use SdrawGrid instead.")
#define ERROR(x) 😔

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 450;

void SdrawGrid(
    int left, int top,
    unsigned int x_shift, unsigned int y_shift,
    unsigned int n_displayed_rows, unsigned int n_displayed_cols,
    unsigned int n_total_rows, unsigned int n_total_cols,
    unsigned int grid_width, unsigned int grid_height
) {
    const int row_height = grid_height / n_displayed_rows;
    const int col_width = grid_width / n_displayed_cols;
    // Horizontal lines
    for (int row = 0; row <= n_displayed_rows; row++) {
        int y = top - y_shift%row_height + row*grid_height/n_displayed_rows;
        DrawLine(left, y, left+grid_width, y, BLACK);
    }
    // Vertical lines
    for (int col = 0; col <= n_displayed_cols; col++) {
        int x = left - x_shift%col_width + col*grid_width/n_displayed_cols;
        DrawLine(x, top, x, top+grid_height, BLACK);
    }
    // Cell numbers
    for (int row = 0; row <= n_displayed_rows; row++) {
        for (int col = 0; col <= n_displayed_cols; col++) {
            char cell_n_str[sizeof(int)*8 * 2 + 1];
            int actual_col = x_shift/col_width + col;
            int actual_row = y_shift/row_height + row;
            sprintf(cell_n_str, "%d,%d", actual_col, actual_row);
            DrawText(cell_n_str,
                left - x_shift%col_width + col*grid_width/n_displayed_cols + 3,
                top - y_shift%row_height + row*grid_height/n_displayed_rows + 3,
                20,
                BLACK);
        }
    }
}

int Simax(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int x_shift = 0, y_shift = 0, n_displayed_rows = 5, n_displayed_cols = 5;
    const double SCALE_FACTOR = 1.2;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "hi");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        const int x_shift_speed = (WINDOW_WIDTH / 200) + 1;
        const int y_shift_speed = (WINDOW_HEIGHT / 200) + 1;
        if (IsKeyDown(KEY_RIGHT)) {
            x_shift += x_shift_speed;
        } else if (IsKeyDown(KEY_LEFT)) {
            x_shift = Simax(0, x_shift-x_shift_speed);
        }
        if (IsKeyDown(KEY_UP)) {
            y_shift = Simax(0, y_shift-y_shift_speed);
        } else if (IsKeyDown(KEY_DOWN)) {
            y_shift += y_shift_speed;
        }
        if (IsKeyDown(KEY_MINUS)) {
            n_displayed_rows = Simax(1, (int)(n_displayed_rows*SCALE_FACTOR) + 1);
            n_displayed_cols = Simax(1, (int)(n_displayed_cols*SCALE_FACTOR) + 1);
        } else if (IsKeyDown(KEY_EQUAL)) {
            n_displayed_rows = Simax(1, (int)(n_displayed_rows/SCALE_FACTOR) - 1);
            n_displayed_cols = Simax(1, (int)(n_displayed_cols/SCALE_FACTOR) - 1);
        }
        if (IsKeyDown(KEY_R)) {
            x_shift = 0;
            y_shift = 0;
            n_displayed_rows = 5;
            n_displayed_cols = 5;
        }
        Vector2 scroll = GetMouseWheelMoveV();
        x_shift = Simax(0, x_shift-2*scroll.x);
        y_shift = Simax(0, y_shift-2*scroll.y);
        // printf("%lf %lf\n", m.x, m.y);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            const int grid_top = WINDOW_WIDTH/5;
            const int grid_left = WINDOW_WIDTH/5;
            SdrawGrid(grid_left, grid_top,
                x_shift, y_shift,
                n_displayed_rows, n_displayed_cols,
                10, 10,
                WINDOW_WIDTH*4/5, WINDOW_HEIGHT*4/5);
            DrawLine(grid_left, grid_top, grid_left, WINDOW_HEIGHT, RED);
            DrawLine(grid_left, grid_top, WINDOW_WIDTH, grid_top, RED);

        EndDrawing();
    }
    CloseWindow();
}
