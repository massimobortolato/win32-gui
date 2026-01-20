#pragma once

#include "Widget.h"

class Panel : public Widget {
 protected:
  void onResize(int w, int h) override;
  // void onClose() override;

 public:
  Panel(Widget* parent = nullptr);
  ~Panel();
};
