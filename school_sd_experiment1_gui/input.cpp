// input.cpp: 实现文件
//

#include "pch.h"
#include "school_sd_experiment1_gui.h"
#include "afxdialogex.h"
#include "input.h"


// input 对话框

IMPLEMENT_DYNAMIC(input, CDialogEx)

input::input(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHOOL_SD_EXPERIMENT1_GUI_DIALOG, pParent)
{

}

input::~input()
{
}

void input::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(input, CDialogEx)
END_MESSAGE_MAP()


// input 消息处理程序
