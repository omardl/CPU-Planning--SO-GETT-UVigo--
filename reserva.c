#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

    usleep((long)1/10000000000000);
    
    if (argc != 1) {

      printf("Debes introducir un entero, para una duracion normal es aconsejable el 10.\n");
      
     /*Con un 4 la duracion de cada proceso esta entre 5 y 10 segundos*/
     /*Con un 10, algo menos de 20 segundos*/
     /*Con un 20, algo mas de 30 segundos*/
     /*Si queremos que dure mas de un minuto, debe ser de 40 para arriba*/
     /*El tiempo que dura un proceso no va a ser el mismo que el del uso de la cpu, asi que para 
asegurar procesos largos mejor ponerle un numero de 3 cifras*/


    } else {

        int tipo = atoi(argv[0]);
    
        int i, bucle;
        
        for (bucle = 0; bucle < tipo; bucle++){
            for(i=0; i < 1000000000; i++) {

                //Un printf vacio aumenta ligeramente el delay de cada iteraccion
                printf("");

                if ( (bucle == 0) && (i == 1) ) {

                     printf("Proceso de reserva iniciado.\n");

                } 
            }
        }
         
        printf("Proceso de reserva finalizado.\n");

    }

    return 0;

}
