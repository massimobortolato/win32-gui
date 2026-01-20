#include "Widget.h"

#include <iostream>

#include "internal/Environment.h"

//--------------------------------------------------------------------------------------------------
Widget::Widget(Widget* parent) : _parent(parent) {
}

//--------------------------------------------------------------------------------------------------
Widget::~Widget() {
  std::cout << "Widget::~Widget\n";
}

//--------------------------------------------------------------------------------------------------
void Widget::onResize(int w, int h) {
  std::cout << "Widget::onResize: " << w << "x" << h << "\n";
}

//--------------------------------------------------------------------------------------------------
void Widget::onClose() {
}

//--------------------------------------------------------------------------------------------------
void Widget::show() {
  ShowWindow(reinterpret_cast<HWND>(_hwnd), SW_SHOW);
}

//--------------------------------------------------------------------------------------------------
void Widget::hide() {
  ShowWindow(reinterpret_cast<HWND>(_hwnd), SW_HIDE);
}

//--------------------------------------------------------------------------------------------------
void Widget::setHandle(Handle* handle) {
  _hwnd = handle;
  Environment::registerWidget(this);
}

//--------------------------------------------------------------------------------------------------
Widget::Handle* Widget::getNewId() {
  static int currentId = 100;
  return reinterpret_cast<Handle*>(++currentId);
}
