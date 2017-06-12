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

f(x) = m*x + b
fit f(x) datafile using 1:4 via m,b


plot datafile using 1:4 notitle  with points pt 1 ps 2, \
   f(x) title "1 / ((0.98419 +/- 0.01963) * x + (0.248544 +/- 0.05923))  " lt 2


EOP
