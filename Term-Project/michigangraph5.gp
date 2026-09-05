set terminal svg enhanced size 800, 600
set style data lines

set style line 1 lc rgb "red" lw 1

set xlabel "Day of Year"
set ylabel "Ice Concentration (%)"
set grid

set title "Daily Lake Michigan Ice Concentration (2023-2024)"
set xrange [1:100]
set yrange [0:40]
plot "mich5.dat" using 1:2 title "2023-2024" with lines ls 1, \
