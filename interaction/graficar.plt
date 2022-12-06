#Para la norma
set term qt
plot "norma.txt" u 1:2 w lines lw 1.5 lc "orange"
set term pngcairo enhanced
unset key
set output "graf_norma.png"
replot
unset output

#Para la densidad de probabilidad
set term gif animate delay 2
set output "densidad_de_probabilidad.gif"
stats "probabilidad.txt" u 1:2
set xr [STATS_min_x:STATS_max_x]
set yr [STATS_min_y:STATS_max_y]
N = 1000
lambda=0.3
n=100
k=2.0*3.141592*n/N
a = lambda*k*k
V(x) = (x < 2*N/5 || x > 3*N/5) ? 0 : a
unset key
do for [i=0:STATS_blocks-2] {
	plot "probabilidad.txt" index i u 1:2 w lines lc "red" lw 1.5, V(x) lc "blue" lw 2
}
