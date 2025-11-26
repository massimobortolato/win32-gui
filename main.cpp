#include <iostream>

#include "Application.h"
#include "Widget.h"

int main() {
  Application app;
  Widget w;
  w.show();
  
  app.run();
  return 0;
}
