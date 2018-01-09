#include <iostream>

#include "window.hh"

int main()
{
  srand (time(NULL));
  Window w(1366, 768);
  if (w.init_render())
    return 1;
  return w.render_loop();
}
