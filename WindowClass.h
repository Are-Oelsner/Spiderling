#ifndef __WINDOWCLASS_H__
#define __WINDOWCLASS_H__

class WindowClass {
  protected:
    ///Private Variables
    int g_width{1360};
    int g_height{768};
    int g_window{0};

  public:
    ///Constructors
    WindowClass();

    WindowClass(int t_width, int t_height, int t_window);

    //~WindowClass();

    ///Functions
    //Getters
    int width();
    int height();
    int window();

    //Setters
    void width(int width);
    void height(int height);
    void window(int window);
};

#endif
