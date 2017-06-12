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

plot 1/x, \
 datafile using 1:2 notitle with points


EOP
