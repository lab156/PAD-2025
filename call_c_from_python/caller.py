from ctypes import CDLL
import sys


def main(x):
    # Specify the path to your shared library
    # For Linux/macOS:
    so_file = "./fun.so"
    # For Windows:
    # so_file = "./my_functions.dll"

    # Load the shared library
    c_functions = CDLL(so_file)

    # Call the C function
    result = c_functions.square(x)
    print(result)  # Output: 100


if __name__ == "__main__":
    x = sys.argv[1]
    main(int(x))
