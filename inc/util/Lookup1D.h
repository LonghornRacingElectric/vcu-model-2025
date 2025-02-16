#ifndef VCU_CORE_Lookup1D_H
#define VCU_CORE_Lookup1D_H



typedef struct Lookup1D {
    float x0;
    float x1;
    float n;
    float y[11];
} Lookup1D;

#ifdef __cplusplus
extern "C" {
#endif
    void Lookup1D_initArray(Lookup1D* lookup1d, float x0, float x1, float y[], float n);
    void Lookup1D_print(Lookup1D* lookup1d);
    void Lookup1D_init(Lookup1D* lookup1d, float xP, float yP); // y = kx
    float Lookup1D_evaluate(Lookup1D* lookup1d, float x);

#ifdef __cplusplus
}
#endif

// class Lookup1D {
// private:
//     float x0 = 0;
//     float x1 = 0;
//     float n = 10.0;
//     float y[11]{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//
// public:
//     Lookup1D() = default; // y = 1
//     Lookup1D(float x0, float x1, float y[], float n);
//     void print();
//     Lookup1D(float xP, float yP); // y = kx
//     float operator()(float x);
// };


#endif