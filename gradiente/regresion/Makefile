CC = gcc
CFLAGS = -lm -O3 -Wall 
LFLAGS = -L. -lreg 

TARGET1 = linear_regr_grad_desc
TARGET2 = mem_management
TARGET3 = libreg.a
TARGET4 = generate_write
TARGET5 = lineal_args
TARGET6 = viz

LIBFILES = reg_utils.h reg_utils.c


#compilacion directa con
# gcc linear_regression_gd.c -o linear_regression_gd -lm
#$(CC) $(CFLAGS) -o $(TARGET2) mem_management.c

all: $(TARGET3) $(TARGET1) $(TARGET2)  $(TARGET4) $(TARGET5) $(TARGET6)

$(TARGET3): $(LIBFILES)
	$(CC) -c reg_utils.c -o reg_utils.o
	ar -rcs $(TARGET3) reg_utils.o

$(TARGET1): lineal.c 
	$(CC) lineal.c $(LFLAGS) -o $(TARGET1) $(CFLAGS) 

$(TARGET2): mem_management.c 
	$(CC) $(TARGET2).c $(LFLAGS) -o $(TARGET2) $(CFLAGS)

$(TARGET4): $(TARGET4).c
	$(CC) $(TARGET4).c $(LFLAGS) -o $(TARGET4) $(CFLAGS)

$(TARGET5): $(TARGET5).c
	$(CC) $(TARGET5).c $(LFLAGS) -o $(TARGET5) $(CFLAGS)

$(TARGET6): $(TARGET6).c
	$(CC) $(TARGET6).c $(LFLAGS) -o $(TARGET6) $(CFLAGS)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)  reg_utils.o
