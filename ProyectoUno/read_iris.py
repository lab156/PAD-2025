import pandas as pd
import numpy as np
from sklearn.datasets import load_iris


def get_iris_data():
    iris = load_iris()
    # target is the dependent variable
    y = iris.target
    # data has 4 columns
    x = [row[0] for row in iris.data]
    return x, y


def main():
    x, y = get_iris_data()
    print("Resumen de los datos leidos:")
    print(f"x tiene {len(x)=} elementos.")
    print(f"y tiene {len(y)=} elementos.")
    print("")
    print("Los primeros 3 elementos de x son:")
    print(f"{x[:3]}")
    print("")
    print("Los primeros 3 elementos de y son:")
    print(f"{y[:3]}")


if __name__ == "__main__":
    main()
