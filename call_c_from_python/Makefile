CC = gcc
CFLAGS = -fPIC -shared 
TARGET = fun


all: $(TARGET).so

$(TARGET).so: $(TARGET).c
	$(CC) $< -o $@ $(CFLAGS) 

clean:
	rm -f $(TARGET).so
