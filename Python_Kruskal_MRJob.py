import sys
from tkinter.tix import Y_REGION
from mrjob.job import MRJob, MRStep

class edge:
    def __init__(self, src, dest, weight):
        self.src = src
        self.dest = dest
        self.weight = weight

#%%
"""
The original MRJob class
"""
class Kruskal(MRJob):

    """
    This method is for taking year input from command line.
    """
    # def configure_args(self):
    #     super(Baseball, self).configure_args()
    #     self.add_passthru_arg("-m", "--year", help="The year will be taken from user.")

    def steps(self):
        return [
            MRStep(mapper = self.mapper1,
                    reducer = self.reducer1),
            MRStep(mapper = self.mapper2,
                    reducer = self.reducer2),
            MRStep(mapper = self.mapper2,
                    reducer = self.reducer2),
            MRStep(mapper = self.mapper2,
                    reducer = self.reducer2),
            # MRStep(mapper = self.mapper2,
            #         reducer = self.reducer2),
            # MRStep(mapper = self.mapper2,
            #         reducer = self.reducer2),
            MRStep(mapper = self.mapper2,
                    reducer = self.reducer3)
        ]
    
    # Task
    # Get a free account for student from AWS,
    # Need to write a python code for Kruskal algorithm.
    # Need to check how many cores in Lab machine.
    # Need to update my code and try to use command line parameter.

    # Reading the values from line and 
    # calling reducer by dividing the weight by 10
    def mapper1(self, _, line):
        src, dest, weight = line.split(" ")
        yield int(int(weight) / 26), (int(src), int(dest), int(weight))
    
    # Sorting the values based on weight
    def reducer1(self, key, values):
        yield key, sorted(values, key = lambda x: x[2])

        # 1000 edges -> 1 - 100 (weight) -> 100

    # Taking the least weighted values
    def mapper2(self, key, values):
        parent_dict = {}
        newValues = []
        for val in values:
            parent_dict[val[0]] = val[0]
            parent_dict[val[1]] = val[1]
            newValues.append(val)

        for val in newValues:
            a = val[0]
            b = val[1]

            stack = list()
            while (parent_dict[a] != a):
                stack.append(parent_dict[a])
                a = parent_dict[a]
            while (len(stack) != 0):
                parent_dict[stack.pop()] = a
            
            while (parent_dict[b] != b):
                stack.append(parent_dict[b])
                b = parent_dict[b]
            while (len(stack) != 0):
                parent_dict[stack.pop()] = b

            if (a != b):
                parent_dict[a] = b
                yield key, val
    
    def reducer2(self, key, values):
        yield int(int(key) / 2), sorted(values, key = lambda x: x[2])

    def reducer3(self, key, values):
        cost = 0
        total_edge = 0
        for val in values:
            cost = cost + val[2]
            total_edge = total_edge + 1
            # yield "", "{} : {}".format(key, val)
        yield "", "Cost = {}, Number of Edges = {}".format(cost, total_edge)
    
if __name__ == '__main__':
    Kruskal().run()
