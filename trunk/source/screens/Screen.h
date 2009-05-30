#ifndef SCREEN_H_
#define SCREEN_H_

#include "../ShootMii.h"

namespace shootmii {
  class Screen {
    protected:
      App* app;
    public:
      Screen(App*);
      virtual ~Screen();
      virtual void dealEvent(const u32, const u32)=0;
  };
}

#endif /*SCREEN_H_*/
