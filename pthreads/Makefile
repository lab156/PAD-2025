CC = gcc
CFLAGS = -lm -Ofast -Wall -lpthread
LFLAGS = -L. -lreg 

TARGET1 = ex
TARGET2 = basic


all: $(TARGET1) $(TARGET2)


$(TARGET1): pthread_example.c
	$(CC) pthread_example.c -o $(TARGET1) $(CFLAGS) 

$(TARGET2): basic_threads.c
	$(CC) basic_threads.c -o $(TARGET2) $(CFLAGS)

clean:
	rm -f $(TARGET1) $(TARGET2) 
