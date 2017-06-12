#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"

set term jpeg size 1366,768 background "#eeeeee"
set output "data.jpg"
set grid x,y,xtics,ytics,mxtics,mytics
#set xtic 20
#set ytic 2
set mxtic 2
set mytic 2
set xlabel "n, степень"
set ylabel "D, отклонение"
#set yrange [0:28]
set xrange [0:1.2]


plot datafile using 1:2 notitle with lines


EOP
