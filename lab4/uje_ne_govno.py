
import numpy as np
from itertools import permutations


def read_matrix(filename):
    matrix = np.loadtxt(filename, dtype=np.int16)
    return matrix


def sum_path(matrix, path):
    path = list(path)
    n = 0
    cur_vert = path[0]
    for i in path[1:]:
        if matrix[cur_vert][i] == 0:
            return float("inf")
        else:
            n += matrix[cur_vert][i]
            cur_vert = i
    return n


def salesman(matrix):
    min_sum = float("inf")
    min_path = []
    for perm in permutations(range(len(matrix))):
        perm = [*list(perm), perm[0]]
        cur_sum = sum_path(matrix, perm)
        if cur_sum < min_sum:
            min_sum = cur_sum
            min_path = list(perm)
    return [min_sum, min_path]


matrix = read_matrix("test2.txt")
result = salesman(matrix)
print(result)
