set terminal png size 800,600
set output 'output/solutions.png'
set xlabel 'Position (x)'
set ylabel 'Temperature (T)'
set title 'Profil de température'
set key top right
plot 'output/initial_condition.dat' using 1:2 with lines title 'Condition Initiale' lw 2 lc rgb 'cyan', \
     'output/exact_solution.dat' using 1:2 with lines title 'Solution Exacte' lw 2 lc rgb 'green', \
     'output/jacobi_solution.dat' using 1:2 with lines title 'Solution Jacobi' lw 2 lc rgb 'purple'
