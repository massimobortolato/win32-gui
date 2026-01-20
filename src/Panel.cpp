#include "Panel.h"

#include <Windows.h>

#include "internal/Environment.h"

//--------------------------------------------------------------------------------------------------
Panel::Panel(Widget* parent) : Widget(parent) {
  if (parent) {
    auto hwnd = reinterpret_cast<Handle*>(CreateWindow(
        Environment::className(),
        "Panel",
        WS_VISIBLE | WS_CHILD,
        0, 0,
        800, 600,
        reinterpret_cast<HWND>(parentHandle()),
        reinterpret_cast<HMENU>(Widget::getNewId()),
        Environment::hInstance(),
        this));
    setHandle(hwnd);
  } else {
    setHandle(reinterpret_cast<Handle*>(CreateWindowEx(0, Environment::className(), "Panel",
                                                       WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                                       800, 600, nullptr, nullptr, Environment::hInstance(), this)));
  }
}

//--------------------------------------------------------------------------------------------------
Panel::~Panel() {}

//--------------------------------------------------------------------------------------------------
void Panel::onResize(int w, int h) {
  // Custom onResize logic for Panel
}

//--------------------------------------------------------------------------------------------------
// void Panel::onClose() {
//   // Custom onClose logic for Panel
// }
