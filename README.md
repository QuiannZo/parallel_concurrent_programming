# concurrente23b-quiann_zolfaghari

## Glossary

- Programación serial: El programa corre en un solo hilo de un proceso. ESto significa que el programa se ejecuta de forma serial como lo indica su nombre.

- Programación concurrente: Se tienen varias tareas ejecutandose que no necesariamente corren a la vez. Una tarea puede progresar independientemente de las demas. Se ejecuta x programa de forma concurrente, y la memoria puede ser compartida en el proceso padre.

- Programación paralela: Se ejecuta a la vez. Se identifican partes de un proceso que se pueden desarrollar de forma independiente, para asi lograr un paralelismo. OMP permite marcar las regiones donde se puede hacer esto.

- Concurrencia de tareas: Se refiere a la ejecución simultanea de varias tareas independientes.

- Paralelismo de datos: Se dividen los datos y se procesan paralelamente. Esto implica separar las unidades de trabajo y hacer un mapeo.

- Hilo de ejecución: Unidad de ejecucion dependiente de un proceso. Un programa puede tener multiples hilos de ejecucion realizando cada uno tareas de manera concurrente.

- Indeterminismo: Se refiere a la imposibilidad de predecir el orden exacto de ejecución de las tareas en un programa concurrente. Esto es natural, sin embargo, puede "evitarse" usando barreras.

- Memoria privada y compartida: La memoria compartida es aquella que todos los hilos de un programa comparten. La privada es la memoria de cada hilo, con sus parametros, o cual sea el dato que quiera guardarse.

- Espera activa: Consiste en que un hilo esté esperando activamente a que ocurra un algo sin utilizar recursos. Esto obviamente es negativo ya que desperdicia recursos.

- Condición de carrera: El resultado de la ejecución de un programa depende del orden de ejecución de las instrucciones, y este orden no está determinado de alguna manera por el programador. Esto causa errores.

- Control de concurrencia: Se refiere a las tecnicas y mecanismos utilizados para garantizar que las operaciones concurrentes no se interfieran entre ellas.

- Seguridad condicional: Se puede usar en paralelismo de datos. Hace que los hilos puedan accesar datos sin generar condiciones de carrera.

- Exclusión mutua: Dos hilos o mas no pueden ejecutar simultaneamente secciones criticas del codigo.

- Semáforo: Un semáforo es una variable de sincronización que se usa para controlar el acceso a recursos compartidos por los hilos.

- Barrera: Un mecanismo de sincronización que permite a varios hilos esperar hasta que todos hayan alcanzado un punto específico de ejecución antes de continuar con el proceso. Cuando llega a x cantidad, "deja pasar" a los hilos.

- Variable de condición: Es una variable que se usa para sincronizar hilos. Signal deja pasar un hilo, broadcast a todos.

- Candado de lectura y escritura: Mecanismo que permite a varios hilos leer simultáneamente una sección critica pero donde solo un hilo puede escribir en la sección a la vez.

- Descomposición: Dividir un problema grande en partes más pequeñas que pueden ser resueltas concurrentemente. Esta relacionado directamente al mapeo.

- Mapeo: El mapeo consiste en dividir una carga de trabajo para que esta pueda ser trabajada de forma concurrente. Hay varios tipos de mapeo que conviene usar segun sea util en x caso.

- Incremento de velocidad: La mejora en el rendimiento de un programa lograda mediante la programación paralela o concurrente.

- Comunicación punto a punto entre procesos: Transferencia directa de datos entre dos procesos concurrentes.

- Comunicación colectiva entre procesos: Transferencia de datos entre varios procesos.

- Reducción: Un proceso en el que múltiples resultados parciales se combinan para producir un resultado final. Al final se debe hacer alguna operacion para "unir" los datos.