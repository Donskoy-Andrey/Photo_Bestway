import numpy as np
from PIL import Image


def main():
    path = "data/images/test.png"
    img = Image.open(path)
    array = np.asarray(img)[:, :, 2]
    with open("data/txt/photo.txt", "w") as txt_file:
        for line in array:
            line = [str(i) for i in line]
            txt_file.write(" ".join(line) + "\n")


if __name__ == "__main__":
    main()