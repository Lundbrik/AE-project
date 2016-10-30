#! /usr/bin/python
import matplotlib.pyplot as plt
import sys

def read_file(path):
    file_p = open(path, 'r')
    lines = []
    for line in file_p:
        lines.append(line)
    file_p.close()
    return lines

def parse_file(lines):
    title = lines[0]
    x_label = lines[1]
    y_label = lines[2]
    num_curves = int(lines[3])
    curve_labels = []
    curves = []
    for i in range(4, 4 + num_curves):
        curve_labels.append(lines[i])
        curves.append([])
    n = []
    for i in range(4 + num_curves, len(lines)):
        toks = lines[i].split(' ')
        n.append(toks[0])
        for j in range(num_curves):
            curves[j].append(toks[j+1])
    return title, x_label, y_label, num_curves, curve_labels, n, curves

def plot(title, x_label, y_label, num_curves, curve_labels, n, curves,
        save=False,
        path=''):
    fig, ax = plt.subplots()
    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    for i in range(num_curves):
        ax.plot(n, curves[i], label=curve_labels[i])
    ax.legend(loc='best')
    #ax.legend(loc=2)
    #ax.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
    ax.set_xscale('log')
    ax.set_yscale('log')
    ax.get_xaxis().get_major_formatter().labelOnlyBase = False
    if save:
        plt.savefig(path)
    else:
        plt.show()

if len(sys.argv) == 2:
    lines = read_file(sys.argv[1])
    #print ("Read " + str(len(lines)) + " lines")
    t, x, y, nc, cl, n, c = parse_file(lines)
    plot(t, x, y, nc, cl, n, c)
elif len(sys.argv) == 3:
    lines = read_file(sys.argv[1])
    path = sys.argv[2]
    #print ("Read " + str(len(lines)) + " lines")
    t, x, y, nc, cl, n, c = parse_file(lines)
    plot(t, x, y, nc, cl, n, c, True, path)
else:
    print ("Usage: " + sys.argv[0] + " [data file]")
