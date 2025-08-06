CC = gcc
CFLAGS = -lm -Ofast -Wall -lgsl -lgslcblas 
LFLAGS = -L. -lreg 

TARGET1 = gamma


all: $(TARGET1) 


$(TARGET1): $(TARGET1).c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -f $(TARGET1) 
