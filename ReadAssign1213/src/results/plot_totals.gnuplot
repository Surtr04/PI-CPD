reset
set term postscript eps color blacktext
set output "totals.eps"

set nokey
set style fill solid
set ylabel "number of accesses"
set grid
plot "plot_totals.txt" using 2: xtic(1) with histogram

