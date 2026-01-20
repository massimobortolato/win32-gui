#pragma once

#include "Widget.h"

class PushButton : public Widget {

 public:
  PushButton(Widget* parent = nullptr);
  ~PushButton();
};
