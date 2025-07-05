CC = gcc
CFLAGS = -Wall -fPIC
AR = ar rcs
TARGET_STATIC = main_static
TARGET_SHARED = main_shared
LIB_STATIC = libstrutils.a
LIB_SHARED = libstrutils.so
OBJS = bstrutils.o

all: static shared

static: $(LIB_STATIC) $(TARGET_STATIC)

$(LIB_STATIC): $(OBJS)
	$(AR) $@ $^

$(TARGET_STATIC): main.c $(LIB_STATIC)
	$(CC) main.c -L. -lstrutils -o $@

shared: $(LIB_SHARED) $(TARGET_SHARED)

$(LIB_SHARED): $(OBJS)
	$(CC) -shared -o $@ $^

$(TARGET_SHARED): main.c $(LIB_SHARED)
	$(CC) main.c -L. -lstrutils -o $@

bstrutils.o: bstrutils.c strutils.h
	$(CC) $(CFLAGS) -c bstrutils.c

clean:
	rm -f *.o *.a *.so main_static main_shared

