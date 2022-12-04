set terminal wxt size 500, 400
set title 'Original and filtered samples'
set xlabel 'Time'
set ylabel 'Amplitude'
plot 'data.tmp' title 'Data'
plot '-' w lines lc rgb 'blue' title "sampled data", '-' w lines lc rgb 'red' title "Filtered data"
0 0.000375
1 1.169076
2 0.057991
3 -0.757378
4 0.175503
5 1.143962
6 0.105087
7 -0.731211
8 0.246852
9 1.223981
e
0 0.000150
1 0.467743
2 0.373994
3 -0.051701
4 -0.028488
5 0.423013
6 0.347486
7 -0.052484
8 0.023566
9 0.485113
e
replot
