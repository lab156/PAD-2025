CC = gcc
CFLAGS = -Wall -lm -O3
TARGET = laplace_serial


#compilacion directa con
#gcc laplace_serial.c -o your_program -lm


all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)
