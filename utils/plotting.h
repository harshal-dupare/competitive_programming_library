#pragma once

#include <chrono>
#include <string>
#include <iostream>
#include <graphics.h>
#include <X11/Xlib.h>

template<typename R>
class plotter
{
public:
    using namespace std;
    int point_color = 8;
    int line_color = 10;
    plotter()
    {
        XInitThreads();
        int gd = DETECT, gm;
        char driver[] = "";
        initgraph(&gd, &gm, driver);
    }

    void set_point_color(_color c)
    {
        this->point_color = c;
    }

    void set_line_color(_color c)
    {
        this->line_color = c;
    }

    void line(R x1, R y1, R x2, R y2)
    {
        setcolor(this->line_color);
        line(x1,y1,x2,y2);
    }

    void point(R x, R y)
    {
        putpixel(x, y, this->point_color);
    }

    void close()
    {
        getch();
        closegraph();
    }
};