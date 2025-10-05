build:
	gcc -fPIC -shared -o examples/stellar_types.so \
	stellar_types/*.c -I/usr/include/lua5.3 \
	-llua5.3 -std=c89 -DLUA_C89_NUMBERS -DSTELLAR_TYPES_LUA

build_py:
	gcc -fPIC -shared -o examples/stellar_types_python.so \
	stellar_types/*.c -I/usr/include/lua5.3 \
	-std=c89 -DLUA_C89_NUMBERS -DSTELLAR_TYPES_PYTHON