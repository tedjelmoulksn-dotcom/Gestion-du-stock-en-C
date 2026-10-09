CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2
CPPFLAGS += -Iinclude

.PHONY: all test sanitize clean
all: build/inventory_demo

build/inventory_demo: src/main.c src/stock.c include/gestion_de_stock.h
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) src/main.c src/stock.c -o $@

build/test_stock: tests/test_stock.c src/stock.c include/gestion_de_stock.h
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) tests/test_stock.c src/stock.c -Wl,--wrap=malloc,--wrap=free -o $@

test: build/test_stock
	./build/test_stock

sanitize:
	$(MAKE) clean
	$(MAKE) test CFLAGS="-std=c11 -Wall -Wextra -Wpedantic -Werror -g -fsanitize=address,undefined -fno-omit-frame-pointer"

clean:
	rm -rf build
