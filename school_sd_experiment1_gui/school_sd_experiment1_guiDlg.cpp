
// school_sd_experiment1_guiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "school_sd_experiment1_gui.h"
#include "school_sd_experiment1_guiDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <atlconv.h>

//x^3 -7x^2 +15x -9 = 0;
//1 4	

// forward declare
class Element;

std::vector<std::string> extract_terms(const std::string& equation);
std::vector<Element> parse_terms(const std::vector<std::string>& terms);
std::vector<double> solve_polynomial(const std::vector<Element>& polynomial,
	const std::pair<double, double>& x_range = std::make_pair(0.0, 10.0));

/**
 * @brief 多项式元素结构体 1: 系数 2: 次数
 */
class Element final
{
public:
	int ratio{}, power{};
	std::vector<Element> polynomial{};

	Element() = default;

	[[nodiscard]] double value(const double val) const
	{
		if ((this->ratio) == 0) return 0;
		if (val == 0 && (this->power) != 0) return 0;
		if ((this->power) == 0) return (this->ratio);
		return (this->ratio) * std::pow(val, this->power);
	}

	auto operator<=>(const Element other) const
	{
		return this->power <=> other.power;
	}
	double operator*(const double val) const
	{
		return this->value(val);
	}
	friend double operator*(const double val, const Element element)
	{
		return element.value(val);
	}

	void get_terms(const std::string& equation);
	[[nodiscard]] std::vector<double> solve(const std::pair<double, double>& x_range) const;
};	

void Element::get_terms(const std::string& equation)
{
	auto const terms{ extract_terms(equation) };
	polynomial = parse_terms(terms);
}

std::vector<double> Element::solve(const std::pair<double, double>& x_range) const
{
	return solve_polynomial(polynomial, x_range);
}

/**
 * @brief 提取方程中的各个项
 * @param equation 
 * @return 
 */
std::vector<std::string> extract_terms(const std::string& equation) {

	std::string express{ equation };

	std::transform(express.begin(), express.end(), express.begin(), 
    [](const unsigned char c) { return std::tolower(static_cast<int>(c), std::locale()); });

    std::vector<std::string> terms;
    std::regex const term_regex(R"(\s*([+-]?(\d*\.?\d*)x(\^\d+)?|\s*[+-]?(\d*\.?\d*)x|\s*[+-]?(\d*\.?\d+))\s*)");

    std::sregex_token_iterator it(express.begin(), express.end(), term_regex, 0);
    std::sregex_token_iterator const end;

    while (it != end) {
        terms.push_back(it->str());
        ++it;
    }

    return terms;
}

/**
 * @brief 解析各项元素,提取成统一多项式
 * @param terms 
 * @return 
 */
std::vector<Element> parse_terms(const std::vector<std::string>& terms)
{
	std::vector<Element> polynomial;
	for (const auto& term : terms) {
		Element element;
		if (term.contains('x')) {
			if (auto const pos = term.find('x');
				term.contains('^')) {
				element.power = std::stoi(term.substr(pos + 2));
				if (term[0] == 'x') {
					element.ratio = 1;
				} else {
					element.ratio = std::stoi(term.substr(0, pos));
				}
			} else {
				element.power = 1;
				if (term[0] == 'x') {
					element.ratio = 1;
				} else {
					element.ratio = std::stoi(term.substr(0, pos));
				}
			}
		}
		else {
			element.power = 0;
			element.ratio = std::stoi(term);
		}
		polynomial.push_back(element);
	}

	if (!polynomial.empty()) {
		polynomial.back().ratio = -polynomial.back().ratio;
	}

	return polynomial;
}

/**
 * @brief 根据范围计算出解
 * @param polynomial 
 * @param x_range default {0, 0} 
 * @return 
 */
std::vector<double> solve_polynomial(const std::vector<Element>& polynomial, 
                                     const std::pair<double, double>& x_range)
{
	std::vector<double> solve_stack;
	double result{}, solve{x_range.first};

	while (solve <= x_range.second) {
		for (const auto& ele : polynomial) {
			result += (ele * solve);
		}
		if (result == 0) {
			solve_stack.push_back(solve);
		}
		result = 0;
		solve += 1;
	}

	return solve_stack;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cschoolsdexperiment1guiDlg 对话框



Cschoolsdexperiment1guiDlg::Cschoolsdexperiment1guiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCHOOL_SD_EXPERIMENT1_GUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cschoolsdexperiment1guiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_inputText);
	DDX_Text(pDX, IDC_EDIT2, m_inputRange);
	DDX_Text(pDX, IDC_EDIT3, m_outputText);
}

BEGIN_MESSAGE_MAP(Cschoolsdexperiment1guiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &Cschoolsdexperiment1guiDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &Cschoolsdexperiment1guiDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &Cschoolsdexperiment1guiDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// Cschoolsdexperiment1guiDlg 消息处理程序

BOOL Cschoolsdexperiment1guiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_inputText = TEXT("Input a polynomial. Example: 3X^4+2x^2+3X-4=5");
	m_inputRange = TEXT("Input x range. Example: 2 3 (' ' to separate, Default is [1, 100]");
	UpdateData(FALSE);

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cschoolsdexperiment1guiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cschoolsdexperiment1guiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cschoolsdexperiment1guiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cschoolsdexperiment1guiDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void Cschoolsdexperiment1guiDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int input_equation_length = WideCharToMultiByte(CP_UTF8, 0, m_inputText, -1,
		NULL, 0, NULL, nullptr);
	std::string temp_equation(input_equation_length - 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, m_inputText, -1, &temp_equation[0], 
		input_equation_length, NULL, NULL);

	int input_range_length = WideCharToMultiByte(CP_UTF8, 0, m_inputRange, -1,
		NULL, 0, NULL, nullptr);
	std::string temp_range(input_equation_length - 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, m_inputRange, -1, &temp_range[0], 
		input_equation_length, NULL, NULL);


	std::string equation = "3X^4 +2x^2+3X -4= 5";
	std::pair<double, double> x_range{ 0,100 };

	equation = temp_equation;
	
	if (std::istringstream stream(temp_range);
		stream >> x_range.first >> x_range.second) {
		auto x = std::format("已输入正确范围, Ranges is : [{} {}]", x_range.first, x_range.second);
		m_inputRange = CA2WEX(x.c_str());
	} else {
		m_inputRange = TEXT("未输入正确范围, 范围默认为 [1, 100]");
	}


	if (!equation.contains('x') && !equation.contains('X')) {
		m_inputText = TEXT("Input Error! Try Again!");
		return;
	}

	std::string out_string = std::format("In range : [{} {}]   ", x_range.first, x_range.second);

	std::vector<std::string> const terms = extract_terms(equation);
	std::vector<Element> const polynomial{parse_terms(terms)};
	if (const auto answer{ solve_polynomial(polynomial, x_range) };
		!answer.empty()) {
		out_string += "Answer is : ";
		for (auto val : answer) {
			out_string += std::format("{} ", val);
		}
		out_string += "\n";
	} else {
		out_string += "No Answer";
	}

	m_outputText = CA2WEX(out_string.c_str());

	UpdateData(FALSE);
}

void Cschoolsdexperiment1guiDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
