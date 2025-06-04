CC = gcc
CFLAGS = -Wall -lm -O3
TARGET = linear_regr_grad_desc


#compilacion directa con
# gcc linear_regression_gd.c -o linear_regression_gd -lm

all: $(TARGET)

$(TARGET): lineal.c
	$(CC) $(CFLAGS) -o $(TARGET) lineal.c

clean:
	rm -f $(TARGET)
