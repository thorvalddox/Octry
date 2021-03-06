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

set cbrange [300:700]
set palette defined (0 "blue", 1 "green")


plot 'worldgen.txt' matrix with image

do for [t=0:9] {
print("build compression ".t)
set output "worldgen".t."png"
plot 'compress'.t.'.txt' matrix with image
}