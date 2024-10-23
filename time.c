#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Verificar que hay un comando
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
        exit(1); 
    }

    struct timeval start, end; // Estructura para almacenar el tiempo
    pid_t pid; // Variable para almacenar el PID del hijo

    // Obtener el tiempo inicial antes de ejecutar el comando
    gettimeofday(&start, NULL);

    // Crear un nuevo proceso hijo
    pid = fork();

    if (pid < 0) { // Error al crear el proceso
        perror("Error en fork");
        exit(1);
    } else if (pid == 0) { // Proceso hijo
        // Se ejecuta comanddo que ingresó como argumento
        execvp(argv[1], &argv[1]);
        // Si execvp falla, mostrar un error y salir
        perror("Error en execvp");
        exit(1);
    } else { // Proceso padre
        int status; // Variable para almacenar el estado del hijo
        // Esperar a que el hijo termine su ejecución
        waitpid(pid, &status, 0);
        
        // Obtener el tiempo final después de que el hijo ha terminado
        gettimeofday(&end, NULL);

        // Calcular el tiempo transcurrido
        long seconds = end.tv_sec - start.tv_sec; // Diferencia en segundos
        long microseconds = end.tv_usec - start.tv_usec; // Diferencia en microsegundos
        double elapsed = seconds + microseconds / 1e6; // Convertir a segundos

        // Mostrar el tiempo total que tomó ejecutar el comando
        printf("Tiempo transcurrido: %.6f segundos.\n", elapsed);
    }

    return 0; // Finalizar el programa
}
