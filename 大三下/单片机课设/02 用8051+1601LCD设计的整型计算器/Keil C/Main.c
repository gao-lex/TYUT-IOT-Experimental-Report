//-----------------------------------------------------------------
// 名称:用8051+1601LCD设计的整型计算器
//-----------------------------------------------------------------
// 说明: 本例由LABCENTER ELECTRONICS公司提供,原始程序由C与汇编混合
//		编写,本例将所有代码全部改编成了C程序代码并简化了设计.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
#define INT8U  unsigned char
#define INT16U unsigned int
static long a,b;			//当前运算符的前后两个操作数
static char CurrKeyChar;	//当前按键字符
static char Last_OP;		//最近输入的操作符
static char Last_Char;		//所输入的前一字符
static char result;			//当前运算的结果状态
//显示缓冲,数字输入缓冲及数字输入缓冲区索引定义
static char xdata outputbuffer[MAX_DISPLAY_CHAR+1];
static char xdata NumberStr[MAX_DISPLAY_CHAR+1];
static char xdata NumberIdx;
char numbers[MAX_DISPLAY_CHAR] = {0};
int numsTop = 0;
char flags[MAX_DISPLAY_CHAR] = {0};
int flagsTop = 0;
char mid;
char flagCompare(char a,char b);//如果a运算符优先于b，则返回1 优先级相等返回0 a优先级小于b返回-1
int i;
int j;
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() 
{  
    a = 0; b = 0;//两个操作数初始化为0
    CurrKeyChar = '=' ; Last_OP = '0';//初始化当前按键及最近输入的操作符
    NumberStr[0] = '\0';NumberIdx = 0;//消除输入缓冲，缓冲索引归0
    
    Initialise_LCD();//初始化LCD
    LCD_Disp_String("0");//初始化显示0
    while(1)//循环扫描键盘并进行运算处理与显示
    {
        //调用矩阵键盘扫描程序，有键按下时返回按键字符，无键按下时循环扫描
        do{CurrKeyChar = GetKeyChar();}while(!CurrKeyChar);

        if(CurrKeyChar!='=' && CurrKeyChar != 'C')
        {
            if(NumberIdx<MAX_DISPLAY_CHAR)
            {
                NumberStr[NumberIdx++]=CurrKeyChar;
                NumberStr[NumberIdx] = 0;
                LCD_Disp_String(NumberStr);
            }
            else
                LCD_Disp_String("Too Long! ");
        }
        else if(CurrKeyChar == 'C'){
            a = 0; b = 0;//两个操作数初始化为0
            CurrKeyChar = '=' ; Last_OP = '0';//初始化当前按键及最近输入的操作符
            NumberStr[0] = '\0';NumberIdx = 0;//消除输入缓冲，缓冲索引归0
            numbers[0] = 0;
            numsTop = 0;
            flags[0] = 0;
            flagsTop = 0;mid = 0;
            i=0;
            LCD_Disp_String(" ");
        }
        else{
            
            for (i = 0; i < NumberIdx; i++) {
                if (isdigit(NumberStr[i]))
                {
                    numbers[numsTop++] = NumberStr[i] - '0';
                    numbers[numsTop] = 0;
                }
                else {
                    if (flagsTop == 0 || (flagsTop != 0 && (flagCompare(NumberStr[i], flags[flagsTop - 1]) == 1)))
                    {
                        flags[flagsTop++] = NumberStr[i];
                        flags[flagsTop] = 0;
                    }
                    else {
                        while (flagsTop!= 0 && (flagCompare(flags[flagsTop - 1], NumberStr[i]) >= 0))
                        {
                            switch (flags[flagsTop-1])
                            {
                            case '+':
                                mid = numbers[numsTop - 1] + numbers[numsTop - 2];
                                numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                                numsTop -= 1;
                                numbers[numsTop - 1] = mid;
                                flags[--flagsTop] = 0;
                                break;
                            case '-':
                                mid = numbers[numsTop - 1] - numbers[numsTop - 2];
                                numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                                numsTop -= 1;
                                numbers[numsTop - 1] = mid;
                                flags[--flagsTop] = 0;
                                break;
                            case '*':
                                mid = numbers[numsTop - 1] * numbers[numsTop - 2];
                                numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                                numsTop -= 1;
                                numbers[numsTop - 1] = mid;
                                flags[--flagsTop] = 0;
                                break;
                            case '/':
                                mid = numbers[numsTop - 2] / numbers[numsTop - 1];
                                numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                                numsTop -= 1;
                                numbers[numsTop - 1] = mid;
                                flags[--flagsTop] = 0;
                                break;
                            }
                        }
                        flags[flagsTop++] = NumberStr[i];

                    }
                }
            }
            
            for (j = flagsTop - 1; j >= 0; j--)
            {
                switch (flags[j])
                {
                case '+':
                    mid = numbers[numsTop - 1] + numbers[numsTop - 2];
                    numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                    numsTop -= 1;
                    numbers[numsTop - 1] = mid;
                    break;
                case '-':
                    mid = numbers[numsTop - 1] - numbers[numsTop - 2];
                    numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                    numsTop -= 1;
                    numbers[numsTop - 1] = mid;
                    break;
                case '*':
                    mid = numbers[numsTop - 1] * numbers[numsTop - 2];
                    numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                    numsTop -= 1;
                    numbers[numsTop - 1] = mid;
                    break;
                case '/':
                    mid = numbers[numsTop - 2] / numbers[numsTop - 1];
                    numbers[numsTop - 1] = numbers[numsTop - 2] = 0;
                    numsTop -= 1;
                    numbers[numsTop - 1] = mid;
                    break;
                }
            }
            mid = numbers[0];
            sprintf(numbers,"%d",(int)mid);
            LCD_Disp_String(numbers);
        }
    }
}	

char flagCompare(char a,char b)
{
    switch(a)
    {
        case '*':
            if(b=='+' || b=='-') return 1;
            else return 0;
        case '/':
            if(b=='+' || b=='-') return 1;
            else return 0;
        default:
            if(b == '*' || b=='/') return -1;
            else return 0;
    }
}