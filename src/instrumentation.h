//OpenMP intstrumentation//

//evento Extrae que indica el fin de un region paralela de un thread en concreto//
void start_event_thread ();

//evento Extrae que indica el inicio de un region paralela de un thread en concreto//
void end_event_thread();

//evento Extrae que indica el inicio de un chunk de iteraciones//
void start_event_loop ();

//evento Extrae que indica el inicio de un chunk de iteraciones//
void end_event_loop ();

//evento Extrae que indica dependencias entre tareas
void start_horizontal_dependences (int dependence);

//evento Extrae que indica dependencias entre tareas 
void start_vertical_dependences ();

//se setean el valor de la variable que cuenta el numero de dependencias acomuladas
void set_count_dependences (int dependence);

//evento Extrae que indica el inicio de una region critica
void start_event_critical();

//evento Extrae que indica el fin de una region critica
void end_event_critical();

//evento Extrae que inicia el contador de tareas dentro de un loop
void init_task_dependences();

//evento Extrae que indica el inicio de una task
void start_event_task();

//evento Extrae que indica el fin de una task
void end_event_task();
