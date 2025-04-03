if ! pkg-config --exists raylib; then
    echo "Raylib not found. Install it with 'brew install raylib'."
    exit 1
fi

clang grid.c zoom.m -o simplesheet \
    $(pkg-config --cflags --libs raylib) \
    -framework Cocoa -framework CoreVideo -framework IOKit -framework OpenGL
