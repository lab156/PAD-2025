CC = gcc
CFLAGS = -Wall -lm -O3
TARGET = laplace_serial


#compilacion directa con
#gcc laplace_serial.c -o your_program -lm


all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS) 

clean:
	rm -f $(TARGET)
