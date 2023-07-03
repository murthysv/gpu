from PIL import Image, ImageColor

pixels_out = []
height = 0
width = 0
count = 0


with open("tmp/image_tmp.txt", 'r') as file:
    width, height = map(int, file.readline().split())

    image_out = Image.new("RGB", size=(width, height))

    for y in range(height):
        for x in range(width):
            image_out.putpixel((x,y), ImageColor.getcolor(file.readline().strip(), "RGB"))

    image_out.save('tmp/test.png')
