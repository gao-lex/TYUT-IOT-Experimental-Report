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
//-----------------------------------------------------------------
// 检查待显示数据是否越界
//-----------------------------------------------------------------
int calc_chkerror(long num) { return labs(num) <= 9999999? OK : ERROR;}
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
        if(isdigit(CurrKeyChar))//如果是数字键
        {
            //缓冲区未满时存入缓冲，索引递增，末尾添加字符串结束标志，刷新Lcd显示
            if(NumberIdx<MAX_DISPLAY_CHAR)
            {
                NumberStr[NumberIdx++]=CurrKeyChar;
                NumberStr[NumberIdx] = '\0';
                LCD_Disp_String(NumberStr);
            }
        }
        else //处理非数字按键(加减乘除、清0)
        {
            //最近尚未输入操作符则当前输入的数字串转换为a操作数
            //否则转换为b操作数
            if(Last_OP=='0') a=atol(NumberStr);
            else b=atol(NumberStr);
            //处理操作符，按下c时全部清零，否则处理加减乘除等于共5个符号
            //遇到"="号时对前面的合法表达式求值，遇到形如"10+8-"这样的表达式
            //最后输入的不是等于也需要对前面的表达式"10*8"求值
           if(CurrKeyChar == 'C')Operator_Process('C');
           else Operator_Process(Last_OP); 
           //消除输入缓冲，缓冲索引归0
           NumberStr[0] = '\0';NumberIdx =0;
           if(CurrKeyChar!='=') Last_OP = CurrKeyChar;
        }
        //完成当前输入数字或非数字处理之后，Last_char变量保存最近输入的字符
        Last_Char = CurrKeyChar;
    }
}	

//-----------------------------------------------------------------
// 根据运算符按键进行运算处理
//-----------------------------------------------------------------
void Operator_Process(char OP)
{ 
    switch(OP)
    {
        case '+':
            if(CurrKeyChar == '=' || isdigit(Last_Char)){
                a+=b;result = calc_chkerror(a);}
            else result = SLEEP;
            break;
        case '-':
            if(CurrKeyChar == '=' || isdigit(Last_Char)){
                a-=b;result = calc_chkerror(a);}
            else result = SLEEP;
            break;
        case '*':
            if(CurrKeyChar == '=' || isdigit(Last_Char)){
                a*=b;result = calc_chkerror(a);}
            else result = SLEEP;
            break;
        case '/':
            if(CurrKeyChar == '=' || isdigit(Last_Char)){
                if(b){a/=b;result = calc_chkerror(a);}}
            else result = SLEEP;
            break;
        case 'C':a = b=0;CurrKeyChar = Last_OP ='0';result = OK;break;
        default: result = SLEEP;
    }

    switch(result)//将合法的长整数结果转换为字符串并输出显示
    {
        case OK:
            sprintf(outputbuffer,"%ld",a);
            LCD_Disp_String(outputbuffer);
            break;
        case SLEEP:break;
        //其余状况显示异常："Exception"
        case ERROR:
        default:
            a=b=0;CurrKeyChar = Last_OP ='0';
            LCD_Disp_String("Exception ");break;
    }
}