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

    HFONT hFont;
    NONCLIENTMETRICS ncm = {};
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
    hFont = CreateFontIndirect(&ncm.lfMessageFont);
  }
}

//--------------------------------------------------------------------------------------------------
LRESULT Environment::WindowProc_(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  auto widgetOpt = widgetForHwnd(hwnd);

  if (uMsg == WM_CREATE) {
    std::cout << "WM_CREATE received for hwnd: " << hwnd << std::endl;
    _topHandles.push_back(hwnd);
  }

  // std::cout << "WindowProc_: hwnd=" << hwnd << " uMsg=" << std::hex << uMsg << " widget=" << (widgetOpt.has_value() ? "true" : "false") << std::endl;

  if (widgetOpt.has_value()) {
    auto widget = widgetOpt.value();

    if (uMsg == WM_CREATE) {
      std::cout << "Window created: " << hwnd << std::endl;
      // widget->onCreate();
      return 0;
    }

    if (uMsg == WM_SIZE) {
      RECT rc;
      GetClientRect(hwnd, &rc);
      widget->onResize(rc.right - rc.left, rc.bottom - rc.top);
      return 0;
    }

    if (uMsg == WM_CLOSE) {
      std::cout << "Window closed: " << hwnd << std::endl;
      widget->onClose();
      DestroyWindow(hwnd);
      return 0;
    }

    if (uMsg == WM_DESTROY) {
      _widgets.erase(hwnd);
      _topHandles.remove(hwnd);
      std::cout << "Window destroyed: " << hwnd << " widgets: " << _widgets.size() << std::endl;
      if (_topHandles.empty()) {
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

//--------------------------------------------------------------------------------------------------
void Environment::destroyWidget(Widget* widget) {
  auto hwnd = reinterpret_cast<HWND>(widget->handle());
  _widgets.erase(hwnd);
}