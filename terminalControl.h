#pragma once

#define CSI "\033["

namespace tc{   //terminal control;
    
    void moveTo(int row,int col);
    void setForeColor(int id);
    void setBackColor(int id);
    void cleanScreen();
    void resetColor();
    void hideCursor();
    void showCursor();
    int transition(int chessBoardCol);
    void setScreen(int row, int col);
}