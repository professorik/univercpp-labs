#include "msoftcon.h"

class circle // графический объект "круг"
{
protected:
    int xCo,yCo; // координаты центра
    int radius;
    color fillcolor; // цвет
    fstyle fillstyle; // стиль заполнения
public:
    // конструктор
    circle( int x, int y, int r, color fc, fstyle fs ):
            xCo(x), yCo(y), radius(r), fillcolor(fc), fillstyle(fs)
    { }
    void draw() // рисование круга
    {
        set_color(fillcolor); // установка цвета и
        set_fill_style(fillstyle); // стиля заполнения
        draw_circle(xCo,yCo,radius);// вывод круга на экран
    }
};

int main()
{
    init_graphics(); // инициализация графики
    // создание кругов
    circle c1(15, 7, 5, cBLUE, X_FILL);
    circle c2(41, 12, 7, cRED, O_FILL);
    circle c3(65, 18, 4, cGREEN, MEDIUM_FILL);
    c1.draw(); // рисование кругов
    c2.draw();
    c3.draw();
    set_cursor_pos(1,25); // левый нижний угол
    return 0;
} 