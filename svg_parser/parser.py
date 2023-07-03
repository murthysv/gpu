import xml.etree.ElementTree as ET
import sys
from pathlib import Path


def parse_svg(svg_string):
    root = ET.fromstring(svg_string)
    paths = root.findall(".//{http://www.w3.org/2000/svg}path")
    
    result = []
    for path in paths:
        d = path.get("d")
        fill = path.get("fill")
        
        vertices = []
        for command in d.split():
            if command.isnumeric():
                vertices.append(int(command))
        
        result.append(" ".join(map(str, vertices)) + " " + fill[1:])
    
    return result


def parse_svg_file(file_path):
    with open(file_path, 'r') as f:
        svg_string = f.read()
    
    return parse_svg(svg_string)

def write_to_file(file_path, content):
    with open(file_path, 'w') as file:
        file.write(' '.join(content))
        file.write('\n')


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Please provide a single file_name as a command-line argument.")
        sys.exit(1)

    file_name = sys.argv[1]
    file_path = "../svgs/" + file_name + ".svg"

    print("SVG Path: ", file_path)

    parsed_data = parse_svg_file(file_path)
    for item in parsed_data:
      print(item)
    write_to_file("../tmp.txt", parsed_data)

