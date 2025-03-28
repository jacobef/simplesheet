#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cahr char

// Struct for array: size info, pointer itself, capacity?
//
// Make arr store in ints, not str?

struct str {
    char *data;
    int len;
};


struct sheet {
    int rows;
    int columns;
    int length;
    char *data;
};

void print_sheet(struct sheet sheet) {
    // ???
}

void add_rows_and_cols(struct sheet sheet, int n_rows, int n_cols) {
    // mallocs n more rows to arr
    // Fill with empty strings
    cahr *buffer = malloc(sheet.length + ((n_rows * sheet.columns) + (n_cols * sheet.rows) * sizeof(char)));
    buffer = sheet.data + (((n_rows * sheet.columns) + (n_cols * sheet.rows) * "0"); // not like python
    sheet.data = buffer;
    free(buffer);
}

void edit_cell(struct sheet *sheet, int col, int row, struct str new_value) {
    // ???
}

char *get_at(int col, int row, char *arr, int n_cols) {
    return &arr[((row) * n_cols) + col];
}
// aaaabbbbcccc
// The array itself as a global variable;
// Function to add n rows
// Function to add n columns



int main() {
    int n_rows = 10;
    int n_columns = 10;
    char *arr = malloc((n_rows * n_columns)*sizeof(char));
    // To avoid -Wconversion
    // To avoid intger division and other weird math
    memset(arr, 'x', 100);
    arr[21] = 'a';
    printf("%c <-- the funny one I tried to cast | > %c < <--- the other one", arr[21], *get_at(1,2, arr, n_columns));
}
