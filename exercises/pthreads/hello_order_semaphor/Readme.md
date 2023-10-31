 ###¿Produce el mismo resultado que su solución anterior?

Si. Esta version bloquea el primer hilo desde el inicio y el primer hilo no comienza automáticamente sino que depende del hilo principal para iniciar su ejecución, sin embargo, al activarse primero el hilo cero el orden seguira igual despues dando al final el mismo resultado.

###¿Qué pasa si el hilo principal incrementa el semáforo del hilo 0 después de hacer su saludo Hello from main thread?

Al incrementar el semaphor da paso a que el hilo 0 inicie la ejecucion, esto despues de imprimir.