__author__ = 'Thorvald'

import random

from libc.stdlib cimport rand,RAND_MAX

cdef gauss(double variance=1.0):
    return variance/RAND_MAX*(rand()-rand())

def main():
    for i in range(10):
        print(gauss())