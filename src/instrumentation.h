//OpenMP intstrumentation//

//evento Extrae que indica el fin de un region paralela de un thread en concreto//
void start_event_thread ();

//evento Extrae que indica el inicio de un region paralela de un thread en concreto//
void end_event_thread();

//evento Extrae queindica el inicio de un chunk de iteraciones//
void start_event_loop ();

//evento Extrae queindica el inicio de un chunk de iteraciones//
void end_event_loop ();