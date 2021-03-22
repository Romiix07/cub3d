gcc *.c -D BUFFER_SIZE=30 -L. -lmlx_Linux -lmlx -I. -I../include -L/usr/lib -I../minilibx_linux -lXext -lX11 -lm -lz

echo "-fsanitize=address -fno-omit-frame-pointer"
