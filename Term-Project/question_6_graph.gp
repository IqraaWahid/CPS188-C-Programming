set terminal svg enhanced size 800, 600 #size of graph created
set title "Ice Concentration Percentages" #title of graph
set xlabel "Day" #x-axis label
set ylabel "Ice Percent (%)" #y-axis name
set key top right
set xrange [1:365] #x values will be from 1 to 365
set grid

#plotting the data from the text file ‘graphfile.txt’, colour of each graph is different:
plot 'graphfile.txt' using 1:2 with lines lc rgb "red" title "Sup.", \
	'' using 1:3 with lines lc rgb "blue" title "Mich.", \
    '' using 1:4 with lines lc rgb "green" title "Huron", \
    '' using 1:5 with lines lc rgb "purple" title "Erie", \
    '' using 1:6 with lines lc rgb "orange" title "Ont.", \
    '' using 1:7 with lines lc rgb "brown" title "St.Clr",
