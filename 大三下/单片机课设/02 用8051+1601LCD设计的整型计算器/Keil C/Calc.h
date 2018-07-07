//-----------------------------------------------------------------
// calc.h 头文件
//-----------------------------------------------------------------
#define MAX_DISPLAY_CHAR 9	//定义适合屏幕显示的ASCII字符的最大个数
enum ERROR { OK = 0, SLEEP = 1, ERROR = 2};	// 错误处理状态
//-----------------------------------------------------------------
// 函数声明
//-----------------------------------------------------------------
void Operator_Process(char token);
int  calc_chkerror(long num);
void LCD_Disp_String(char buf[]);
void Initialise_LCD();
char GetKeyChar();
void Clearscreen();