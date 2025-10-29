# -----------------------------------------------
# Gnuplot script: plot_trayectorias.gp
# Genera 8 gráficas PNG y 1 GIF animado a partir de results/datos.dat
# 
# Columnas en datos.dat:
# 1=t, 2=theta1, 3=omega1, 4=theta2, 5=omega2, 
# 6=KE1, 7=PE1, 8=KE2, 9=PE2, 10=E_Total
# -----------------------------------------------

# --- Configuraciones Base ---
set datafile separator whitespace
set grid
set key outside right top
set terminal pngcairo enhanced font "Arial,10"
set size 1.0, 1.0
set origin 0.0, 0.0

# =======================================================
# 1. GRÁFICA MULTIPLOT (Posición vs. T y Espacio Fase)
# =======================================================
set output 'results/trayectorias.png'
set multiplot layout 2, 1 title "Análisis de Péndulos Acoplados"

# --- Plot 1.1: Posiciones angulares vs. Tiempo ---
set size 1.0, 0.5
set origin 0.0, 0.5
set title "Posiciones angulares vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Posición θ (rad)"
plot 'results/datos.dat' every ::1 using 1:2 with lines title 'Péndulo 1 (θ_1)', \
     '' every ::1 using 1:4 with lines title 'Péndulo 2 (θ_2)'

# --- Plot 1.2: Espacio Fase (Omega vs Theta) ---
set size 1.0, 0.5
set origin 0.0, 0.0
unset title 
unset xlabel
unset ylabel
set title "Espacio Fase: Velocidad vs. Posición"
set xlabel "Posición θ (rad)"
set ylabel "Velocidad angular ω (rad/s)"
plot 'results/datos.dat' every ::1 using 2:3 with lines title 'Péndulo 1 (θ_1, ω_1)', \
     '' every ::1 using 4:5 with lines title 'Péndulo 2 (θ_2, ω_2)'

unset multiplot


# =======================================================
# 2. GRÁFICAS INDIVIDUALES (Trayectorias θ vs t y ω vs t)
# =======================================================

# --- GRÁFICA 2.1: Péndulo 1 - Posición (θ_1 vs t) ---
set output 'results/theta1_vs_t.png'
set title "Péndulo 1: Posición θ_1 vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Posición θ_1 (rad)"
plot 'results/datos.dat' every ::1 using 1:2 with lines title 'θ_1'

# --- GRÁFICA 2.2: Péndulo 1 - Velocidad (ω_1 vs t) ---
set output 'results/omega1_vs_t.png'
set title "Péndulo 1: Velocidad angular ω_1 vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Velocidad angular ω_1 (rad/s)"
plot 'results/datos.dat' every ::1 using 1:3 with lines title 'ω_1'

# --- GRÁFICA 2.3: Péndulo 2 - Posición (θ_2 vs t) ---
set output 'results/theta2_vs_t.png'
set title "Péndulo 2: Posición θ_2 vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Posición θ_2 (rad)"
plot 'results/datos.dat' every ::1 using 1:4 with lines title 'θ_2'

# --- GRÁFICA 2.4: Péndulo 2 - Velocidad (ω_2 vs t) ---
set output 'results/omega2_vs_t.png'
set title "Péndulo 2: Velocidad angular ω_2 vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Velocidad angular ω_2 (rad/s)"
plot 'results/datos.dat' every ::1 using 1:5 with lines title 'ω_2'


# =======================================================
# 3. GRÁFICAS DE MODOS DE OSCILACIÓN COLECTIVOS
# (Basadas en la posición angular θ)
# =======================================================

# --- GRÁFICA 3.1: Modo en Fase (theta1 + theta2 vs t) ---
set output 'results/modo_en_fase.png'
set title "Modo en Fase: (θ_1 + θ_2) vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Suma de Posiciones (θ_1 + θ_2) (rad)"
# Columna 2 (theta1) + Columna 4 (theta2)
plot 'results/datos.dat' every ::1 using 1:(column(2)+column(4)) with lines lc rgb "dark-green" title 'θ_1 + θ_2'

# --- GRÁFICA 3.2: Modo en Contrafase (theta1 - theta2 vs t) ---
set output 'results/modo_en_contrafase.png'
set title "Modo en Contrafase: (θ_1 - θ_2) vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Diferencia de Posiciones (θ_1 - θ_2) (rad)"
# Columna 2 (theta1) - Columna 4 (theta2)
plot 'results/datos.dat' every ::1 using 1:(column(2)-column(4)) with lines lc rgb "dark-red" title 'θ_1 - θ_2'


# =======================================================
# 4. GRÁFICAS DE ANÁLISIS DE ENERGÍA
# =======================================================
# Columna 6: KE1, 8: KE2, 10: E_Total

# --- GRÁFICA 4.1: Transferencia de Energía (KE vs t) ---
set output 'results/transferencia_energia.png'
set title "Transferencia de Energía (Energía Cinética) vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Energía Cinética KE (Joules)"
plot 'results/datos.dat' every ::1 using 1:6 with lines lc rgb "blue" title 'KE Péndulo 1', \
     '' every ::1 using 1:8 with lines lc rgb "red" title 'KE Péndulo 2'

# --- GRÁFICA 4.2: Conservación de Energía (E_Total vs t) ---
set output 'results/conservacion_energia.png'
set title "Conservación de la Energía Total vs. Tiempo"
set xlabel "Tiempo (t)"
set ylabel "Energía Total E_{Total} (Joules)"
# Columna 10 (E_Total)
plot 'results/datos.dat' every ::1 using 1:10 with lines lc rgb "black" title 'E_{Total} (Sistema Acoplado)'


# =======================================================
# 5. GIF ANIMADO DEL ESPACIO FASE (ω vs θ)
# =======================================================

# Configuración del terminal GIF (delay 5 = 20 FPS)
set terminal gif animate delay 5 optimize size 600,450
set output 'results/espacio_fase_animado.gif'

# Configuración específica del plot
set title "Espacio Fase Animado: ω vs θ"
set xlabel "Posición θ (rad)"
set ylabel "Velocidad angular ω (rad/s)"

# Usamos stats para calcular el rango de la animación (más robusto)
stats 'results/datos.dat' using 2:3 nooutput
XMin = STATS_min_x; XMax = STATS_max_x
YMin = STATS_min_y; YMax = STATS_max_y
stats 'results/datos.dat' using 4:5 nooutput
if (STATS_min_x < XMin) { XMin = STATS_min_x }
if (STATS_max_x > XMax) { XMax = STATS_max_x }
if (STATS_min_y < YMin) { YMin = STATS_min_y }
if (STATS_max_y > YMax) { YMax = STATS_max_y }

set xrange [XMin-0.1:XMax+0.1]
set yrange [YMin-0.1:YMax+0.1]

# Calcula el número total de frames
stats 'results/datos.dat' nooutput
TotalFrames = int(STATS_records / 20.0) # 1 frame por cada 20 puntos
if (TotalFrames < 10) { TotalFrames = STATS_records } 

do for [i=1:TotalFrames] {
    LineCount = i * 20
    # Grafica el Péndulo 1 (θ_1, ω_1) y Péndulo 2 (θ_2, ω_2) hasta la línea 'LineCount'
    plot 'results/datos.dat' every ::1::LineCount using 2:3 with lines lc rgb "blue" title 'Péndulo 1', \
         '' every ::1::LineCount using 4:5 with lines lc rgb "red" title 'Péndulo 2'
}

# Importante: Reestablecer la salida al final del script
unset output
# -----------------------------------------------