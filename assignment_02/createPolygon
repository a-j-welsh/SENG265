#!/bin/bash

python generate_polygon.py 0 100 3 > triangles0.txt
python rotate_scale_translate.py -f 0.9 -n 25 triangles0.txt > triangles1.txt
python rotate_scale_translate.py -x -125 -y 125 triangles1.txt > triangles2.txt


python generate_polygon.py 0 100 4 > squares0.txt
python rotate_scale_translate.py -f 0.9 -n 25 squares0.txt > squares1.txt
python rotate_scale_translate.py -x 125 -y 125 squares1.txt > squares2.txt

python generate_polygon.py 0 100 5 > pentagons0.txt
python rotate_scale_translate.py -f 0.9 -n 25 pentagons0.txt > pentagons1.txt
python rotate_scale_translate.py -x 125 -y -125 pentagons1.txt > pentagons2.txt

python generate_polygon.py 0 100 6 > hexagons0.txt
python rotate_scale_translate.py -f 0.9 -n 25 hexagons0.txt > hexagons1.txt
python rotate_scale_translate.py -x -125 -y -125 hexagons1.txt > hexagons2.txt

python lines_to_svg_new.py triangles2.txt squares2.txt pentagons2.txt hexagons2.txt > polygons.svg
Open -a Safari polygons.svg