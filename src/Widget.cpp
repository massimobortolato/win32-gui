#include "Widget.h"

#include <iostream>

#include "internal/Environment.h"

//--------------------------------------------------------------------------------------------------
Widget::Widget(Widget* parent) : _parent(parent) {
  _hwnd = createHandle(parent);
  Environment::registerWidget(this);
}

//--------------------------------------------------------------------------------------------------
Widget::~Widget() {
  std::cout << "onDestroy\n";
}

//--------------------------------------------------------------------------------------------------
Widget::Handle* Widget::createHandle(Widget* parent) {
  return reinterpret_cast<Handle*>(CreateWindowEx(0, Environment::className(), "Widget",
                                                  WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                                  800, 600, NULL, NULL, Environment::hInstance(), NULL));
}

//--------------------------------------------------------------------------------------------------
void Widget::onCreate() {}

//--------------------------------------------------------------------------------------------------
void Widget::onResize(int w, int h) {
  std::cout << "onResize: " << w << "x" << h << "\n";
}

//--------------------------------------------------------------------------------------------------
void Widget::onClose() {
  std::cout << "onClose\n";
}

//--------------------------------------------------------------------------------------------------
void Widget::show() {
  ShowWindow(reinterpret_cast<HWND>(_hwnd), SW_SHOW);
}

//--------------------------------------------------------------------------------------------------
void Widget::hide() {
  ShowWindow(reinterpret_cast<HWND>(_hwnd), SW_HIDE);
}
