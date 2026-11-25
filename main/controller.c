#include "../include/controller.h"

Controller createController(){
    Controller controller = (Controller)malloc(sizeof(controllerT));

    controller->lsystem = createLsystem();
    controller->turtle = NULL;

    return controller;
}

void controllerLsystemSetAxiom(Controller controller, char* axiomStr){
    lsystemSetComponents(controller->lsystem, lsystemStringToComponentList(axiomStr));
}

void controllerLsystemAddRule(Controller controller, char* ruleStr){
    lsystemAddRule(controller->lsystem, createRule(ruleStr));
}

void controllerLSystemIterate(Controller controller, int cantIterations, int debugPrinting){
    for(int i = 0; i < cantIterations; i++){
        if(debugPrinting)
            printf("Generating iteration: %d/%d", i+1, cantIterations);
        lsystemIterate(controller->lsystem);
    }
}

void controllerTurtleInitialize(Controller controller, vector3 position, vector3 direction, float lineWidth, float lineColorHue){
    controller->turtle = createTurtle(position, direction, lineWidth, lineColorHue);
}

void controllerTurtleDrawIteration(Controller controller, int windowWidth, int windowHeight){
    InitWindow(windowWidth, windowHeight, "Lsystem");
    SetTargetFPS(30);
    SetMousePosition(windowWidth/2, windowHeight/2);
    DisableCursor();

    List lineList = turtleFollowInstructionList(controller->turtle, controller->lsystem->iterationComponents);

    Camera camera;
    camera.position = (Vector3){0, -50, -20};
    camera.target = (Vector3){0, 0, 0};
    camera.up = (Vector3){0, -1, 0};
    camera.projection = CAMERA_PERSPECTIVE;
    camera.fovy = CAMERA_FOV;

    while(!WindowShouldClose()){
        float dx = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S)) * CAMERA_VELOCITY;
        float dy = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * CAMERA_VELOCITY;
        float dz = (IsKeyDown(KEY_E) - IsKeyDown(KEY_Q)) * CAMERA_VELOCITY;
        Vector2 mouseDelta = GetMouseDelta();
        UpdateCameraPro(&camera, (Vector3){dx, dy, dz}, (Vector3){mouseDelta.x * CAMERA_SENSITIVITY, mouseDelta.y * CAMERA_SENSITIVITY, 0}, 0);
        SetMousePosition(windowWidth/2, windowHeight/2);
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(BLACK);
        drawLineList(lineList);
        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}