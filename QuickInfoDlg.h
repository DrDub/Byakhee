#if !defined(AFX_QUICKINFODLG_H__923EDF23_A664_11D2_A50C_00105A4ACC2C__INCLUDED_)
#define AFX_QUICKINFODLG_H__923EDF23_A664_11D2_A50C_00105A4ACC2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuickInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuickInfoDlg dialog

class CQuickInfoDlg : public CDialog
{
// Construction
public:
	BOOL Show( CString strTipName, CString strTip );
	CQuickInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQuickInfoDlg)
	enum { IDD = IDD_QUICKINFO };
	CStatic	m_wndTextArea;
	CStatic	m_wndIcon;
	BOOL	m_fDontTellMeAgain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuickInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strText;
	CString m_strTipName;

	// Generated message map functions
	//{{AFX_MSG(CQuickInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    //this is redeclared to prevent the caller from displaying the dialog direcly - they must use Show()
    virtual int DoModal() { return CDialog::DoModal(); }

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUICKINFODLG_H__923EDF23_A664_11D2_A50C_00105A4ACC2C__INCLUDED_)
