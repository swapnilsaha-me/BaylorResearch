import sys
import time

par = {}

def find_par(a):
    stack = list()
    while (par[a] != a):
        stack.append(par[a])
        a = par[a]
    while (len(stack) != 0):
        par[stack.pop()] = a
    return a
    

class edge:
    def __init__(self, src, dest, weight):
        self.src = src
        self.dest = dest
        self.weight = weight

def Kruskal(filename):
    arr = []
    # Reading input from 
    with open(filename, 'r') as file:
        for line in file.readlines():
            src, dest, w = [int(x) for x in line.split(' ')]
            arr.append(edge(src=src, dest=dest, weight=w))
    arr.sort(key = lambda x: x.weight, reverse=False)
    for val in arr:
        par[val.src] = val.src
        par[val.dest] = val.dest
    cost = 0
    edges = []
    for val in arr:
        a = find_par(val.src)
        b = find_par(val.dest)
        if a != b:
            par[a] = b
            cost = cost + val.weight
            edges.append(val)
    print()
    print("Cost is = ", cost)
    print("Total Edges = ", len(edges))
    print()

if __name__ == '__main__':
    # Checking the filename from command line input
    if(len(sys.argv) > 1):
        filename = sys.argv[1]
        time1 = time.time()
        Kruskal(filename)
        time2 = time.time()
        print(time2 - time1)
