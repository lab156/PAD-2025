CC = gcc
CFLAGS = -Wall -lm -Ofast -fopenmp
TARGET = test
DYNLIB = dynlib
#DYNLIB_SO = libdyn.so

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	rm -f $(OBJS) $(TARGET)


#$(TARGET): $(TARGET).o $(DYNLIB_SO)
#	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o $(DYNLIB_SO) -L. -ldyn

#$(DYNLIB_SO): $(DYNLIB).c
#	$(CC) -c $< -fPIC
#	$(CC) $(DYNLIB).o -shared -o libdyn.so $(CFLAGS)

#clean:
	#rm -f $(TARGET) $(DYNLIB_SO)
