set output "worldgen.png"
set terminal png size 800,600;
set xlabel "X axis"
set ylabel "Y axis"
set zlabel "Z axis"
set palette grey

set title "color plot"
set contour
set dgrid3d
unset surface
set cntrparam levels auto 50
set view map
unset clabel
#
set table "contours.dat"
splot "worldgen.txt" u 1:2:3 not
unset table
unset contour

set palette defined (0 "blue", 1 "green")


plot 'worldgen.txt' matrix with image, "contours.dat" u 1:2 lc 0 w l not