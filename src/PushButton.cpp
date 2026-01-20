#include "PushButton.h"

#include <Windows.h>

#include "internal/Environment.h"

//--------------------------------------------------------------------------------------------------
PushButton::PushButton(Widget* parent) : Widget(parent) {
  auto hwnd = reinterpret_cast<Handle*>(CreateWindow("BUTTON", "PushButton",
                                                     WS_TABSTOP | WS_VISIBLE | WS_CHILD,
                                                     10, 10, 100, 30,
                                                     reinterpret_cast<HWND>(parentHandle()),
                                                     reinterpret_cast<HMENU>(Widget::getNewId()),
                                                     Environment::hInstance(), nullptr));
  setHandle(hwnd);
}

//--------------------------------------------------------------------------------------------------
PushButton::~PushButton() {}
