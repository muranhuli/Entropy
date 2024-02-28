import matplotlib.pyplot as plt

# Read in the data from the two txt files
def draw(filename):
    with open(f'./results/{filename}_distribution1.txt', 'r') as f1, open(f'./results/{filename}_distribution2.txt', 'r') as f2:
        data1 = [float(line) for line in f1]
        data2 = [float(line) for line in f2]

    # Create a figure and axis object for plotting
    fig, ax = plt.subplots()

    # Plot the data from the first file as a line plot on the axis object

    import numpy as np

    x1 = range(len(data1))
    y1 = data1
    ax.plot(x1, y1, label='File 1')

    # Plot the data from the second file as a line plot on the same axis object
    x2 = range(len(data2))
    y2 = data2
    ax.plot(x2, y2, label='File 2')

    # Set the x and y axes to use log scale
    ax.set_xscale('log')
    ax.set_yscale('log')

    # Add a title and axis labels to the plot
    ax.set_title('Line Plot of Data from Two Files')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')

    # Show the plot
    plt.legend()
    plt.show()
    plt.savefig(f'./results/{filename}_distribution.png')

if __name__ == '__main__':
    l = ['core', 'cardinality', 'degree', 'intersection', 'pairdeg']
    for info in l:
        draw(info)