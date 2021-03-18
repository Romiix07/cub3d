gcc *.c -D BUFFER_SIZE=30 -I. -I../include -L../minilibx -lmlx_Linux -lmlx -L/usr/lib -I../mlx_linux -lXext -lX11 -lm -lz

echo "-fsanitize=address -fno-omit-frame-pointer"
