from ctypes import CDLL
import sys


def main(x):
    # Specify the path to your shared library
    # For Linux/macOS:
    # shared object
    so_file = "./fun.so"
    # For Windows:
    # so_file = "./fun.dll"

    # Load the shared library
    c_functions = CDLL(so_file)

    # Call the C function
    result = c_functions.square(x)
    print(result)


if __name__ == "__main__":
    x = sys.argv[1]
    # x es un String no un int
    main(x)
