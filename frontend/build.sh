clang grid.c zoom.m -o simplesheet \
    $(pkg-config --cflags --libs raylib) \
    -framework Cocoa -framework CoreVideo -framework IOKit -framework OpenGL
