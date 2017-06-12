#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file2.txt"

set term jpeg size 1366,768 background "#eeeeee"
set output "data2.jpg"

set grid x,y,mxtics,mytics

set mxtic 2
set mytic 2

set xlabel "Степень в уравнении"
set ylabel "Степень гран.условия"

set yrange [0:2]
set xrange [0:5.5]

#plot datafile using 1:2 notitle smooth csplines  with lines lt 1 lw 1
#with points

plot datafile using 1:2 notitle with points pt 1 ps 2, \
     datafile using 1:2 notitle smooth csplines  with lines lt 2 lw 1


EOP
