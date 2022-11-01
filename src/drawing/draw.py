import sys
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

def draw(xs: list, ys: list):

    img = plt.imread("./../data/images/test.png")
    img = Image.fromarray(np.asarray(Image.open("./../data/images/test.png"))[:, :, 2])
    
    plt.figure(figsize=(8, 8))
    plt.title("Best way", fontsize=20)
    plt.imshow(img)
    plt.plot(xs[::-1], [abs(i) for i in ys[::-1]], c='r')
    plt.grid(True)
    plt.savefig(f'../data/images/output.png')


def main():
    path = "./../data/txt/output.txt"
    xs, ys = [], [] 
    with open(path, 'r') as file:
        for i in file.readlines():
            x, y = i.split()
            xs.append(int(x))
            ys.append(int(y) * (-1))
    draw(xs, ys)

if __name__ == "__main__":
    main()