#include <iostream>
#include <stdarg.h>
#include <string>
#include <math.h>

using namespace std;

template<int S>
class VecBase {
  public:
    double v[S];
    double & operator[](int i) { return v[i]; }
    double & operator[](int i) const { return v[i]; }
    
    VecBase() {}
    VecBase(double f, ...) {
      v[0] = f;
      
      va_list vl;
      va_start(vl, f);
      for (int i = 1; i < S; i++) 
        v[i] = va_arg(vl, double);
      va_end(vl);
    }
    
    float length2() const {
      float f = 0.f;
      for (int i = 0; i < S; i++) f += v[i]*v[i];
      return f;
    }
    
    float length() const {
      return sqrt(length2());
    }
    
    void log() {
      cout << "(";
      for (int i = 0; i < S-1; i++) cout << v[i] << "; ";
      cout << v[S-1] << ")\n";
    }
};

static const int var = 2;
typedef VecBase<var> Vec;

float nextFloat() {
  return rand() * 1.0f / RAND_MAX;
}

float f(Vec v) {
  return v[0]*v[0] + v[1]*v[1];
}

static float alpha = 1.618;
static float beta = 0.618;
static float M = 20;
static float t = 1;
static float R = 0.01;
static float N = 20;
static float k = 0;
static float j = 1;

int main() {
  
  Vec x;
  for (int i = 0; i < var; i++) x[i] = rand()*21 - 10;
  
  while (true) {
    
    bool ok = false;
    
    while (true) {
      Vec ksi;
      for (int i = 0; i < var; i++) ksi[i] = nextFloat()*2 - 1;
      float ksiLength = ksi.length();
      
      Vec y;
      for (int i = 0; i < var; i++) y[i] = x[i] + t*ksi[i]/ksiLength;
      
      if (f(y) >= f(x)) break;
      
      Vec z;
      for (int i = 0; i < var; i++) z[i] = x[i] + alpha*(y[i]-x[i]);
      
      if (f(z) >= f(x)) break;
      
      x = z;
      t *= alpha;
      k++;
      if (k == N) {
        ok = true; 
        break;
      } else j = 1;
    }
    
    if (ok) break;
    
    if (j < M) j++;
    else {
      if (t <= R) break;
      else {
        t *= beta;
        j = 1;
      }
    }
    
  } 
  
  cout << "\n\n\n\n\n";
  cout << "x = "; x.log();
  cout << "f(x) = " << f(x) << "\n\n\n";
  
  return 0;
}

