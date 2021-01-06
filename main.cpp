#include <tchar.h>
#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <cmath>

using namespace std;
#define  RED RGB(255,0,0)
#define BLUE RGB(0,0,255)
int CurR;
int CurX, CurY;

class Circle {
    int xc, yc, Rad;
    int flag;
    HDC hdc;
public:
    void Draw() {
        MidPointMod();
    }

    void Draw8Points(int x, int y) {
        int x1 = xc + x, y1 = yc + y;
        int xx = x1 - CurX, yy = y1 - CurY;
        int R = sqrt(xx * xx + yy * yy);
        SetPixel(hdc, xc + x, yc + y, (R <= CurR ? BLUE : RED));

        x1 = xc - x, y1 = yc + y;
        xx = x1 - CurX, yy = y1 - CurY;
        R = sqrt(xx * xx + yy * yy);
        SetPixel(hdc, xc - x, yc + y, (R <= CurR ? BLUE : RED));

        x1 = xc - x, y1 = yc - y;
        xx = x1 - CurX, yy = y1 - CurY;
        R = sqrt(xx * xx + yy * yy);
        if (!flag) SetPixel(hdc, xc - x, yc - y, (R <= CurR ? BLUE : RED));


        x1 = xc + x, y1 = yc - y;
        xx = x1 - CurX, yy = y1 - CurY;
        R = sqrt(xx * xx + yy * yy);
        if (!flag) SetPixel(hdc, xc + x, yc - y, (R <= CurR ? BLUE : RED));


        x1 = xc + y, y1 = yc + x;
        xx = x1 - CurX, yy = y1 - CurY;
        R = sqrt(xx * xx + yy * yy);
        SetPixel(hdc, xc + y, yc + x, (R <= CurR ? BLUE : RED));

        x1 = xc - y, y1 = yc + x;
        xx = x1 - CurX, yy = y1 - CurY;
        R = sqrt(xx * xx + yy * yy);
        SetPixel(hdc, xc - y, yc + x, (R <= CurR ? BLUE : RED));


        x1 = xc - y, y1 = yc - x;
        xx = x1 - CurX, yy = y1 - CurY;
        R = sqrt(xx * xx + yy * yy);
        if (!flag) SetPixel(hdc, xc - y, yc - x, (R <= CurR ? BLUE : RED));

        x1 = xc + y, y1 = yc - x;
        xx = x1 - CurX, yy = y1 - CurY;
        R = sqrt(xx * xx + yy * yy);
        if (!flag) SetPixel(hdc, xc + y, yc - x, (R <= CurR ? BLUE : RED));
    }


    void MidPointMod() {
        int x = 0, y = Rad;
        int d = 1 - Rad;
        int c1 = 3, c2 = 5 - 2 * Rad;
        Draw8Points(x, y);
        while (x < y) {
            if (d < 0) {
                d += c1;
                c2 += 2;
            } else {
                d += c2;
                c2 += 4;
                y--;
            }
            c1 += 2;
            x++;
            Draw8Points(x, y);
        }

    }


public:
    Circle(int stx, int sty, int edx, int edy, HDC hdc, int flag) {
        xc = stx, yc = sty;
        int x = stx - edx, y = edy - sty;
        Rad = sqrt(x * x + y * y);
        this->hdc = hdc;
        this->flag = flag;
    }
};

class Line {
public:
    int stx, sty, edx, edy;
    HDC hdc;

    void Draw() {
        midpoint();
    }


    void midpoint() {
        double dx = edx - stx;
        double dy = edy - sty;
        double slope = dy / dx;
        if ((abs(dy) <= abs(dx)) && (slope >= 0)) {
            if (stx > edx) {
                swap(stx, edx);
                swap(sty, edy);
            }
            double d = (edx - stx) - 2 * (edy - sty);
            double change1 = 2 * (edx - stx) - 2 * (edy - sty);
            double change2 = -2 * (edy - sty);
            int x = stx;
            int y = sty;
            int xx = x - CurX, yy = y - CurY;
            int R = sqrt(xx * xx + yy * yy);
            SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));
            while (x <= edx) {
                if (d <= 0) {
                    y++;
                    d += change1;
                } else {
                    d += change2;
                }
                x++;
                xx = x - CurX, yy = y - CurY;
                R = sqrt(xx * xx + yy * yy);
                SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));
            }
        } else if ((abs(dy) > abs(dx)) && (slope > 0)) {
            if (sty > edy) {
                swap(stx, edx);
                swap(sty, edy);
            }
            double d = 2 * (edx - stx) - (edy - sty);
            double change1 = 2 * (edx - stx);
            double change2 = 2 * ((edx - stx) - (edy - sty));
            int x = stx;
            int y = sty;
            int xx = x - CurX, yy = y - CurY;
            int R = sqrt(xx * xx + yy * yy);
            SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));
            while (y <= edy) {
                if (d < 0) {
                    d += change1;
                } else {
                    x++;
                    d += change2;
                }
                y++;
                xx = x - CurX, yy = y - CurY;
                R = sqrt(xx * xx + yy * yy);
                SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));
            }

        } else if ((slope < 0) && (abs(dy) <= abs(dx))) {
            if (stx > edx) {
                swap(stx, edx);
                swap(sty, edy);
            }
            int x = stx;
            int y = sty;
            double d = -(edx - stx) - 2 * (edy - sty);
            double change1 = -2 * (edy - sty);
            double change2 = -2 * ((edx - stx) + (edy - sty));
            int xx = x - CurX, yy = y - CurY;
            int R = sqrt(xx * xx + yy * yy);
            SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));
            while (x <= edx) {
                if (d < 0) {
                    d += change1;
                } else {
                    y--;
                    d += change2;
                }
                x++;
                xx = x - CurX, yy = y - CurY;
                R = sqrt(xx * xx + yy * yy);
                
                SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));

            }

        } else {
            if (sty > edy) {
                swap(stx, edx);
                swap(sty, edy);
            }
            int x = stx;
            int y = sty;
            double d = 2 * (edx - stx) + (edy - sty);
            double change1 = 2 * (edx - stx);
            double change2 = 2 * ((edx - stx) + (edy - sty));
            int xx = x - CurX, yy = y - CurY;
            int R = sqrt(xx * xx + yy * yy);
            SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));
            while (y <= edy) {
                if (d > 0) {
                    d += change1;
                } else {
                    d += change2;
                    x--;
                }
                y++;
                xx = x - CurX, yy = y - CurY;
                R = sqrt(xx * xx + yy * yy);
                SetPixel(hdc, x, y, (R <= CurR ? BLUE : RED));

            }
        }
    }

    Line(int stx, int sty, int edx, int edy, HDC hdc) {
        this->stx = stx;
        this->sty = sty;
        this->edx = edx;
        this->edy = edy;
        this->hdc = hdc;
    }

};


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

/* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

/* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_HAND); // the second paramter is the shape
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
/* Use Windows's default colour as the background of the window */

//CHANGE THE COLOR FROM HERE
    wincl.hbrBackground = reinterpret_cast<HBRUSH>(CTLCOLOR_STATIC);
    COLOR_BACKGROUND;

/* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

/* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Code::Blocks Template Windows App"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            544,                 /* The programs width */
            375,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );
/* Make the window visible on the screen */

    ShowWindow(hwnd, nCmdShow);
    // CreateConsole();
    // ShowWindow(GetConsoleWindow(), nCmdShow);


/* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0)) {

/* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
/* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

/* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


int x, y, x2, y2, input;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wp, LPARAM lp) {
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {

        case WM_RBUTTONUP: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            break;
        }
        case WM_LBUTTONDOWN: {
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
        }

            cout << "1 -> for line drawing, so you will enter 2 mouth clicks. [1]" << "\n"
                 << "2 -> for circle drawing, so you will enter 2 mouth clicks" << "\n" <<
                 "3 -> for half circle drawing, so you will enter 2 mouth clicks. [2]" << "\n"
                 << "4 -> for new window (Circle) drawing, so you will enter 2 mouth clicks. [2]" << "\n"
                 << "5 -> To close WindowApp. [1]" << "\n";
            cin >> input;
            switch (input) {
                case 1: {
                    Line(x, y, x2, y2, hdc).Draw();
                    break;

                }
                case 2: {
                    Circle(x, y, x2, y2, hdc, 0).Draw();
                    break;

                }
                case 3: {
                    Circle(x, y, x2, y2, hdc, 1).Draw();
                    break;
                }
                case 4: {
                    RECT ret;
                    ret.left = 0, ret.right = 1366;
                    ret.bottom = 768, ret.top = 0;
                    FillRect(hdc, &ret, CreateSolidBrush(RGB(255, 255, 255)));
                    int xx = x - x2, yy = y2 - y;
                    CurR = sqrt(xx * xx + yy * yy);
                    CurX = x, CurY = y;
                    Circle(x, y, x2, y2, hdc, 0).Draw();
                    break;
                }
                case 5: {
                    SendMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                }

            }

    }
    return DefWindowProc(hwnd, message, wp, lp);
}


