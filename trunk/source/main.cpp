#include "App.h"
#include "GRRLIB.h"

Mtx GXmodelView2D;

int main() {
	shootmii::App* app = new shootmii::App();
    while(app->isRunning()) app->run();
    delete app;
    return 0;
}
