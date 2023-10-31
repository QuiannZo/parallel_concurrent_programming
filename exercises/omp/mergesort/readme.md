# Registre el incremento del desempeño tomando como línea base una ejecución serial.

El rendimiento de la version serial para el caso 1 modificado de la forma

    $ perf stat bin/mergesort < tests/input001.txt

fue de: 

    0,031670222 seconds time elapsed

Para la version paralela: 

    0,041384810 seconds time elapsed
