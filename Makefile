build:
	gcc -fPIC -shared -o stellar_types.so \
	stellar_types/*.c -I/usr/include/lua5.3 \
	-llua5.3 -std=c89 -DLUA_C89_NUMBERS
