from PIL import Image

pixels_out = []
height = 0
width = 0

with open("../2d_gpu/image_tmp.txt", 'r') as file:
    width, height = map(int, file.readline().split())
    pixels_out = [int(line.strip()) for line in file]

image_out = Image.new("RGB", size=(width, height))
image_out.putdata(pixels_out)
image_out.save('test.png')
