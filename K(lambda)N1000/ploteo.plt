#set term pngcairo enhanced

a=1000/5
k=(6.283185307*70)/1000 #6.28.. es 2*pi


f(x) = x<1 ? (1+((x*x/(4*(1-x)))*sin(2*a*k*sqrt(1-x))**2))**(-1)  : x>1 ? (1+((x*x/(4*(1+x)))*sinh(2*a*k*sqrt(1+x))**2))**(-1)  : 1/0

#set output "LambdaN1000.png"

set multiplot

set origin 0,0
set size 1,1
set xrange [0:5.1]
set yrange [0:1]
set ylabel "Coeficiente de transmisión T({/Symbol l})"
set xlabel "Valor del parámetro {/Symbol l}"
set tics scale 0.5 front
set xtics 0.5 offset 0,0
set ytics 0.1 offset 0,0
plot 'variandoLambda.txt' u 1:2:3:4 w xyerror pt 3 lw 1.2 lc "red" notitle, f(x) lw 2 lc "blue" notitle
set origin 0.4,0.2
set size 0.5,0.7
set xrange [0.4:1]
set yrange [-0.1:0.9]
unset xlabel
unset ylabel
unset label
set tics scale 0.5 front
set xtics 0.1 offset 0,0.5
set ytics 0.2 offset 0.5,0
plot 'variandoLambda.txt' u 1:2:3:4 w xyerror pt 3 lw 1.2 lc "red" notitle, f(x) lw 2 lc "blue" notitle



#unset output
