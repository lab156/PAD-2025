import numpy as np
import pandas as pd
import sys


def main(filename):
    with open('data/file-06.csv', 'r') as fobj:
        # Funcion de Pandas para abrir archivos .CSV
        # Esta funcion entrega un DataFrame
        DF = pd.read_csv(fobj)
    # Perform linear regression of degree 1
    X_arr = DF.iloc[:, 0]  # Leer todas las filas de la 1ra columna
    y_arr = DF.iloc[:, 1]
    coeffs = np.polyfit(X_arr, y_arr, 1)
    # TODO como encontrar el MSE??

    print(f"Coefficients are m={coeffs[0] + 1} and b={coeffs[1]}")


if __name__ == "__main__":
    # print(sys.argv[1])
    # La funcion se tiene que llamar con un argumento
    # este argumento es el nombre de un archivo .CSV
    main(sys.argv[1])
