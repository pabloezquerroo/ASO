# **ASO**

Proyecto y ejercicios de la asignatura de Ampliación de Sistemas Operactivos.

* ## Proyecto
    ###### [Enunciado detallado](./PracticaShell/Shell.pdf)
    ###### Objetivo:
    Programar un intérprete de órdenes sencillo que permita la ejecución de trabajos con un solo programa, sin cauces, ni redirección de la entrada/salida.

    ###### Descripción:
    El programa debe soportar algunas de las características propias de los shells que detallaremos a continuación. Siempre que no se especifique lo contrario, el comportamiento será análogo al del shell por defecto (bash).

* ## Ejercicios
    *   ##### [Ficheros](./EjerciciosFicheros/Ficheros.pdf): 
        * ##### *Ejercicio 1 (Comando myls)*
            Escribir un programa con una funcionalidad semejante a la del comando ls que cumpla con unas especificaciones dadas. *Más detallado en el enunciado.*
        * ##### *Ejercicio 2 (Cerrojos)*
            Escribir un programa que consulte y muestre en la salida estándar el estado del cerrojo sobre un fichero que se pasa como argumento. *Más detallado en el enunciado.*


    * ##### [E/S Multiplexada y Pipes](./EjerciciosESMultiplexadaYPipes/E%20S%20Multiplexada%20y%20Pipes.pdf)
        * ##### *Ejercicio 1 (Tuberías con nombre)*
            Ejercicio para identificar el comportamiento de las tuberías con nombre. *Más detallado en el enunciado.*
        * ##### *Ejercicio 2 (Tueberías sin nombre)*
            Escribir un programa que emule el comportamiento de la shell en la ejecución de una sentencia en la forma: comando1 argumento 1 | comando2 argumento2. *Más detallado en el enunciado.*

    * ##### [Señales](./EjercicioSe%C3%B1ales/Se%C3%B1ales.pdf)
        * ##### *Ejercicio 1 (Señales)*
            Crear un programa (Mensaje) que muestra un texto en pantalla de manera periódica. El periodo, en segundos, se especifica como argumento de entrada del programa. Para finalizarlo es necesario mandarle la señal SIGTERM mediante el comando kill del sistema, y antes de finalizar el programa mostrará el número de segundos que han transcurrido desde su inicio. El programa ignorará la tecla de interrupción (CTRL+C). *Más detallado en el enunciado.*