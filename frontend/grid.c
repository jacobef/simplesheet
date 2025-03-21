#include <raylib.h>

#define DrawGrid ERROR("DrawGrid is raylib's weird thing. Use SdrawGrid instead.")
#define ERROR(x) 😔

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 450;

void SdrawGrid(int n_rows, int n_cols, int left, int top, int width, int height) {
    for (int i = 0; i <= n_rows; i++) {
        int x = left + i*width/n_rows;
        DrawLine(x, top, x, top+height, BLACK);
    }
    for (int i = 0; i <= n_cols; i++) {
        int y = top + i*height/n_cols;
        DrawLine(left, y, left+width, y, BLACK);
    }
}

int Simax(int a, int b) {
    return a > b ? a : b;
}

int x_shift = 0;
int y_shift = 0;
int n_rows = 5;
int n_cols = 5;
const double SCALE_FACTOR = 1.2;

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "hi");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        const int x_shift_speed = (WINDOW_WIDTH / 20) + 1;
        const int y_shift_speed = (WINDOW_HEIGHT / 20) + 1;
        if (IsKeyDown(KEY_RIGHT)) {
            x_shift += x_shift_speed;
        } else if (IsKeyDown(KEY_LEFT)) {
            x_shift -= x_shift_speed;
        } else if (IsKeyDown(KEY_UP)) {
            y_shift -= y_shift_speed;
        } else if (IsKeyDown(KEY_DOWN)) {
            y_shift += y_shift_speed;
        }
        if (IsKeyDown(KEY_MINUS)) {
            n_rows = Simax(1, (int)(n_rows*SCALE_FACTOR) + 1);
            n_cols = Simax(1, (int)(n_cols*SCALE_FACTOR) + 1);
        } else if (IsKeyDown(KEY_EQUAL)) {
            n_rows = Simax(1, (int)(n_rows/SCALE_FACTOR) - 1);
            n_cols = Simax(1, (int)(n_cols/SCALE_FACTOR) - 1);
        }
        if (IsKeyDown(KEY_R)) {
            x_shift = 0;
            y_shift = 0;
            n_rows = 5;
            n_cols = 5;
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            SdrawGrid(n_rows, n_cols, x_shift, y_shift, WINDOW_WIDTH, WINDOW_HEIGHT);
        EndDrawing();
    }
    CloseWindow();
}
