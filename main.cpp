#include <gl/glut.h>
#include <math.h>

//Функция изменения размеров и установки координат
void Reshape(int width, int height)
{
//Установка порта вывода
    glViewport(0, 0, width, height);

//Режим матрицы проекций
    glMatrixMode(GL_PROJECTION);
//Единичная матрица
    glLoadIdentity();

//Установка двумерной ортографической системы координат
    gluOrtho2D(-50., 50., -50., 50.);

//Режим видовой матрицы
    glMatrixMode(GL_MODELVIEW);
}

//Функция визуализации
void Draw(void)
{
//Очистка цветового буфера
    glClear(GL_COLOR_BUFFER_BIT);

//Установка цвета отображения
    glColor3d(1.0, 1.0, 0.0);

//Рисование осей
    glBegin(GL_LINES);
//Установка вершин
        glVertex2d(-40., .0);
        glVertex2d(40., .0);
        glVertex2d(.0, -40.);
        glVertex2d(.0, 40.);
//Завершить рисование осей
    glEnd();
    glBegin(GL_QUADS);
    glVertex2d(-10, -10);
    glVertex2d(-10,  0);
    glVertex2d( 0,  0);
    glVertex2d( 0, -10);
    glEnd();


//Установка цвета отображения ломаной
    glColor3d(0.0, 1.0, 1.0);

//Рисование ломаной линии
    glBegin(GL_LINE_STRIP);

    double x,y;
    for(double fi=0; fi<20.*acos(0.); fi+=2.*acos(0.)/20.)
    {
    //Вычисление координат
        x=fi*cos(fi);
        y=fi*sin(fi);

    //Установка вершины ломаной
        glVertex2d(x, y);
    }

//Завершить рисование ломанной
    glEnd();

//Завершить выполнение команд
    glFlush();
}

int main(int argc, char *argv[])
{
//Инициализация GLUT
    glutInit(&argc, argv);
//Задание размеров окна
    glutInitWindowSize(400, 300);
//Задание положения окна
    glutInitWindowPosition(100, 100);

//Инициализация режимов
    glutInitDisplayMode(GLUT_RGB);
//Задание заголовка окна
    glutCreateWindow("Whirlpool");

//Определить функцию изменения размеров
    glutReshapeFunc(Reshape);
//Определить функцию перерисовки
    glutDisplayFunc(Draw);

//Определить цвет очистки
    glClearColor(0, 0, 0, 1);

//Вход в главный цикл GLUT
    glutMainLoop();

    return 0;
}