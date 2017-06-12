#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file2.txt"

set term jpeg size 1366,768 background "#eeeeee"
set output "data3.jpg"

set grid x,y,mxtics,mytics

set mxtic 2
set mytic 2

set xlabel "Степень в уравнении"
set ylabel "Степень гран.условия"

set yrange [0:6]
set xrange [0:6]

plot x, \
 datafile using 1:4 notitle with points


EOP
