
// ������������ϵͳDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������������ϵͳ.h"
#include "������������ϵͳDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <malloc.h>
#include <stdio.h>
#include<fstream>
#include<stdlib.h>
#include<math.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
struct HaffNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;
};
struct HaffCode
{
	int *bit;
	int start;
	int weight;
	char data;
};
typedef struct
{
	int weight;                  
	int parent, lchild, rchild;    
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;



/*ȫ�ֱ���*/
HuffmanTree HT;//�����������
HuffmanCode HC;//�������������
HaffNode *ht;//�������ڵ�ָ��
HaffCode *hc;//����������ָ��
int *w, *b, i, j, n;//wȨֵ,n��С
char *a;//����ַ�
int flag = 0;//��ʶ
int numb = 0;//����
SYSTEMTIME st;
CString strDate, strTime;
CString getTime() {
	GetLocalTime(&st);
	strTime.Format("%2d:%2d:%2d-->", st.wHour, st.wMinute, st.wSecond);
	return strTime;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// C������������ϵͳDlg �Ի���



C������������ϵͳDlg::C������������ϵͳDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, m_num(0)
	, m_element(_T(""))
	, m_weight(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C������������ϵͳDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_record);
	DDX_Text(pDX, IDC_EDIT2, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_element);
	DDX_Text(pDX, IDC_EDIT4, m_weight);
}

BEGIN_MESSAGE_MAP(C������������ϵͳDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &C������������ϵͳDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C������������ϵͳDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C������������ϵͳDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C������������ϵͳDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &C������������ϵͳDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C������������ϵͳDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C������������ϵͳDlg ��Ϣ�������

BOOL C������������ϵͳDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ʼ��ϵͳ... ...\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("�����ʼ���շ�������,�����ұ������ַ�Ԫ�ش�С,���������\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	/*����������ťΪ������*/
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C������������ϵͳDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť,����Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C������������ϵͳDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C������������ϵͳDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/*ȡ��С*/
int minx(HuffmanTree t, int i)
{
	int j, flag;
	int k = 1000; // ȡkΪ������С�ڵ�ֵ
	for (j = 1;j <= i;j++)
		if (t[j].weight<k&&t[j].parent == 0)
			k = t[j].weight, flag = j;
	t[flag].parent = 1;
	return flag;     //������Сֵλ��
}
void select(HuffmanTree t, int i, int &s1, int &s2)
{
	int j;
	s1 = minx(t, i);//����minx����
	s2 = minx(t, i);
	if (s1>s2)// s1Ϊ��С������ֵ�����С���Ǹ�
	{
		j = s1;
		s1 = s2;
		s2 = j;
	}
}


/*��������*/
void paint(CDC *pDC, int parent, int x, int y, int c, int d)//c��ʾ�ýڵ�Ĳ��,d��ʾ�ýڵ����丸�����ҹ�ϵ
{
	double pi = 3.14;//���ڼ����֧����
	int ix, iy, ix0, iy0;
	float hd1, hd2;
	/*ȷ��hd1 hd2ֵ*/
	if (c % 2 == 0 && d != 4)
	{	
		hd1 = pi / 6;
		hd2 = pi / 3; 
	}
	else 
	{ 
		hd1 = pi / 3;
		hd2 = pi / 6; 
	}
	/*�������Ǻ���ȷ��ƫ����*/
	ix0 = 50 * cos(hd1);
	iy0 = 50 * sin(hd1);
	/*��ݹ����*/
	if (ht[parent].lchild != -1)
	{
		paint(pDC, ht[parent].lchild, x - ix0, y + iy0, c + 1, -1);
	}
	
	pDC->Ellipse(x - 10, y - 10, x + 8, y + 8);//��һ�������ڽ�Բ

	char str[5];
	_itoa(ht[parent].weight, str, 10);//������ת��Ϊ�ַ��� int--->char*
	pDC->TextOut(x - 4, y - 8, str);//��ʾȨֵ��ָ��λ��
	/*d��Ϊ0���*/
	if (d != 0)
	{
		ix = x - 8 * cos(hd2)*d;
		iy = y - 8 * sin(hd2);
		pDC->MoveTo(ix, iy);
		ix = x - 36 * cos(hd2)*d;
		iy = y - 36 * sin(hd2);
		pDC->LineTo(ix, iy);
	}
	/*�ҵݹ����*/
	if (ht[parent].rchild != -1)
		paint(pDC, ht[parent].rchild, x + ix0, y + iy0, c + 1, 1);
}
/*��ͼ���ú���*/
void paint(CDC *pDC)
{
	paint(pDC, 2 * n - 2, 175, 10, 0, 0);
}


/*������Ĺ�����������Ϊ�����������ʽ*/
void Haffman(int w[], int n, HaffNode ht[], HaffCode hc[], char a[])
{
	int i, j, m1, m2, x1, x2;//M1,M2��ʾ��С�ʹ�С,x1 x2��ʾ���Һ���


	/*��ʼ���� �����Ȩֵ��Ϣ*/
	for (i = 0;i<2 * n - 1;i++)
	{
		if (i<n)//��������Ȩֵ
			ht[i].weight = w[i];
		else//��Ч�ڵ㴦��
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].lchild = -1;
		ht[i].rchild = -1;
	}


	/*��ʼ���� ������ַ���Ϣ*/
	for (i = 0;i<n;i++)
		hc[i].data = a[i];


	/*���������Ԫ�ؽ�����������*/

	/*�����СȨֵλ��*/
	for (i = 0;i<n - 1;i++)
	{
		m1 = m2 = 1000;//m1 m2ȡ���޴�ֵ ����Ȩֵ
		x1 = x2 = 0;//����λ��


		/*����ڵ�����С�ڵ�ʹ�С�ڵ� �ֱ���Ȩֵ����m1��m2 λ�ô���x1��x2*/
		for (j = 0;j<n + i;j++)
		{
			if (ht[j].weight<m1&&ht[j].parent == 0)
			{
				m2 = m1;
				x2 = x1;
				m1 = ht[j].weight;
				x1 = j;
			}
			else
				if (ht[j].weight<m2&&ht[j].parent == 0)
				{
					m2 = ht[j].weight;
					x2 = j;
				}
		}

		/*��x1��x2��Ϊ�½ڵ�������ӽڵ�,�½ڵ��ȨֵΪ�����ӽڵ�֮��*/
		ht[x1].parent = n + i;
		ht[x2].parent = n + i;
		ht[n + i].weight = ht[x1].weight + ht[x2].weight;
		ht[n + i].lchild = x1;
		ht[n + i].rchild = x2;

	}



	/*�����������ɹ���������*/

	HaffCode cd;
	cd.bit = new int[n];
	int child, parent;
	/*�����нڵ���б���*/
	for (i = 0;i<n;i++)
	{
		/*��ʼ������������ṹ������*/
		cd.start = n - 1;
		cd.weight = ht[i].weight;
		child = i;
		parent = ht[child].parent;


		/*�����е�Ҷ�ӽڵ���ڵ����ó�0,�ҽڵ����ó�1*/
		while (parent != 0)
		{
			if (ht[parent].lchild == child)
				cd.bit[cd.start] = 0;
			else
				cd.bit[cd.start] = 1;
			cd.start--;
			child = parent;
			parent = ht[child].parent;
		}


		hc[i].bit = new int[n];
		/*���������Ϣ*/
		for (j = cd.start + 1;j<n;j++)
			hc[i].bit[j] = cd.bit[j];
		//����
		hc[i].start = cd.start;
		hc[i].weight = cd.weight;
	}
}


/*BUTTON1: �����ַ�������*/
void C������������ϵͳDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	/*׼������*/
	delete[]w;
	delete[]ht;
	delete[]hc;
	UpdateData(TRUE);

	/*nΪ�����ַ���С,�����ַ���СΪ������������ռ�*/
	n = m_num;
	w= new int[n];
	ht = new HaffNode[2 * n - 1];
	hc = new HaffCode[n];

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("�������ַ����ӦȨֵ,������������\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);//ʹ�����ַ���С��ťʧЧ
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);//�򿪱����ַ���Ȩֵ��ť
}


/*BUTTON2: �����ַ������ӦȨֵ*/
void C������������ϵͳDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	/*a����������ַ�*/
	UpdateData(TRUE);
	int m = 0;
	m = strlen(m_element);
	a = new char[m + 1];
	strcpy(a, m_element);

	/*w�����ַ���Ӧ��Ȩֵ*/
	/*�Ƚ������Ȩֵ�����q��,Ȩֵ�ĳ���Ϊm*/
	UpdateData(TRUE);
	m = strlen(m_weight);
	char *q = new char[m + 1];
	strcpy(q, m_weight);

	/*���տո�Ȩֵ�ֿ�����w��*/
	q[m] = ' ';
	q[m + 1] = ' ';

	for (int i = 0, j = 0;i<m;i++, j++)
	{
		int s = 0;
		while (q[i] != ' ')
		{
			s = 10 * s + q[i] - '0';
			i++;
		}
		w[j] = s;
	}

	Haffman(w, n, ht, hc, a);//�������������

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("�������,�����½�����ʼ����ϵͳ\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	/*���½�����ť��ʾΪ������*/
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
}


/*BUTTON4: �½���*/
void C������������ϵͳDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	/*����������ťΪ����*/
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);

	flag = 1;

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("���ڴ�����������... ...\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("�����ɹ�!�뱣���ļ�\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	/*������ʼ��ֵ*/
	int m, i, s1, s2, start;
	int c, f;
	HuffmanTree p;
	char *cd;

	/*�����ж�*/
	if (n <= 1)
		return;

	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode)); // ����hfm��,malloc() ����������̬�ط����ڴ�ռ�

	/*��ʼ������ֵ*/
	for (p = HT + 1, i = 1;i <= n;++i, ++p, ++w)
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (;i <= m;++i, ++p)
		p->parent = 0;

	/*���շ�����*/
	for (i = n + 1;i <= m;++i)
	{
		select(HT, i - 1, s1, s2);//ѡ�����Сֵ��С���Ϊs1
		HT[s1].parent = HT[s2].parent = i;//s1s2����һ����ͬ�ĸ��ڵ�
		HT[i].lchild = s1;//i��ڵ�����Ϊs1
		HT[i].rchild = s2;//i�ҽڵ�����Ϊs2
		HT[i].weight = HT[s1].weight + HT[s2].weight;//������Ȩֵ
	}

	HC = (HuffmanCode)malloc((n + 1)*sizeof(char*));//����hfm����
	cd = (char*)malloc(n*sizeof(char));
	cd[n - 1] = '\0';

	/*��շ�������*/
	for (i = 1;i <= n;i++)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent;f != 0;c = f, f = HT[f].parent)
			// ��Ҷ�ӵ������������
			if (HT[f].lchild == c)
				cd[--start] = '0';//��֧Ϊ0
			else
				cd[--start] = '1';//��֧Ϊ1
		HC[i] = (char*)malloc((n - start)*sizeof(char));

		strcpy(HC[i], &cd[start]);//���շ����������HC��
	}

	free(cd);//�ͷŶ���Ŀռ�cd

	TCHAR szFilter1[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg1(FALSE, _T("txt"), _T("hfmTree"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter1, this);
	CString strFilePath1;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg1.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť��ѡ����ļ�·����ʾ���༭����   
		strFilePath1 = fileDlg1.GetPathName();
	}

	/*����hfmTree.txt*/
	ofstream fop(strFilePath1);
	fop << "data code" << endl;

	for (int i = 0;i<n;i++)
	{
		fop << a[i] << "    ";
		for (int j = hc[i].start + 1;j<n;j++)
			fop << hc[i].bit[j];
		fop << endl;
		flush(cout);
	}

	ifstream fip(strFilePath1);
	fip.close();


	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ӡ��\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����


	UpdateData(TRUE);
	CWnd *pWnd = GetDlgItem(IDC_PRINTTREE);//��ÿؼ����
	CDC *pDC = pWnd->GetDC();//CDCʵ����һ�������ָ��,pWnd����ֵΪGetDC
	CBrush NewBrush(RGB(0, 255, 0));//������ɫ��ˢ
	CBrush*pOldBrush = pDC->SelectObject(&NewBrush);//pDCָ��ˢ����
	paint(pDC);//��������
	UpdateData(FALSE);


	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ӡ����!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����
}


/*BUTTON5:����*/
void C������������ϵͳDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ѡ����Ҫ�����ļ�!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	TCHAR szFilter2[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg2(TRUE, _T("txt"), _T("tobetran"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter2, this);
	CString strFilePath2;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg2.DoModal())
	{
		// ���������ļ��Ի����ϵġ�ȷ������ť��ѡ����ļ�·����ʾ���༭����   
		strFilePath2 = fileDlg2.GetPathName();
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ѡ������ļ����뱣��λ��!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����
	TCHAR szFilter3[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg3(FALSE, _T("txt"), _T("CodeFile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter3, this);
	CString strFilePath3;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg3.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť��ѡ����ļ�·����ʾ���༭����   
		strFilePath3 = fileDlg3.GetPathName();
	}

	/*���ļ�*/
	FILE *tobetran, *codefile;
	tobetran = fopen(strFilePath2, "rb");
	codefile = fopen(strFilePath3, "wb");

	char *tran;//���tobetran����ַ�
	i = 99;//��ʶλ
	tran = (char*)malloc(100 * sizeof(char)); //Ϊtran����100���ֽ�

	while (i == 99)
	{
		if (fgets(tran, 100, tobetran) == NULL)//tobetran�ļ�Ϊ��,�˳�
		{
			break;
		}
		
		//����ѭ��,�����������
		for (i = 0;*(tran + i) != '\0';i++)
		{
			for (j = 0;j <= n;j++)
			{
				if (*(a + j - 1) == *(tran + i))//�ҵ�Ҫ������ַ��뽨���ĺշ������������Ӧ���ַ����б���
				{
					fputs(HC[j], codefile);//�����ַ��ı���
					if (j>n)//�޷��ҵ����Ӧ�ַ�,�˳�
					{
						break;
					}
				}
			}
		}
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("���빤�����!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	fclose(tobetran);//�ر��ļ�
	fclose(codefile);
	free(tran);
}


/*BUTTON6:����*/
void C������������ϵͳDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ѡ�������ļ�\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����
	TCHAR szFilter2[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg2(TRUE, _T("txt"), _T("CodeFile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter2, this);
	CString strFilePath2;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg2.DoModal())
	{
		// ���������ļ��Ի����ϵġ�ȷ������ť��ѡ����ļ�·����ʾ���༭����   
		strFilePath2 = fileDlg2.GetPathName();
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ѡ�������ļ�����λ��\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	// ���챣���ļ��Ի���   
	TCHAR szFilter3[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	CFileDialog fileDlg3(FALSE, _T("txt"), _T("Textfile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter3, this);
	CString strFilePath3;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg3.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť��ѡ����ļ�·����ʾ���༭����   
		strFilePath3 = fileDlg3.GetPathName();
	}

	//���ļ�
	FILE *codef, *txtfile;
	txtfile = fopen(strFilePath3, "w");
	codef = fopen(strFilePath2, "r");

	char *tbdc, *outext, i2;
	int io = 0, i, m;
	unsigned long length = 10000;

	tbdc = (char*)malloc(length*sizeof(char)); //����ռ�
	fgets(tbdc, length, codef);//���ļ��ṹ��ָ��stream�ж�ȡ����,ÿ�ζ�ȡһ�С�
	outext = (char*)malloc(length*sizeof(char)); //����ռ�
	m = 2 * n - 1;
	//�������,�Ӹ�����  ���ַ���0����1��ȷ�������ӻ��Һ���,ֱ��Ҷ�ӽ��
	for (i = 0;*(tbdc + i) != '\0';i++)  //����ѭ����ʼ����
	{
		i2 = *(tbdc + i);
		if (HT[m].lchild == 0)//�ҵ�Ҷ�ӽ��
		{
			*(outext + io) = *(a + m - 1);//����Ӧ�ַ�����outext
			io++;
			m = 2 * n - 1;
			i--;
		}
		else if (i2 == '0') m = HT[m].lchild;//��֧����
		else if (i2 == '1') m = HT[m].rchild;//��֧����
	}

	*(outext + io) = '\0';//������
	fputs(outext, txtfile);//���������ַ�

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("������:\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	/*��ӡ������*/
	str = outext;
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����
	str.Format(_T("\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����
	
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("�������!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����
	/*�ͷſռ�*/
	free(tbdc);
	free(outext);
	fclose(txtfile);
	fclose(codef);
}


/*BUTTON7:��ӡ����*/
void C������������ϵͳDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ѡ����Ҫ��ӡ�����ļ�!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

	TCHAR szFilter4[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg4(TRUE, _T("txt"), _T("CodeFile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter4, this);
	CString strFilePath4;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg4.DoModal())
	{
		// ���������ļ��Ի����ϵġ�ȷ������ť��ѡ����ļ�·����ʾ���༭����   
		strFilePath4 = fileDlg4.GetPathName();
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // �����һ������µ�����

	str.Format(_T("��ѡ���ӡ�����ļ�����λ��\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // �����һ������µ�����

							   // ���챣���ļ��Ի���   
	TCHAR szFilter5[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	CFileDialog fileDlg5(FALSE, _T("txt"), _T("CodePrin"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter5, this);
	CString strFilePath5;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg5.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť��ѡ����ļ�·����ʾ���༭����   
		strFilePath5 = fileDlg5.GetPathName();
	}
	//���ļ�
	FILE * CodePrin, *CodeFile;
	CodePrin = fopen(strFilePath5, "w");
	CodeFile = fopen(strFilePath4, "r");

	char *work3;
	work3 = (char*)malloc(51 * sizeof(char));//��̬�����ڴ�

	/*ÿ��50����ӡ����*/
	do
	{
		if (fgets(work3, 51, CodeFile) == NULL)//�ļ�Ϊ���˳�
		{
			break;
		}
		fputs(work3, CodePrin);//��work3����codeprint
		/*��ӡ50������*/
		str = work3;
		lastLine = m_record.LineIndex(m_record.GetLineCount());
		m_record.SetSel(lastLine - 1, lastLine - 1, 0);
		m_record.ReplaceSel(str);  // �����һ������µ�����

	} while (strlen(work3) == 50);

	/*�ͷſռ�*/
	free(work3);
	fclose(CodePrin);
	fclose(CodeFile);
}