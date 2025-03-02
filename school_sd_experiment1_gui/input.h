#pragma once
#include "afxdialogex.h"


// input 对话框

class input : public CDialogEx
{
	DECLARE_DYNAMIC(input)

public:
	input(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~input();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHOOL_SD_EXPERIMENT1_GUI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
