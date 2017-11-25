import matplotlib.pyplot as plt

# Функция для отображения
def func(x):
    return [i ** 2 for i in x]


if __name__ == '__main__':
    x = []
    y = []
    with open('data_graphic.txt', encoding='utf-8') as file:
        for line in file:
            x1, y1 = line.split()
            x.append([int(x1)])
            y.append([float(y1)])


    plt.xlabel("Count thread")
    plt.ylabel("Time")
    plt.plot(x, y, 'r')

    # Сетка на фоне для улучшения восприятия

    plt.grid(color="grey", which="major", axis='x', linestyle='-', linewidth=0.5)
    plt.grid(color="grey", which="minor", axis='x', linestyle=':', linewidth=0.25)
    plt.grid(color="grey", which="major", axis='y', linestyle='-', linewidth=0.5)

    plt.show()