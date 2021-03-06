#include <iostream>

#include "window.hh"

int main()
{
  srand (time(NULL));
  Window w(1920, 1080);
  if (w.init_render())
    return 1;
  return w.render_loop();
}
