#include <linux/sched.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/signal.h>
#include <asm/siginfo.h>
#include <linux/controlador.h>

void ControladorProcesos (struct task_struct* p) {
  
     // Codigo para las llamadas a pruebas.c
     if (strcmp(p->comm, "pruebas") == 0 ) {

           struct sched_param cola0 = { .sched_priority = 99 };

           sched_setscheduler(p, SCHED_FIFO, &cola0);
         
     }
    

     // Gestion de llamadas al resto de tipos
     if (strcmp(p->comm,"mantenimiento")==0){

        if(comprobar_m_k(p, 1)==0){

            struct sched_param cola1 = { .sched_priority = 50 };

            sched_setscheduler(p, SCHED_FIFO, &cola1);

            printk(KERN_INFO "Se añade un proceso %s a la cola con prioridad 50\n", p->comm);

        } else {

            printk(KERN_INFO "NO PUEDES PASAR, PROCESO %s (%d)", p->comm, p->pid);

            kill_pid(find_vpid(p->pid), SIGKILL,1);

        }
     }

    if (strcmp(p->comm,"pago")==0){

        if(comprobar_m_k(p, 1)==0){

            struct sched_param cola2 = { .sched_priority = 40 };

            sched_setscheduler(p, SCHED_FIFO, &cola2);

            printk(KERN_INFO "Se añade un proceso %s a la cola con prioridad 40\n", p->comm);

        } else {

            printk(KERN_INFO "NO PUEDES PASAR, PROCESO %s (%d)", p->comm, p->pid);

            kill_pid(find_vpid(p->pid), SIGKILL,1);

        }
     }
    if (strcmp(p->comm,"administracion")==0){

        if(comprobar_m_k(p, 1)==0){

            struct sched_param cola3 = { .sched_priority = 25 };

            sched_setscheduler(p, SCHED_FIFO, &cola3);

            printk(KERN_INFO "Se añade un proceso %s a la cola con prioridad 25\n", p->comm);

        } else {

            printk(KERN_INFO "NO PUEDES PASAR, PROCESO %s (%d)", p->comm, p->pid);

            kill_pid(find_vpid(p->pid), SIGKILL,1);

        }
     }

     if (strcmp(p->comm,"anulacion")==0){

        if(comprobar_m_k(p, 0)==0){

            struct sched_param cola4 = { .sched_priority = 20 };

            sched_setscheduler(p, SCHED_RR, &cola4);

            printk(KERN_INFO "Se añade un proceso %s a la cola con prioridad 20\n", p->comm);

        } else {

            printk(KERN_INFO "NO PUEDES PASAR, PROCESO %s (%d)", p->comm, p->pid);

            kill_pid(find_vpid(p->pid), SIGKILL,1);

        }
     }

     if (strcmp(p->comm,"reserva")==0){

        if(comprobar_m_k(p, 0)==0){

            struct sched_param cola5 = { .sched_priority = 15 };

            sched_setscheduler(p, SCHED_RR, &cola5);

            printk(KERN_INFO "Se añade un proceso %s a la cola con prioridad 15\n", p->comm);
  
        } else {

            printk(KERN_INFO "NO PUEDES PASAR, PROCESO %s (%d)", p->comm, p->pid);

            kill_pid(find_vpid(p->pid), SIGKILL,1);

        }
     }

     if (strcmp(p->comm,"consulta")==0){

        if(comprobar_m_k(p, 0)==0){

            struct sched_param cola6 = { .sched_priority = 10 };

            sched_setscheduler(p, SCHED_RR, &cola6);

            printk(KERN_INFO "Se añade un proceso %s a la cola con prioridad 10\n", p->comm);

        } else {

            printk(KERN_INFO "NO PUEDES PASAR, PROCESO %s (%d)", p->comm, p->pid);

            kill_pid(find_vpid(p->pid), SIGKILL,1);
        }
     }
  
}


// Si devuelve 1, se mata al proceso entrante, si no, devuelve 0
int comprobar_m_k(struct task_struct* p, int es_m){

    int procesos_maximos = 15;

    int procesosencola = 0;

    int procesos_k_en_cola = 0;

    // Cantidad de procesos en el sistema

    for_each_process(p){
        
        if ((strcmp(p->comm,"mantenimiento")==0)||(strcmp(p->comm,"pago")==0)||(strcmp(p->comm,"administracion")==0)) {
            procesosencola ++;
        }

        // Contador separado de procesos k (poco prioritarios)

        if((strcmp(p->comm,"consulta")==0)||(strcmp(p->comm,"reserva")==0)||(strcmp(p->comm,"anulacion")==0)) {
            procesosencola ++;
            procesos_k_en_cola ++;
        }
    }

    // Si no se llega al maximo, devuelve 0 y mete el nuevo proceso
    if(procesosencola < (procesos_maximos + 1)) {
        
        return 0;
    
    // Si el sistema esta lleno y hay un proceso k, se busca una victima solo si el proceso es un m
    } else { 
        if( (procesos_k_en_cola > 0) && (es_m == 1) ) { 

            buscavictima(p);

            return 0;   
        }
    // Si el sistema esta lleno y no hay procesos k o no esta entrando un proceso m, se elimina el que intenta entrar
    }
    return 1;
}


void buscavictima(struct task_struct* p){
   
    unsigned long tiempo_maximo = 0;
    unsigned long tiempo_en_cpu;
    int pid_tiempo_maximo = 0;    
    char nombre_proceso_eliminado[20];
;

    printk(KERN_INFO "Buscando un proceso menos prioritario para eliminarlo y dar paso al nuevo...\n");

    for_each_process(p){
      
        if((strcmp(p->comm,"consulta")==0)||(strcmp(p->comm,"reserva")==0)||(strcmp(p->comm,"anulacion")==0)){

            tiempo_en_cpu = cputime_to_secs(p->utime);      

            if (tiempo_en_cpu  > tiempo_maximo) {

                tiempo_maximo = tiempo_en_cpu;
                pid_tiempo_maximo = p->pid;
                strcpy(nombre_proceso_eliminado, (p->comm));

            }
        }
    }
         
    //printk(KERN_INFO "Se mata al proceso %s (%d), proceso menos prioritario que mas tiempo lleva en el sistema.\n", nombre_proceso_eliminado, pid_tiempo_maximo);
    kill_pid(find_vpid(pid_tiempo_maximo), SIGKILL, 1);   
    return;

}



void so_timer() {

     struct task_struct* p;

     unsigned long tiempo_en_cpu;

     unsigned long t_maximo_permitido = 30;
     
     for_each_process(p){

        if( (strcmp("mantenimiento", p->comm) == 0) || (strcmp("pago", p->comm) == 0) || (strcmp("anulacion", p->comm) == 0) || (strcmp("reserva", p->comm) == 0) || (strcmp("administracion", p->comm) == 0) || (strcmp("consulta", p->comm) == 0) ) {

            tiempo_en_cpu = cputime_to_secs(p->utime);
          
            if (tiempo_en_cpu > t_maximo_permitido) {
                  
                printk(KERN_INFO "El proceso %s lleva %lu segundos en cpu, debe morir.", p->comm, tiempo_en_cpu);
               
                kill_pid(find_vpid(p->pid),SIGKILL, 1);

            }
        }
    }
  
    return;

}
