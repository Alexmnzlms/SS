#ifndef CODGEN
#define CODGEN

double uniforme();
double* construye_prop_a(int n);
double* construye_prop_b(int n);
double* construye_prop_c(int n);
int genera_demanda(double* tabla, int tama);

int * tabla_indices_ord(int n);
double* construye_prop_c_ord(int n, int* indices);
int genera_demanda_ord(double* tabla, int* indices, int tama);

int genera_demanda_bb(double* tabla, int tama);

int genera_demanda_constante(int tama);

#endif

