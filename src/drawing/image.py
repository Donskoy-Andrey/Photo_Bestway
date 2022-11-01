import numpy as np
from PIL import Image
import sys


def main():
    input_path = sys.argv[1]
    img = Image.open(input_path)
    array = np.asarray(img)[:, :, 2]
    with open("../data/txt/input.txt", "w") as txt_file:
        for line in array:
            line = [str(i) for i in line]
            txt_file.write(" ".join(line) + "\n")


if __name__ == "__main__":
    main()