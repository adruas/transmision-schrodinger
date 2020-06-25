#Ploteo de la variación de la velocidad radial con el tiempo

#set term pngcairo enhanced
#set output "variandoNlambda09.png"

set multiplot
set origin 0,0
set size 1,1
set xrange [400:4100]
set yrange [0:1]
set ylabel "Valor del coeficiente K"
set xlabel "Valor del parámetro N"
set tics scale 0.5 front
set xtics 500 offset 0,0
set ytics 0.1 offset 0,0
plot "variandoN.txt" w linespoints lw 2 lc "blue" notitle
set origin 0.1,0.3
set size 0.5,0.5
set xrange [400:4100]
set yrange [0.12:0.17]
unset xlabel
unset ylabel
unset label
set tics scale 0.5 front
set xtics 1000 offset 0,0.5
set ytics 0.01 offset 0.5,0
plot "variandoN.txt" w linespoints lw 2 lc "blue" notitle

