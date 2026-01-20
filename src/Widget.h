#pragma once

class Widget {
 protected:
  friend class Environment;
  class Handle;

 private:
  Widget* _parent = nullptr;
  Handle* _hwnd = nullptr;

 protected:
  Widget* parent() const { return _parent; }
  Handle* handle() const { return _hwnd; }
  Handle* parentHandle() const { return _parent ? _parent->_hwnd : nullptr; }
  void setHandle(Handle* handle);

 protected:
  static Handle* getNewId();

 protected:
  virtual void onResize(int w, int h);
  virtual void onClose();

 public:
  Widget(Widget* parent = nullptr);
  virtual ~Widget();

  void show();
  void hide();
};
