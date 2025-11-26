#pragma once

#include <windows.h>

#include <map>
#include <optional>

#include "../Widget.h"

class Environment {
  std::optional<HINSTANCE> _hInstance;
  std::map<HWND, Widget*> _widgets;

  std::optional<Widget*> widgetForHwnd(HWND hwnd) {
    auto it = _widgets.find(hwnd);
    if (it != _widgets.end()) {
      return it->second;
    }
    return std::nullopt;
  }
  static Environment& instance() {
    static Environment env;
    return env;
  }

  LRESULT WindowProc_(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  LRESULT D2DSurfaceProc_(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

 public:
  static void initialize(HINSTANCE hInstance);

  static void registerWidget(Widget* widget) {
    auto hwnd = reinterpret_cast<HWND>(widget->_hwnd);
    instance()._widgets.insert({hwnd, widget});
  }

  static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return instance().WindowProc_(hwnd, uMsg, wParam, lParam);
  }
  static LRESULT D2DSurfaceProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return instance().D2DSurfaceProc_(hwnd, uMsg, wParam, lParam);
  }
  static HINSTANCE hInstance() { return instance()._hInstance.value(); }

  static const char* className() { return "AppWindowClass"; }
  static const char* d2dClassName() { return "D2DSurfaceClass"; }
};
