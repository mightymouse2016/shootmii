#include "curves.h"

#include "../ShootMii.h"

namespace shootmii {

  Coordinates::Coordinates(const float _x, const float _y) :
    x(_x), y(_y) {
  }

  Function::Function(const float _a, const float _b, const float _c) :
    a(_a), b(_b), c(_c) {
  }

  void Function::setA(float _a) {
    a = _a;
  }

  void Function::setB(float _b) {
    b = _b;
  }

  void Function::setC(float _c) {
    c = _c;
  }

  PolyDeg2::PolyDeg2(const float _a, const float _b, const float _c) :
    Function(_a, _b, _c) {
  }

  float PolyDeg2::operator()(const float t) const {
    return a*t*t+b*t+c;
  }

  Affine::Affine(const float _a, const float _b) : Function(_a,_b,0) {}

  float Affine::operator()(const float t) const {
    return a*t+b;
  }

}
