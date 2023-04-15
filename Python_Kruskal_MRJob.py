# import boto3
# from botocore.config import Config

# client = boto3.client('kinesis', config=)



import sys
# from tkinter.tix import Y_REGION
from mrjob.job import MRJob, MRStep
import math
import time

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
    def configure_args(self):
        super(Kruskal, self).configure_args()
        self.add_passthru_arg("-m", "--min_weight", help="The year will be taken from user.")
        self.add_passthru_arg("-a", "--max_weight", help="The year will be taken from user.")

    # def __init__(self, min_weight = 0, max_weight = 0):
    #     self.min_weight = min_weight
    #     self.max_weight = max_weight

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

    # Reading the values from line and 
    # calling reducer by dividing the weight by 10
    def mapper1(self, _, line):
        src, dest, weight = line.split(" ")
        number_of_map_reduce = 4
        div = math.ceil((abs(int(self.options.max_weight) - int(self.options.min_weight)) + number_of_map_reduce) / number_of_map_reduce)
        yield int(int(weight) / div), (int(src), int(dest), int(weight))
    
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
    time1 = time.time()
    Kruskal().run()
    time2 = time.time()
    print(time2 - time1)


# swapnilsaha69@gmail.com

#Date - 11/01/2022
# 1. 
# 2. 
# 3. 



#Date - 09/27/2022
# 1. Need to talk with Arun, (Urgent).
# 2. Need to think about distributed parallel algorithm for Dijkstra.
# 3. Need to check my code in lab PC.
# 4. Need to add a paragraph in the overleaf for the normal Dijkstra, and a paragraph for parallel one.
# 5. Need to find out a way how can I use multiple CPU, I may need to install a Hadoop environment.




#Date - 09/20/2022
# 1. Need to go through the Dijskatra algorithm for parallel one. - Done
# 2. We are trying to find out the methodologies for different types of graph algorithm.
# 3. Can we apply Krsukal's methodology (distribute and merge) to other graph algorithm? - Thinking
# 4. Read a paper in every week and add it to related work. - Done
# 5. Need to implement MRJob in AWS. - Trying
# 6. Talk with ECS support manager. - Done




# Date - 09/06/2022
# 1. Urgent-- Need to generate a huge graph to test it, at least around 100Mb. I may need to make it more big.
# 2. Need to go through filter-kruskal, and need to compare it (Need to add it in paper - related work).
# 3. Need to add kruskal algorithm in paper - relate work.
# 4. Need to explore some other graph algorithm.
# 5. Need to talk with Arun about AWS.



# Need to write an email about funding.
# I may need to add some parameter in MRJob to make it able to use multiple CPU.



# Date - 09/01/2022
# 1. Talk to Arun about AWS
# 2. Need to thing about some other graph algorithm.
# 3. Need to go through some papers for related work.
# 4. Run the experiment in the lab machine.


# Date: 23-Aug-2022
# Task
# Need to take the time difference when it starts, and when it ends for the distributed one and normal one.
# Run python MRJob in AWS
# Is there any python library which have implemented the MST algorithm?


# Python_Kruskal_MRJob.py input_set_2.txt --min_weight 1 --max_weight 100

