#include "Environment.h"

#include <iostream>

//--------------------------------------------------------------------------------------------------
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  return Environment::WindowProc(hwnd, uMsg, wParam, lParam);
}

//--------------------------------------------------------------------------------------------------
static LRESULT CALLBACK D2DSurfaceProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  return Environment::D2DSurfaceProc(hwnd, uMsg, wParam, lParam);
}

//--------------------------------------------------------------------------------------------------
void Environment::initialize(HINSTANCE hInstance) {
  if (instance()._hInstance.has_value() == false) {
    instance()._hInstance = hInstance;

    WNDCLASS wc = {};
    WNDCLASS wcD2D = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = Environment::className();
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    RegisterClass(&wc);

    wcD2D.lpfnWndProc = D2DSurfaceProc;
    wcD2D.hInstance = hInstance;
    wcD2D.lpszClassName = Environment::d2dClassName();
    RegisterClass(&wcD2D);
  }
}

//--------------------------------------------------------------------------------------------------
LRESULT Environment::WindowProc_(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  auto widgetOpt = widgetForHwnd(hwnd);

  if (widgetOpt.has_value()) {
    auto widget = widgetOpt.value();

    if (uMsg == WM_CREATE) {
      widget->onCreate();
      return 0;
    }

    if (uMsg == WM_SIZE) {
      RECT rc;
      GetClientRect(hwnd, &rc);
      widget->onResize(rc.right - rc.left, rc.bottom - rc.top);
      return 0;
    }

    if (uMsg == WM_CLOSE) {
      widget->onClose();
      DestroyWindow(hwnd);
      return 0;
    }

    if (uMsg == WM_DESTROY) {
      _widgets.erase(hwnd);
      if (_widgets.empty()) {
        PostQuitMessage(0);
      }
      return 0;
    }
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//--------------------------------------------------------------------------------------------------
LRESULT Environment::D2DSurfaceProc_(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}