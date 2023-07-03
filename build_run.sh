#!/bin/bash
arg1="$1"



if [ "$arg1" = "clean" ]; then
    echo "cleaning"
    rm tmp/image_tmp.txt
    rm tmp/gpu
    rm tmp/test.png
    rm tmp/tmp.txt
elif [ "$arg1" = "build" ]; then
    echo "building and running"
    arg2="$2"
    python3 svg_parser/parser.py "$arg2"

    # Compile C++ program
    g++ -o tmp/gpu 2d_gpu/top.cpp

    # Run it
    ./tmp/gpu

    # Call Python script
    python3 png_out/png_out.py

    # Open an image
    xdg-open tmp/test.png  # Replace "my_image.jpg" with the actual image file name
else
    echo "Invalid argument. Please pass 'clean' or 'build'."
fi