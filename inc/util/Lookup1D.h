#ifndef VCU_CORE_Lookup1D_H
#define VCU_CORE_Lookup1D_H

typedef struct Lookup1D {
    float x0;
    float x1;
    float n;
    float y[11];
} Lookup1D;

void Lookup1D_initArray(Lookup1D* lookup1d, float x0, float x1, float y[],
                        float n);
void Lookup1D_print(Lookup1D* lookup1d);
void Lookup1D_init(Lookup1D* lookup1d, float xP, float yP);  // y = kx
float Lookup1D_evaluate(Lookup1D* lookup1d, float x);

#endif