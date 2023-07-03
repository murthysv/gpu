#!/bin/bash
arg1="$1"



if [ "$arg" = "clean" ]; then
    echo "cleaning"
    rm 2d_gpu/image_tmp.txt
    rm png_out/test.png
    rm tmp.txt
elif [ "$arg" = "build" ]; then
    echo "building and running"
    arg2="$2"
    python3 svg_parser/parser.py arg2

    # Compile C++ program
    g++ -o 2d_gpu/gpu 2d_gpu/top.cpp

    # Run it
    ./2d_gpu/gpu

    # Call Python script
    python3 png_out/png_out.py

    # Open an image
    xdg-open my_image.jpg  # Replace "my_image.jpg" with the actual image file name
else
    echo "Invalid argument. Please pass 'clean' or 'build'."
fi