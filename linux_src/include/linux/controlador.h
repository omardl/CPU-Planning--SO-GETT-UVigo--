#ifndef _GESTOR_H_
#define _GESTOR_H_

void ControladorProcesos(struct task_struct*);
int comprobar_m_k(struct task_struct* ,int);
void buscavictima(struct task_struct*);
void so_timer(void);

#endif
