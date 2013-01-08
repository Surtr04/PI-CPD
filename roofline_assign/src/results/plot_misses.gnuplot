reset
set term postscript eps color blacktext
set output "misses.eps"

set nokey
set style fill solid
set ylabel "number of misses"
set grid
plot "plot_misses.txt" using 2: xtic(1) with histogram

