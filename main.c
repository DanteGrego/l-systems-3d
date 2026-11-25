#include "include/controller.h"

int main(){
    Controller controller = createController();

    controllerLsystemSetAxiom(controller, ";(0)!(2)F(10)");
    controllerLsystemAddRule(controller, "F(s) -> F(s;)F(s;)!;[-&F(s/1.2;)][+^F(s/1.2;)]");
    controllerLSystemIterate(controller, 5, 1);

    controllerTurtleInitialize(controller, createVector3(0, 0, 0), createVector3(0, -1, 0), 2, 0);

    controllerTurtleDrawIteration(controller, 800, 800);

    return 0;
}