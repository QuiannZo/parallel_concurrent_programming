Excecution times.

hello_order_semaphor avg: 0,001052s
1. 0.00106896s
2. 0.00108426s
3. 0.00100501s

hello_order_cond_safe avg: 0,001138s
1. 0.00111936s
2. 0.00122465s
3. 0.00107356s

El que tarda menos tiempo es hello_order_cond_safe. Esto se debe al uso
independiente, entre comillas, de la memoria, que hace que los hilos no 
tengan que esperar para poder imprimir datos, quitando asi el cuello de 
botella que existe cuando los hilos intentan escribir al output.