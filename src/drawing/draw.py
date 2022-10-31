import sys
import matplotlib.pyplot as plt


def draw(xs: list, ys: list):
    plt.figure(figsize=(8, 8))
    plt.title("Best way", fontsize=20)
    plt.plot(xs, ys, c='r')
    plt.scatter(xs, ys, c='black')
    plt.xticks(xs, [abs(i) for i in xs])
    plt.yticks(ys, [abs(i) for i in ys])
    plt.grid(True)
    plt.savefig(f'../data/images/ouput.png')


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