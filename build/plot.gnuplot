set terminal png size 800,600
set output 'solutions.png'
set xlabel 'Position (x)'
set ylabel 'Temperature (T)'
set title 'Temperature Profile'
set key top right
plot 'initial_condition.dat' using 1:2 with lines title 'Initial condition' lw 2 lc rgb 'cyan', \
     'exact_solution.dat' using 1:2 with lines title 'Exact Solution' lw 2 lc rgb 'green', \
     'jacobi_solution.dat' using 1:2 with lines title 'Computed Jacobi Solution' lw 2 lc rgb 'purple'
