import numpy as np
import pandas as pd
import sys


def main(filename):
    with open('data/file-06.csv', 'r') as fobj:
        DF = pd.read_csv(fobj)
    # Perform linear regression of degree 1
    X_arr = DF.iloc[:, 0]
    y_arr = DF.iloc[:, 1]
    coeffs = np.polyfit(X_arr, y_arr, 1)

    print(f"Coefficients are m={coeffs[0]} and b={coeffs[1]}")


if __name__ == "__main__":
    print(sys.argv[1])
    main(sys.argv[1])
