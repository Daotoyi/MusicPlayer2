// CPlaySettingsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MusicPlayer2.h"
#include "PlaySettingsDlg.h"
#include "afxdialogex.h"


// CPlaySettingsDlg 对话框

IMPLEMENT_DYNAMIC(CPlaySettingsDlg, CDialogEx)

CPlaySettingsDlg::CPlaySettingsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLAY_SETTING_DIALOG, pParent)
{

}

CPlaySettingsDlg::~CPlaySettingsDlg()
{
}

void CPlaySettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STOP_WHEN_ERROR, m_stop_when_error_check);
	DDX_Control(pDX, IDC_SHOW_TASKBAR_PROGRESS, m_show_taskbar_progress_check);
	DDX_Control(pDX, IDC_OUTPUT_DEVICE_COMBO, m_output_device_combo);
	DDX_Control(pDX, IDC_OUTPUT_DEVICE_INFO_LIST, m_device_info_list);
}

void CPlaySettingsDlg::ShowDeviceInfo()
{
	
	DeviceInfo& device{ theApp.m_output_devices[m_data.device_selected] };
	m_device_info_list.SetItemText(0, 1, device.name.c_str());
	m_device_info_list.SetItemText(1, 1, device.driver.c_str());
	m_data.output_device = device.name;
}


BEGIN_MESSAGE_MAP(CPlaySettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_STOP_WHEN_ERROR, &CPlaySettingsDlg::OnBnClickedStopWhenError)
	ON_BN_CLICKED(IDC_SHOW_TASKBAR_PROGRESS, &CPlaySettingsDlg::OnBnClickedShowTaskbarProgress)
	ON_CBN_SELCHANGE(IDC_OUTPUT_DEVICE_COMBO, &CPlaySettingsDlg::OnCbnSelchangeOutputDeviceCombo)
END_MESSAGE_MAP()


// CPlaySettingsDlg 消息处理程序


BOOL CPlaySettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBackgroundColor(RGB(255, 255, 255));

	//初始化各控件的状态
	m_stop_when_error_check.SetCheck(m_data.stop_when_error);
	m_show_taskbar_progress_check.SetCheck(m_data.show_taskbar_progress);

	for (const auto& device : theApp.m_output_devices)
	{
		m_output_device_combo.AddString(device.name.c_str());
	}
	m_output_device_combo.SetCurSel(m_data.device_selected);

	CRect rect;
	m_device_info_list.GetClientRect(rect);
	int width0, width1;
	width0 = theApp.DPI(100);
	width1 = rect.Width() - width0 - theApp.DPI(20);

	m_device_info_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_device_info_list.InsertColumn(0, _T("项目"), LVCFMT_LEFT, width0);		//插入第1列
	m_device_info_list.InsertColumn(1, _T("值"), LVCFMT_LEFT, width1);		//插入第2列
	m_device_info_list.InsertItem(0, _T("名称"));
	m_device_info_list.InsertItem(1, _T("驱动程序"));
	m_device_info_list.InsertItem(2, _T("状态"));
	ShowDeviceInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPlaySettingsDlg::OnBnClickedStopWhenError()
{
	// TODO: 在此添加控件通知处理程序代码
	m_data.stop_when_error = (m_stop_when_error_check.GetCheck() != 0);
}


void CPlaySettingsDlg::OnBnClickedShowTaskbarProgress()
{
	// TODO: 在此添加控件通知处理程序代码
	m_data.show_taskbar_progress = (m_show_taskbar_progress_check.GetCheck() != 0);
}


void CPlaySettingsDlg::OnCbnSelchangeOutputDeviceCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	m_data.device_selected = m_output_device_combo.GetCurSel();
	ShowDeviceInfo();
}
