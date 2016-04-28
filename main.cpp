#include <iostream>
#include <stdarg.h>
#include <string>
#include <math.h>
#include <time.h>

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

static const int var = 1;
typedef VecBase<var> Vec;

float nextFloat() {
  return rand() * 1.0f / RAND_MAX;
}

float f(Vec v) {
  return v[0]*v[0];
}

static float alpha = 1.618;
static float beta = 0.618;
static float M = 20;
static float R = 0.01;
static float N = 20;
static float k = 0;
static float j = 1;

#define itv for (int i = 0; i < var; i++)

Vec find1(float m = R) {
  float t = 1;
  Vec x;
  float v;
  
  itv x[i] = nextFloat()*20 - 10;
  
  int itr = 0;
  while(++itr) {
    
    
    Vec d;
    itv d[i] = nextFloat()*2-1;
    
    Vec y;
    itv y[i] = x[i] + t*d[i];
    
    cout << itr << "\n  d="; d.log(); 
    cout << "  y="; y.log();
    cout << "  f(y) > f(x)  " << (f(y) > f(x)) << "\n";
    cout << "  t=" << t << "\n\n";
    
    if (f(y) > f(x)) {
      t *= beta;
      
      if (t <= m) {
        v = f(x);
        return x;
      }
      
      continue;
    } else {
      t *= alpha;
      x = y;
    }
    
  }
  
  return x;  
}

Vec find2() {
  float t = 1;
  float alpha = 2;
  float beta = 0.5;
  Vec x;
  
  for (int i = 0; i < var; i++) x[i] = nextFloat()*21 - 10;
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
  
  return x;
}

int main() {
  
  srand(time(0));
  
  clock_t t0 = clock();
  Vec x1 = find1(0.01);
  clock_t t1 = clock();
  Vec x2 = find2();
  clock_t t2 = clock();
  
  cout << "\n\n\n\n\n";
  cout << "x1(" << float(t1-t0)/CLOCKS_PER_SEC << ") = "; x1.log();
  cout << "x2(" << float(t2-t1)/CLOCKS_PER_SEC << ") = "; x2.log();
  cout << "f(x1) = " << f(x1) << "\nf(x2) = " << f(x2);
  
  return 0;
}

