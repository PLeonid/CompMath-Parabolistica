#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"

set term jpeg size 1366,768 background "#ffffff"
set output "j.jpg"
set grid x,y,xtics,ytics,mxtics,mytics
#set xtic 20
#set ytic 2
set mxtic 10
set mytic 10
set xlabel "X, Coordinate"
set ylabel "U, functions"
#set yrange [0:28]
set xrange [1:1500]


plot datafile index 1   using 1:2 notitle with lines, \
     datafile index 50 using 1:2 notitle with lines, \
     datafile index 100 using 1:2 notitle with lines, \
     datafile index 200 using 1:2 notitle with lines, \
     datafile index 300 using 1:2 notitle with lines, \
     datafile index 400 using 1:2 notitle with lines, \
     datafile index 500 using 1:2 notitle with lines




EOP
