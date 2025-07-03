CC = gcc
CFLAGS = -lm -Ofast -Wall -lpthread
LFLAGS = -L. -lreg 

TARGET1 = ex
TARGET2 = basic
TARGET3 = mute
TARGET4 = sum


all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) 


$(TARGET1): pthread_example.c
	$(CC) $< -o $@ $(CFLAGS)

$(TARGET2): basic_threads.c
	$(CC) $< -o $@ $(CFLAGS)

$(TARGET3): mutex_example.c 
	$(CC) $< -o $@ $(CFLAGS)

$(TARGET4): sum_threads.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)
