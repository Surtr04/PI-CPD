reset
set term postscript eps color blacktext
set output "caches.eps"

set nokey
set style fill solid
set yrange[0:2.5]
set ylabel "%miss_rate"
set grid
plot "plot_info.txt" using 2: xtic(1) with histogram

