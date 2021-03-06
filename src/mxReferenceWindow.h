#ifndef MXREFERENCEWINDOW_H
#define MXREFERENCEWINDOW_H
#include "mxGenericHelpWindow.h"
#include <stack>
#include <map>
#include <vector>
#include "Cpp11.h"
using namespace std;

class mxReferenceWindow:public mxGenericHelpWindow {
	
	vector< pair<wxString,wxString> > search_index;
	bool LoadSearchIndex();
	
	wxTreeItemId page_tree_item;
	bool PopulateInitialTree();
	
	vector<pair<wxTreeItemId,wxString> > items_general,items_page;
	
	static mxReferenceWindow *instance;
	mxReferenceWindow(wxString file="");
	wxString current_path;
	wxString current_page;
	
	wxString m_doc_version; ///< version of the cppreference content archive
	
	stack<wxString> history_prev;
	stack<wxString> history_next;
//	bool CurrentPageIsHome() override;
	bool CanPrev() override;
	bool CanNext() override;
	
public:
	static void ShowPage(wxString page="");
	static void ShowAndSearch(const wxString &keyword);
	wxString ProcessHTML(wxString fname, mxReferenceWindow *w=nullptr);
	
	void LoadHelp(wxString file, bool update_history=true);
	
	void OnPrev();
	void OnNext();
	void OnTree(wxTreeItemId item);
	void ShowIndex();
	void OnSearch(wxString value);
	void OnSearch(wxString value, bool update_history);
	bool OnLink(wxString href);
	
	~mxReferenceWindow();
};

#endif

