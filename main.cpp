#include <iostream>

#include "Application.h"
#include "Panel.h"
#include "PushButton.h"

int main() {
  Application app;

  Panel w;
  Panel w2(&w);
  Panel w3(&w2);
  Panel w4(&w3);
  Panel w5(&w);
  PushButton btn(&w);

  w.show();

  app.run();
  return 0;
}
