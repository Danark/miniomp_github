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

//inicia el contador de criticals dentro de un loop
//void init_critical_dependences();

void calc_max_dependences();

//evento Extrae que indica el inicio de una region critica
void start_event_critical(int id);

//evento Extrae que indica el fin de una region critica
void end_event_critical(int id);

//inicia el contador de tareas dentro de un loop
void init_loop_dependences();

//evento Extrae que indica el inicio de una task
void start_event_task();

//evento Extrae que indica el fin de una task
void end_event_task();

//evento que inicializa el hash
void init_hash();

//evento que busca en el hash
int found_hash(int id);

//evento que a;ade en el hash
int insert_hash(int id);
