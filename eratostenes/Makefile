CC = gcc
CFLAGS = -Wall -lm -Ofast
TARGET = criba


all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)
