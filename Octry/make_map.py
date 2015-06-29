map = [[float(n) for n in l.split("\t") for l in open("worldgen.txt").split("\n")
h = np.array(map)

h.rescale(0,255)
image=np.zeros(tuple(h.height.shape) + (3,),dtype=np.uint8)
image[:,:,0] = ((h.height)%15 > 12)*255
image[:,:,1] = h.height
image[:,:,2] = 255-h.height

im = Image.fromarray(image)
im.save("heightmap.png")