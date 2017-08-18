#include <wx/thread.h>
#include <wx/log.h>
#include <wx/dir.h>
#include <wx/image.h>
#include <wx/filename.h>
#include <wx/utils.h>
#include "mxApplication.h"
#include "mxSource.h"
#include "ShareManager.h"
#include "Language.h"
#include "mxSingleton.h"
#include "mxBeginnerPanel.h"
#include "mxIconInstaller.h"
#include "MenusAndToolsConfig.h"
#include "ConfigManager.h"
#include "HelpManager.h"
#include "Parser.h"
#include "CodeHelper.h"
#include "ProjectManager.h"
#include "DebugManager.h"
#include "mxMainWindow.h"
#include "mxHelpWindow.h"
#include "mxTipsWindow.h"
#include "mxUtils.h"
#include "mxArt.h"
#include "mxMessageDialog.h"
#include "version.h"
#include "mxUpdatesChecker.h"
#include "mxSizers.h"
#include "mxErrorRecovering.h"
#include "mxSplashScreen.h"
#include "error_recovery.h"
//#include "linStuff.h"
#include "mxAUI.h"
#include "mxNewWizard.h"
#include "EnvVars.h"
using namespace std;



#ifdef _TIMED_INIT
wxLongLong start_time = wxGetLocalTimeMillis();
wxLongLong aux_start_time;
#endif


IMPLEMENT_APP(mxApplication)
	
mxApplication *g_application = nullptr;

bool mxApplication::OnInit() {
	
	if (argc==2 && wxString(argv[1])=="--version") {
		cout<<"ZinjaI "<<VERSION<<endl;
		return false;
	}
	
	if (argc==2 && wxString(argv[1])=="--help") {
		cout << "ZinjaI's command line special arguments:" << endl;
		cout << "   --help:         prints this help text and exit" << endl;
		cout << "   --version:      display installed version and exit" << endl;
		cout << "   --new-source:   shows the wizard for creating a new simple program" << endl;
		cout << "   --new-project:  shows the wizard for creating a new project" << endl;
		cout << "   --last-source:  opens the first file from Recent Files' list" << endl;
		cout << "   --last-project: opens the first file from Recent Projects' list" << endl;
		return false;
	}
	
SHOW_MILLIS("Entering OnInit...");
	
#ifdef _ZINJAI_DEBUG
//	wxLongLong start_time = wxGetLocalTimeMillis();
	wxLog::SetActiveTarget(new wxLogStderr());
#endif
	
	g_application =this;
	srand(time(nullptr));
	
	sizers = new mxSizers();
	
SHOW_MILLIS("About to find out zinjai_dir...");
	
	wxFileName f_path = wxGetCwd(); 
	f_path.MakeAbsolute();
	wxString cmd_path = f_path.GetFullPath();
	wxFileName f_cmd(argv[0]);

	wxFileName f_zpath = f_cmd.GetPathWithSep();
	f_zpath.MakeAbsolute();
	wxString zpath(f_zpath.GetPathWithSep());
	bool flag=false;
	if (f_zpath!=f_path) {
		if ( ( flag = wxFileName::FileExists(DIR_PLUS_FILE(zpath,"zinjai.dir")) ) ) {
			wxSetWorkingDirectory(zpath);
		} else if ( ( flag = wxFileName::FileExists(DIR_PLUS_FILE(zpath,"../zinjai.dir")) ) ) {
			zpath = DIR_PLUS_FILE(zpath,"../");
			wxSetWorkingDirectory(zpath);
#ifdef __APPLE__
		} else if ( ( flag = wxFileName::FileExists(DIR_PLUS_FILE(zpath,"../Resources/zinjai.dir")) ) )  {
			zpath = DIR_PLUS_FILE(zpath,"../Resources");
			wxSetWorkingDirectory(zpath);
#endif
		} else zpath = cmd_path;
	}

	if (!flag && !wxFileName::FileExists("zinjai.dir")) {
 		wxMessageBox("ZinjaI no pudo determinar el directorio donde fue instalado.\n"
			            "Compruebe que el directorio de trabajo actual sea el correcto.\n"
						"ZinjaI cannot determinate installation path. Please verify that\n"
						"working path is the right one.","Error");
	}
	
SHOW_MILLIS("About to load ConfigManager...");
	
	// fix some env vars changed by the launcher and make zinjai's dir public
	EnvVars::Init(zpath);
	
	// inicialize mxUtils and ConfigManager
	bool first_run = ConfigManager::Initialize(zpath);
	
	if (argc==2 && wxString(argv[1])=="--for-gdb") {
		er_uninit();
	}
	
	// cargar archivo de internacionalizacion
	if (first_run || config->Init.version==20160420) SelectLanguage();
	
	// si delega la carga a otra instancia termina inmediatamente
	if (InitSingleton(cmd_path)) return false;

SHOW_MILLIS("Initializing art...");
	
	// init image handlers and show splash screen
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxXPMHandler);
	ShowSplash();
	
	// load art and help files
	mxArt::Initialize();
	
SHOW_MILLIS("Initializing help system...");
	
	// inicialize HelpManager
	HelpManager::Initialize();
	
	// inicialize CodeHelper
	CodeHelper::Initialize();

SHOW_MILLIS("Finishing config manager's initialization...");
	
	// verifica si hay compilador, terminal, etc instalado y configurado...
	// ...y carga el resto de la configuracion (toolchains, colores, atajos, toolbars, etc)
	config->FinishiLoading(); 
	
SHOW_MILLIS("Creating main window...");	
	
	// create main window
	if (config->Init.size_x==0 || config->Init.size_y==0)
		main_window = new mxMainWindow(nullptr, wxID_ANY, "ZinjaI ", wxDefaultPosition, wxSize(800, 600));
	else
		main_window = new mxMainWindow(nullptr, wxID_ANY, "ZinjaI", wxPoint(config->Init.pos_x,config->Init.pos_y), wxSize(config->Init.size_x,config->Init.size_y));

SHOW_MILLIS("Initializing DebugManager...");	
	
	// inicialize debug manager
	DebugManager::Initialize();
	
	// set top window and let the magic do the rest
	SetTopWindow(main_window);

SHOW_MILLIS("Icon installer and tips...");	
	
#if !defined(__WIN32__) && !defined(__APPLE__)
	if (first_run) new mxIconInstaller(true);
#endif
	
	// show startup tip
	if ( (config->Init.show_tip_on_startup && !config->Init.show_welcome) 
#ifndef _ZINJAI_DEBUG
		|| config->Init.version!=VERSION
#endif
	) {
		main_window->Refresh();
		g_tips_window = new mxTipsWindow(main_window, wxID_ANY);
		if (g_splash) g_splash->ShouldClose();
	}
	
SHOW_MILLIS("Loading welcome panel...");	
	
	LoadFilesOrWelcomePanel(cmd_path);
	
SHOW_MILLIS("Welcome panel done...");	
	
	// si estaba abriendo un proyecto el usuario puede haber cerrado la ventana antes de que el parser termine
	if (!main_window) return false;
	
	// puede haber llegado algo para el singleton mientras cargabamos
	if (g_singleton) g_singleton->ProcessToOpenQueue();
	
	// devolver el foco a la ventana de sugerencias si existe, para que se pueda cerrar con Esc
	if (g_tips_window) g_tips_window->Raise();
	
//#ifdef _ZINJAI_DEBUG
//	cerr<<"Initialization complete: "<<wxGetLocalTimeMillis()-start_time<<"ms"<<endl;
//#endif
	
SHOW_MILLIS("Checking for error recovery files...");	
	// recuperarse de un segfault y/o buscar actualizaciones
	if (!mxErrorRecovering::RecoverSomething()) {
		if (config->Init.check_for_updates) 
			mxUpdatesChecker::BackgroundCheck();
	}
	
SHOW_MILLIS("ZinjaI's initialization complete, you're clear to take off!");	
	
	return true;
}

void mxApplication::SelectLanguage ( ) {
	wxDir dir("lang");
	wxString spec="*.pre", filename;
	bool cont = dir.GetFirst(&filename, spec , wxDIR_FILES);
	wxArrayString langs;
	while ( cont ) {
		langs.Add(filename.BeforeLast('.'));
		cont = dir.GetNext(&filename);
	}
	if (langs.Index("spanish")==wxNOT_FOUND) langs.Add("spanish");
	if (langs.GetCount()>1) {
		wxString newlang = wxGetSingleChoice("Select a Language:\nSeleccione el idioma:","ZinjaI",langs);
		if (newlang.Len()) config->Init.language_file=newlang;
	}
}

bool mxApplication::InitSingleton(const wxString &cmd_path) {
	// inicialize singleton manager
	g_singleton = new mxSingleton; // siempre debe existir la instancia...
	if (!config->Init.singleton) return false; // ...aunque no se use
	g_singleton->Start();
	if (g_singleton->IsRunning() || argc==1) return false; // si no hay otra instancia o no hay argumentos
	// intentar cargar todo en la otra instancia
	bool all_done=true, filter_args=true;
	for (int i=1; i<argc;i++) {
		wxString name = argv[i];
		if (filter_args && name.StartsWith("--")) { 
			if (name=="--") filter_args=false; 
			else all_done=false;
			continue; 
		}
		if (name.AfterLast('.').Lower()!=PROJECT_EXT) {
			bool opened = g_singleton->RemoteOpen(DIR_PLUS_FILE(cmd_path,name));
			int ret=0;
			while (!opened && ret<2) { // dos reintentos, por si estaba muy ocupado
				wxMilliSleep(10*rand()%50); // delay aleatorio tip ethernet
				opened = g_singleton->RemoteOpen(DIR_PLUS_FILE(cmd_path,name));
				ret++;
			}
			if (opened) argv[i][0]='\0';
			else all_done=false;
		}
	}
	return all_done;
}

void mxApplication::ShowSplash ( ) {
	bool no_splash=false;
	for (int i=1;i<argc;i++) 
		if (wxString(argv[i])=="--no-splash") {
			argv[i][0]='\0';
			no_splash=true;
		}
	if (!no_splash && wxFileName(DIR_PLUS_FILE("imgs",SPLASH_FILE)).FileExists()) 
		g_splash = new mxSplashScreen(DIR_PLUS_FILE("imgs",SPLASH_FILE));
}

void mxApplication::LoadFilesOrWelcomePanel(const wxString &cmd_path) {
	// load files or create and empty one
	if (argc==1 || (argc==2&&argv[1][0]=='\0')) {
		if (config->Init.show_welcome) {
			main_window->ShowWelcome(true);
		} else {
			if (config->Init.new_file==0) 
				main_window->NewFileFromText("");
			else 
				main_window->NewFileFromTemplate(config->Files.default_template);
			main_window->Refresh();
		} 
		if (g_splash) g_splash->ShouldClose();
	} else {
		main_window->Refresh();
		wxYield();
		if (g_splash) g_splash->ShouldClose();
		for (int i=1; i<argc;i++) {
			wxString argi(argv[i]);
			if (argi=="--new-source" ) {
				mxNewWizard::GetInstance()->RunWizard(_T("templates"));
			} else if (argi==_T("--new-project")) {
				mxNewWizard::GetInstance()->RunWizard(_T("new_project"));
			} else if (argi=="--last-source" && config->Files.last_source[0].Len()) {
				main_window->OpenFileFromGui(wxString(config->Files.last_source[0]));
			} else if (argi=="--last-project" && config->Files.last_project[0].Len()) {
				main_window->OpenFileFromGui(wxString(config->Files.last_project[0]));
//			} else if (wxString(argv[i])==".") {
//				main_window->ShowExplorerTreePanel();
			} else if (!argi.IsEmpty()) {
				main_window->OpenFileFromGui(wxFileName(DIR_PLUS_FILE(cmd_path,argv[i])).GetLongPath());
			}
		}
		if (!project && main_window->notebook_sources->GetPageCount()==0 && config->Init.show_welcome) {
			main_window->ShowWelcome(true);
		}
	}
	
	
	if ( (project || main_window->notebook_sources->GetPageCount()>0) && config->Init.show_beginner_panel && !config->Init.autohide_panels) {
		if (config->Init.show_beginner_panel && !g_beginner_panel) {
			g_beginner_panel = new mxBeginnerPanel(main_window);
			main_window->m_aui->InsertPane(g_beginner_panel, wxAuiPaneInfo().Name("beginner_panel").Caption("Panel de Asistencias").Right().Layer(0).Show(), wxAUI_INSERT_ROW);
			_menu_item(mxID_VIEW_BEGINNER_PANEL)->Check(true);
			main_window->m_aui->Update();
		}
		
	}
}
