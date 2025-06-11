CC = gcc
CFLAGS = -Wall -lm -O3
TARGET1 = linear_regr_grad_desc
TARGET2 = mem_management


#compilacion directa con
# gcc linear_regression_gd.c -o linear_regression_gd -lm

all: $(TARGET1) $(TARGET2)

$(TARGET1): lineal.c 
	$(CC) $(CFLAGS) -o $(TARGET1) lineal.c

$(TARGET2): mem_management.c 
	$(CC) $(CFLAGS) -o $(TARGET2) mem_management.c

clean:
	rm -f $(TARGET)
