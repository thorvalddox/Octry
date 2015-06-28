__author__ = 'Thorvald'

import numpy as np
import time
from itertools import product

from libc.stdlib cimport rand,RAND_MAX,srand
from PIL import Image

cdef gauss(double variance=1.0):
    return variance/RAND_MAX*(rand()-rand())


class HeightMap:
    def __init__(self,int size,int height,int noise):
        self.height = np.zeros([2**size+1,2**size+1],dtype=np.double)
        self.size = size
        self.blocksize = 2**size
        self.defaultheight = height
        self.noise = noise*self.defaultheight/self.blocksize
    def calculate_square(self, int size,int xpos, int ypos):
        if size < 1:
            return
        cdef int realsize = 2**size
        corners = [self.height[xpos,ypos],self.height[xpos+realsize,ypos],
                   self.height[xpos,ypos+realsize],self.height[xpos+realsize,ypos+realsize]]
        mean = sum(corners)/4
        self.height[xpos+realsize//2,ypos+realsize//2] = mean + gauss(realsize*self.noise)
    def calculate_tilted(self,int size,int xpos,int ypos):
        if size < 1:
            return
        cdef int realsize = 2**size
        corners = [self.height[xpos+realsize/2,ypos],self.height[xpos+realsize/2,ypos+realsize],
                   self.height[xpos,ypos+realsize/2],self.height[xpos+realsize,ypos+realsize/2]]
        mean = sum(corners)/4
        self.height[xpos+realsize//2,ypos+realsize//2] = mean + gauss(realsize*self.noise)
    def scan_squares(self,int size):
        print("building level ",size)
        for (x,y) in product(range(0,2**self.size,2**size),repeat=2):
            self.calculate_square(size,x,y)
    def scan_tilted(self,int size):
        cdef int realsize = 2**size
        print("building level ",size,"tilted")
        for (x,y) in product(range(0,2**self.size,2**size)[:-1],range(0,2**self.size,2**size)): #-1 compensates for border
            self.calculate_tilted(size,x+realsize//2,y)
            self.calculate_tilted(size,y,x+realsize//2)
    def calculate(self):
        np.set_printoptions(2)
        self.height[self.blocksize//2,self.blocksize//2] = self.defaultheight
        for s in reversed(range(self.size)):
            self.scan_squares(s)
            self.scan_tilted(s)
    def rescale(self,newmin,newmax):
        oldmin = np.amin(self.height)
        oldmax = np.amax(self.height)
        factor = (newmax-newmin)/(oldmax-oldmin)
        self.height = factor*(self.height-oldmin)+newmin


def main():
    srand(time.time())
    h = HeightMap(10,200,10)
    h.calculate()
    print(h.height)
    h.rescale(0,255)
    image=np.zeros(tuple(h.height.shape) + (3,),dtype=np.uint8)
    image[:,:,0] = ((h.height)%15 > 12)*255
    image[:,:,1] = h.height
    image[:,:,2] = 255-h.height

    im = Image.fromarray(image)
    im.save("heightmap.png")