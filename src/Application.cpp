#include "Application.h"

#include <iostream>

#include "internal/Environment.h"

//--------------------------------------------------------------------------------------------------
int main(int, char**);

//--------------------------------------------------------------------------------------------------
Application::Application() {
  Environment::initialize(GetModuleHandle(nullptr));
}

//--------------------------------------------------------------------------------------------------
Application::~Application() {}

//--------------------------------------------------------------------------------------------------
void Application::run() {
  MSG msg = {};
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

//--------------------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
  Environment::initialize(hInstance);
  char arg0[] = "app";
  char* args[] = {arg0};
  return main(1, args);
}
