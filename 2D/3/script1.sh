#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

datafile = "file.txt"

set term jpeg size 1366,768 background "#eeeeee"
set output "data1.jpg"
set border 4095 front lt black linewidth 1.000 dashtype solid

set grid x,y,z

set xlabel "Степень ур-я"
set ylabel "Степень гран. условия"
set zlabel "Отклонение от среднего"

#set yrange [0:50]
#set xrange [0:50]
#set zrange [0:180]

set ticslevel 0

set pm3d

set palette rgbformulae 33,13,10

set contour base

set view 45, 45, 1, 1

splot datafile  using 1:2:3 notitle with pm3d

EOP
