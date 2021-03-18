gcc *.c -I../include -I. -lm -L. -lmlx -D BUFFER_SIZE=30 -framework OpenGL -framework AppKit

echo "-fsanitize=address -fno-omit-frame-pointer"