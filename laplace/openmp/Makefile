CC = gcc
CFLAGS = -Wall -lm -O3
TARGET = laplace_omp
TARGET2 = laplace_parallel_region


# Direct compilation
# gcc -c laplace_omp.c -o lap.o -fopenmp
# gcc lap.o -o laplace -fopenmp -lpthread -lm

all: $(TARGET) $(TARGET2)

$(TARGET): $(TARGET).c
	$(CC) -c $(TARGET).c -o $(TARGET).o -fopenmp
	$(CC) $(TARGET).o -o $(TARGET) $(CFLAGS) -fopenmp

$(TARGET2): $(TARGET2).c
	$(CC) -c $< -o $(TARGET2).o -fopenmp
	$(CC) $(TARGET2).o -o $@ $(CFLAGS) -fopenmp

clean:
	rm -f $(TARGET) $(TARGET).o $(TARGET2) $(TARGET2).o
