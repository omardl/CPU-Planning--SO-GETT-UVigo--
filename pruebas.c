#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Los limites m y k se reducen a 15 para aportar sencillez a la comprobacion de su funcionamiento

/*********************************************************************************************************************************** 
************************************************************   PRUEBAS   *********************************************************** 
************************************************************************************************************************************ 

1. Comprobacion del funcionamiento de una cola con FIFO
    - Se prueban 4 procesos administracion

2. Comprobacion del funcionamiento de una cola con RR
    - Se prueban 4 procesos consulta

3. Comprobacion de las prioridades entre dos colas
    - Orden de entrada: 
        I) 2 procesos pago
        II) 4 procesos administracion
        III) 2 procesos pago
        IV) 2 procesos administracion
        
    - Orden de salida:
        I) 4 procesos pago
        II) 6 procesos administracion

4. Comprobacion de las prioridades entre todas las colas
    - Orden de entrada: 
        I) 2 procesos consulta
        II) 2 procesos administracion
        III) 2 procesos pago
        IV) 2 procesos mantenimiento
        V) 2 procesos reserva
        VI) 2 procesos anulacion
    
    - Orden de salida: 
        I) 2 procesos mantenimiento
        II) 2 procesos pago
        III) 2 procesos administracion
        IV) 2 procesos anulacion
        V) 2 procesos reserva
        VI) 2 procesos consulta

5. Comprobar que no se admiten procesos k al llegar al limite k
    - Orden de entrada:
        I) 5 procesos consulta
        II) 5 procesos reserva
        III) 5 procesos anulacion
        IV) 5 procesos consulta

    - Orden de salida:
        I) 5 procesos anulacion
        II) 5 procesos reserva
        III) 5 procesos consulta

6. Comprobar que no se admiten procesos k al llegar al limite m
    - Orden de entrada: 
        I) 5 procesos pago
        II) 5 procesos administracion
        III) 5 procesos mantenimiento
        IV) 1 proceso consulta

    - Orden de salida:  
        I) 5 procesos mantenimiento
        II) 5 procesos pago
        III) 5 procesos administracion

7. Comprobar que no se admiten procesos m al llegar al limite m (habiendo solo procesos m)
    - Orden de entrada: 
        I) 5 procesos pago
        II) 5 procesos administracion
        III) 5 procesos mantenimiento
        IV) 1 proceso pago

    - Orden de salida:  
        I) 5 procesos mantenimiento
        II) 5 procesos pago
        III) 5 procesos administracion

8. Comprobar que se elimina un proceso k para admitir uno m al llegar a su limite
    - Orden de entrada: 
        I) 5 procesos consulta
        II) 5 procesos mantenimiento
        III) 5 procesos pago
        IV) 1 proceso administracion

    - Orden de salida:  
        I) 5 procesos mantenimiento
        II) 1 proceso administracion
        III) 5 procesos pago
        IV) 4 procesos consulta

9. Si un proceso con FIFO pasa mas de un tiempo t1 en su cola, se elimina
    - Se prueban 2 procesos administracion con duracion mayor a t1

10. Si un proceso con RR pasa mas de un tiempo t1 en su cola, se elimina
    - Se prueban 2 procesos consulta con duracion mayor a t1

*/

void prueba1();
void prueba2();
void prueba3();
void prueba4();
void prueba5();
void prueba6();
void prueba7();
void prueba8();
void prueba9();
void prueba10();

int main (int argc, char *argv[]) {

    if (argc == 2) {

        int prueba = atoi(argv[1]);

        switch(prueba) {

        case 1:
            printf("--- PRUEBA 1 ---\n");
            prueba1();
            break; 

        case 2:
            printf("--- PRUEBA 2 ---\n");
            prueba2();
            break;

        case 3:
            printf("--- PRUEBA 3 ---\n");
            prueba3();
            break;

        case 4: 
            printf("--- PRUEBA 4 ---\n");
            prueba4();
            break;

        case 5:
            printf("--- PRUEBA 5 ---\n");
            prueba5();
            break;

        case 6:
            printf("--- PRUEBA 6 ---\n");
            prueba6();
            break;

        case 7:
            printf("--- PRUEBA 7 ---\n");
            prueba7();
            break;

        case 8:
            printf("--- PRUEBA 8 ---\n");
            prueba8();
            break;

        case 9:
            printf("--- PRUEBA 9 ---\n");
            prueba9();
            break;

        case 10:
            printf("--- PRUEBA 10 ---\n");
            prueba10();
            break;

        }


    }

    return 0;

}


void prueba1() {

    int i;
    int estado_hijo;

    
    for (i = 0; i < 4; i++) 

        if (fork() == 0) 

            execl("administracion", "4", (char*) 0);
 
    while (wait(&estado_hijo) > 0) {}
  
    return;
}

void prueba2() {

    int i;
    int estado_hijo;


    for (i = 0; i < 4; i++)

        if (fork() == 0)

            execl("consulta", "4", (char*) 0);
  
    while (wait(&estado_hijo) > 0) {}

    return;


}

void prueba3() {

    int i;
    int estado_hijo;

    for (i = 0; i < 2; i++) {
 
        if (fork() == 0) 

            execl("pago", "4", (char*) 0);

        else if(fork() == 0) 

            execl("administracion", "4", (char*) 0);

        else if (fork() == 0)

            execl("administracion", "4", (char*) 0);

        else if (fork() == 0) 

            execl("pago", "4", (char*) 0);

        else if (fork() == 0)

            execl("administracion", "4", (char*) 0);

    }

    while (wait(&estado_hijo) > 0) {}

    return;
}

void prueba4() {

    int i;
    int estado_hijo;

    for (i = 0; i < 2; i ++) {

        if (fork() == 0) 

            execl("consulta", "4", (char*) 0);

        else if(fork() == 0) 

            execl("administracion", "4", (char*) 0);

        else if(fork() == 0)  

            execl("pago", "4", (char*) 0);

        else if(fork() == 0)  

            execl("mantenimiento", "4", (char*) 0);

        else if(fork() == 0)  

            execl("reserva", "4", (char*) 0);

        else if(fork() == 0)  

            execl("anulacion", "4", (char*) 0);

    }

    while (wait(&estado_hijo) > 0) {}

    return;
}

void prueba5() {

    int i;
    int estado_hijo;

    for (i = 0; i < 5; i ++) {

        if (fork() == 0)

            execl("consulta", "3", (char*) 0);

        else if(fork() == 0)

            execl("reserva", "3", (char*) 0);

        else if(fork() == 0)

            execl("anulacion", "3", (char*) 0);

    }

    sleep(1);

    if (fork() == 0) 
    
        execl("consulta", "2", (char*) 0);

    while (wait(&estado_hijo) > 0) {}

    return;

}

void prueba6() {

    int i;
    int estado_hijo;

    for (i = 0; i < 5; i ++) {

        if (fork() == 0)

            execl("pago", "3", (char*) 0);

        else if(fork() == 0)

            execl("administracion", "3", (char*) 0);
 
        else if(fork() == 0)

            execl("mantenimiento", "3", (char*) 0);

    }

    sleep(1);

    if (fork() == 0)

        execl("consulta", "4", (char*) 0);

    while (wait(&estado_hijo) > 0) {}

    return;

}
 
void prueba7() {

    int i;
    int estado_hijo;

    for (i = 0; i < 5; i ++) {

        if (fork() == 0)

            execl("pago", "3", (char*) 0);

        else if(fork() == 0)

            execl("administracion", "3", (char*) 0);
 
        else if(fork() == 0)

            execl("mantenimiento", "3", (char*) 0);

    }

    sleep(1);

    if (fork() == 0)

        execl("pago", "2", (char*) 0);

    while (wait(&estado_hijo) > 0) {}

    return;

}
 
void prueba8() {

    int i;
    int estado_hijo;

    for (i = 0; i < 5; i ++) {

        if (fork() == 0)

            execl("consulta", "4", (char*) 0);

        else if(fork() == 0)

            execl("mantenimiento", "4", (char*) 0);
 
        else if(fork() == 0)

            execl("pago", "4", (char*) 0);

    }
    
    sleep(1);
    
    if (fork() == 0)

        execl("administracion", "4", (char*) 0);

    while (wait(&estado_hijo) > 0) {}

    return;


 
}
 
void prueba9() {

    int estado_hijo;

    if (fork() == 0) {

        execl("pago", "100", (char*) 0);

    } else {

        wait(&estado_hijo);

    }

    return;
}
 
void prueba10() {

    int estado_hijo;

    if (fork() == 0) {

        execl("consulta", "100", (char*) 0);

    } else {

        wait(&estado_hijo);

    }

    return;
 
}

