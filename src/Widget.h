#pragma once

class Widget {
  friend class Environment;
  class Handle;

  Widget* _parent = nullptr;
  Handle* _hwnd = nullptr;

  Handle* createHandle(Widget* parent);

 protected:
  virtual void onCreate();
  virtual void onResize(int w, int h);
  virtual void onClose();

 public:
  Widget(Widget* parent = nullptr);
  virtual ~Widget();

  void show();
  void hide();
};
