set terminal svg enhanced size 800, 600 
set style data lines

set style line 1 lc rgb "red" lw 3
set style line 2 lc rgb "green" lw 3
set style line 3 lc rgb "orange" lw 3

set xlabel "Day of Year"
set ylabel "Ice Concentration (%)"
set grid

set title "Lake Superior Ice Concentration"
set xrange [1:200]
set yrange [0:82]
plot "superior.dat" using 1:2 title "2021-2022" with lines ls 1, \
     "superior.dat" using 1:3 title "2022-2023" with lines ls 2, \
     "superior.dat" using 1:4 title "2023-2024" with lines ls 3


set title "Lake Michigan Ice Concentration"
set xrange [1:200]
set yrange [0:40]
plot "michigan.dat" using 1:2 title "2021-2022" with lines ls 1, \
     "michigan.dat" using 1:3 title "2022-2023" with lines ls 2, \
     "michigan.dat" using 1:4 title "2023-2024" with lines ls 3

set title "Lake Huron Ice Concentration"
set xrange [1:200]
set yrange [0:70]
plot "huron.dat" using 1:2 title "2021-2022" with lines ls 1, \
     "huron.dat" using 1:3 title "2022-2023" with lines ls 2, \
     "huron.dat" using 1:4 title "2023-2024" with lines ls 3


set title "Lake Erie Ice Concentration"
set xrange [1:200]
set yrange [0:100]
plot "erie.dat" using 1:2 title "2021-2022" with lines ls 1, \
     "erie.dat" using 1:3 title "2022-2023" with lines ls 2, \
     "erie.dat" using 1:4 title "2023-2024" with lines ls 3


set title "Lake Ontario Ice Concentration"
set xrange [1:200]
set yrange [0:30]
plot "ontario.dat" using 1:2 title "2021-2022" with lines ls 1, \
     "ontario.dat" using 1:3 title "2022-2023" with lines ls 2, \
     "ontario.dat" using 1:4 title "2023-2024" with lines ls 3


set title "Lake St. Clair Ice Concentration"
set xrange [1:200]
set yrange [0:110]
plot "stclair.dat" using 1:2 title "2021-2022" with lines ls 1, \
     "stclair.dat" using 1:3 title "2022-2023" with lines ls 2, \
     "stclair.dat" using 1:4 title "2023-2024" with lines ls 3
