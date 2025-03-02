
// school_sd_experiment1_guiDlg.h: 头文件
//

#pragma once


// Cschoolsdexperiment1guiDlg 对话框
class Cschoolsdexperiment1guiDlg : public CDialogEx
{
// 构造
public:
	Cschoolsdexperiment1guiDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCHOOL_SD_EXPERIMENT1_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();

private:
	CString m_inputText{};
	CString m_inputRange{};
	CString m_outputText{};
public:
	afx_msg void OnEnChangeEdit2();
};

