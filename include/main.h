#ifndef MAIN_H
#define MAIN_H

// init function (called before entering the app main loop)
void main_init();
// tick function (called once every frame, here you should put all you update code)
void main_tick();
// draw function (called once every frame, here you should put all you rendering code)
void main_draw();
// exit function (called after breaking out from the app main loop, before terminating the app)
void main_exit();
// resize function (called once at the start after the main_init() call and once every time a window resize event occurs)
void on_resize();

#endif