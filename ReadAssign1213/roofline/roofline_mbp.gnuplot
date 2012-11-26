set term postscript eps enhanced clip
set output "roofline.eps"



# functions
min(a,b)	= a < b ? a : b
max(a,b) 	= a > b ? a : b
deg2rad(d)	= d * pi / 180
rad2deg(r)	= r * 180 / pi


# window settings

x_min = 0.0625
x_max = 16
y_min = 0.0625
y_max = 128

# constants
cpu_freq	= 2.8
cpu_cores	= 2
cpu_flops	= 8
mem_freq	= 1.066 
mem_chan	= 2
mem_width	= 8

# roofline

cpu_peak_perf = cpu_cores * cpu_flops * cpu_freq
mem_peak_perf = mem_freq * mem_chan * mem_width

mem_angle = 45
mem_b 	  = tan(deg2rad(mem_angle))

cpu_roof(x)	= inter_y
mem_roof(x) = mem_roof_a * x ** mem_b
roofline(x) = min(cpu_roof(x),mem_roof(x))

# intersections
inter_x	= cpu_peak_perf / mem_peak_perf
inter_y = cpu_peak_perf

# aux roof functions

mem_a(m) 	= exp( log( cpu_peak_perf ) - log( m ) * mem_b )
mem_x0(a)	= exp( log( y_min / a ) / mem_b )

mem_roof_a = mem_a(inter_x)
mem_roof_x0 = mem_x0(mem_roof_a)


# labels
set xlabel "Operational Intensity (Flops/Byte)"
set ylabel "Attainable GFlops/s"

# ceilings

cpu_half(x) = cpu_roof(x) / 2
cpu_qrtr(x)	= cpu_roof(x) / 4
cpu_octo(x)	= cpu_roof(x) / 8

mem_half(x) = mem_roof(x) / 2

# more window settings

set xrange [x_min:x_max]
set yrange [y_min:y_max]
set logscale x 2
set logscale y 2

#labels




# plot
set grid
set nokey
set size square
set multiplot

plot min( cpu_half(x), mem_roof(x) ) 
plot min( cpu_qrtr(x), mem_roof(x) ) 
plot min( cpu_octo(x), mem_roof(x) ) 

plot min( mem_half(x), cpu_roof(x) )


plot roofline(x)
