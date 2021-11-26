#include <iostream> //  заголовочный файл с классами, функциями и переменными для организации ввода-вывода в языке программирования C++
#include <windows.h>
#include <conio.h> // запоминает нажатие не перерывая консоль
using namespace std; //Строка using namespace std; сообщает компилятору, что нужно использовать группу функций, которые являются частью стандартной библиотеки std.

bool gameover; 
const int width = 40; // Ширина поля для змейки
const int height = 20; 
int x, y, fX, fY,score ;// корды змейки  а так же фруктов и счет
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // возможные пути игрока
eDirection dir;
void mainn()
{
    srand(time(0)); // запуск генератора случайных чисел
    rand(); // холостой ход генератора случаный чисел
    system("mode con cols=51 lines=31"); // установка размеров окна консоли
    MoveWindow(GetConsoleWindow(), 50, 50, 2000, 2000, true); // установка стартовой позиции окна консоли (50 и 50 - это пиксели
}

void Setup() {
    
    gameover = false; // по умолчанию
    dir = STOP; // змейка стоит
    x = width / 2 - 1; // ровняем по центру
    y = height / 2 - 1; // отнимаем, ибо писали +1 ниже
    fX = rand() % width; // Рандомизация фруктов
    fY = rand() % height;

    score = 0;

} // настройка параметров игры

void Draw() {

    system("cls"); // очистка терминала при вызове функции

    for (int i = 0; i < width + 1; i++)
        cout << "#";
    cout << endl; /* Верхняя граница*/

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) 
        {
            if (j == 0)
                cout << "#"; // если это первый елемент, то тут нужна граница
            if (i == y && j == x) // корды для змейки
                cout << "1";
            else if (i == fY && i == fX)
                cout << "f";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        cout << "0"; // отрисовка хвоста
                    }
                }
            }
                cout << " ";  
        }
        cout << endl;
    }
    for (int j = 0; j < width; j++) {
        if (j == 0 || width - 1)
            cout << "#";
            cout << endl;
    }
         
        // проверка ячеек по ширине, и тд..
     //боковые границы. Первая и последняя граница будет с |. Остальные с пробелом.

    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl; /* Нижняя граница*/
     // Прорисовка границы карты

} // Отрисовка карты

void Input() {
    Sleep(10);
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
               dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        }// какую клавищу он точно нажал
    }//отслеживание кнопки пользователя

} // Отслеживание нажатий

void Logic() {
    int prevX = tailX[0];// отображение хвоста змеи
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i]; // второй элемент в хвосте
        prev2Y = tailY[i];
        tailX[i] = prev2X;
        tailX[i] = prev2Y;
        prevX = prev2X;
        prevY = prev2Y;

    }
    switch (dir)
    {
   
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
 
    } // проверка движения
    if (x > width || x < 0 ||y> height || y < 0) // проверка поля для окончания игры
        gameover = true;
    
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;
    }// проверка на скушанный хвост

    if (x == fX && fY) {
        score +=5 ; // балы за фрукт
        fX = rand() % width; // Рандомизация фруктов
        fY = rand() % height;
        nTail++;
    }
} // Логика игры

int main() //Строка using namespace std; сообщает компилятору, что нужно использовать группу функций, которые являются частью стандартной библиотеки std.
{
    int sleep_time = 30; // переменная частоты кадров 
    Setup(); // Вызов для настройки
    while (!gameover /*пока включенна она, включаются функции ниже*/) {
        Draw();
        Input();
        Logic();
    }
}
