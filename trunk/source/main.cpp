#include "ShootMii.h"

using namespace shootmii;

Mtx GXmodelView2D;

int main() {
    
    App* app = new App();
    
    while(app->isRunning()) {  
        app->dealEvent();
        app->run();
    }
    
    delete app;
    return 0;
}
