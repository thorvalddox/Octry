import numpy as np
from PIL import Image

map = [[float(n) for n in l.split("\t") if not n.isspace() and n] for l in open("worldgen.txt").read().split("\n")if  not l.isspace() and l]
height = np.array(map)

print(height)
def rescale(arr,newmin,newmax):
    oldmin = np.amin(np.amin(arr))
    oldmax = np.amin(np.amax(arr))
    factor = (newmax-newmin)/(oldmax-oldmin)
    return factor*(arr-oldmin)+newmin
    
    
height = rescale(height,0,255)
image=np.zeros(tuple(height.shape) + (3,),dtype=np.uint8)
image[:,:,0] = ((height)%15 > 12)*255
image[:,:,1] = height
image[:,:,2] = 255-height

im = Image.fromarray(image)
im.save("heightmap.png")