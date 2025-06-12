CC = gcc
CFLAGS = -lm -O3 -Wall 
LFLAGS = -L. -lreg 
TARGET1 = linear_regr_grad_desc
TARGET2 = mem_management
TARGET3 = libreg.a
LIBFILES = reg_utils.h reg_utils.h


#compilacion directa con
# gcc linear_regression_gd.c -o linear_regression_gd -lm
#$(CC) $(CFLAGS) -o $(TARGET2) mem_management.c

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET3): $(LIBFILES)
	$(CC) -c reg_utils.c -o reg_utils.o
	ar -rcs $(TARGET3) reg_utils.o

$(TARGET1): lineal.c $(LIBFILES)
	$(CC) lineal.c $(LFLAGS) -o $(TARGET1) $(CFLAGS) 

$(TARGET2): mem_management.c $(LIBFILES)
	$(CC) $(TARGET2).c $(LFLAGS) -o $(TARGET2) $(CFLAGS)

clean:
	rm -f $(TARGET) reg_utils.o
