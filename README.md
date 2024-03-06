# Diseño y desarrollo de un sistema de planificación de la CPU para un sistema distribuído, proyecto para la asignatura Sistemas Operativos (3º) del GETT de la UVigo

En este proyecto se ha diseñado e implementado un sistema de planificación de la CPU que da servicio a un sistema distribuído de compraventa de entradas denominado "Taquilla virtual". Dicho sistema distribuído contará con una serie de procesos servidores encargados de realizar las distintas tareas de procesamiento que atienden a los usuarios del sistema. El proyecto se ha desarrollado en un entorno Linux con distribución OpenSuse v12.3 de 32 bits.

Los diferentes procesos servidores de cada nodo tendrán distintas prioridades y, por lo tanto, serán clasificados en diferentes colas, cada una con su algoritmo de planificación correspondiente, y cuyo orden a su vez estará definido por el algoritmo de planificación de colas multinivel del sistema. Los diferentes procesos, ordenados de mayor a menor prioridad, son:

- Mantenimiento (Algoritmo de planificación FIFO)
- Pago (Algoritmo de planificación FIFO)
- Administración (Algoritmo de planificación FIFO)
- Anulación (Algoritmo de planificación RR)
- Reserva (Algoritmo de planificación RR)
- Consulta (Algoritmo de planificación RR)

A su vez, estos procesos serán clasificados como procesos de alta o baja prioridad, cada grupo formado por los 3 procesos más prioritarios o menos. El sistema en conjunto tendrá un límite de procesos, por lo que se establecerá para la entrada de nuevos procesos un límite de alta prioridad (k) y otro de baja prioridad (m). Esto permitirá establecer una holgura para que el sistema no colapse impidiendo procesos importantes ajenos a los indicados. Además, si el sistema llega al límite de procesos, un proceso k podrá entrar siempre que haya un proceso m que pueda ser eliminado.

Los procesos también estarán limitados a permanecer un tiempo t1 en el sistema.

El directorio linux_src contiene exclusivamente aquellos archivos del kernel que se han creado o modificado para el desarrollo del proyecto. El script pruebas.c contiene una serie de pruebas que se podrán ejecutar para testear el correcto desempeño de las funcionalidades del sistema, llamando a los scripts nombre_del_proceso.c correspondientes. Éstos últimos scripts constarán de un bucle de varios segundos de duración que permitirán simular el proceso correspondiente.
