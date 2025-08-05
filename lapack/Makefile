CC = gcc
CFLAGS = -Wall -O3 -llapacke -llapack -lblas
TARGET = solve
TARGET2 = regres_w_lapack

all: $(TARGET) $(TARGET2)

# para compilar:
# gcc solve.c -o solve -Wall -O3 -llapacke -llapack -lblas 

$(TARGET): $(TARGET).c
	$(CC) $< -o $@ $(CFLAGS) 

$(TARGET2): $(TARGET2).c
	$(CC) $< -o $@ $(CFLAGS) 

clean:
	rm -f $(TARGET) $(TARGET2)
