import sys
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

def draw(xs: list, ys: list, file_input: str, file_output: str):
    img = Image.fromarray(np.asarray(Image.open(file_input))[:, :, 2]) 
    plt.figure(figsize=(8, 8))
    plt.title("Best way", fontsize=20)
    plt.imshow(img)
    plt.plot(xs[::-1], [abs(i) for i in ys[::-1]], c='r')
    plt.grid(True)
    plt.savefig(file_output)


def main():
    file_input = sys.argv[1]
    file_output = sys.argv[2]
    path = "./../data/txt/output.txt"
    xs, ys = [], [] 
    with open(path, 'r') as file:
        for i in file.readlines():
            x, y = i.split()
            xs.append(int(x))
            ys.append(int(y) * (-1))
    draw(xs, ys, file_input, file_output)

if __name__ == "__main__":
    main()