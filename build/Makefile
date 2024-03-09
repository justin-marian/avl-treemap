CFLAGS += -c -g -Wall -Wextra -Wpedantic \
                  -Wformat=2 -Wno-unused-parameter \
                  -Wshadow -Wwrite-strings -Wstrict-prototypes \
                  -Wold-style-definition -Wredundant-decls \
                  -Wnested-externs -Wmissing-include-dirs \
                  -Wjump-misses-init -Wlogical-op -O2

SRC_DIR += ../src
LIB_DIR += $(SRC_DIR)/lib
UTILS_DIR += $(SRC_DIR)/utils

FILES += $(SRC_DIR)/AVLRun.c $(LIB_DIR)/AVLTree.c \
		 $(LIB_DIR)/Cipher.c $(LIB_DIR)/Range.c \
		 $(UTILS_DIR)/Utils.c  $(LIB_DIR)/Func.c

.PHONY: all build clean clean_all

all: build
	@gcc *.o -o AVLRun

build: $(FILES)
	@gcc $(CFLAGS) $(FILES)

clean:
	@rm -rf AVLRun.o AVLRun

clean_all:
	@rm -rf *.o AVLRun outputs