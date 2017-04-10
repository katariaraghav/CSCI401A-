

#include "IntersectionFrame.h"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <stdlib.h>
#include <time.h>
#include "IntersectionDrawPanel.h"
#include "World.h"
#include <iostream>
#include <fstream>

enum
{
	ID_SImSTART=1000,
	ID_TURN_TIMER,
    ID_INTERSECTION,
};

wxBEGIN_EVENT_TABLE(IntersectionFrame, wxFrame)
	EVT_MENU(wxID_EXIT, IntersectionFrame::OnExit)
	EVT_MENU(ID_SImSTART, IntersectionFrame::OnSimStart)
    EVT_MENU(ID_INTERSECTION, IntersectionFrame::OnIntersection)
	EVT_TIMER(ID_TURN_TIMER, IntersectionFrame::OnTurnTimer)
wxEND_EVENT_TABLE()

IntersectionFrame::IntersectionFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
, mIsActive(false)
{
    World::get().intersectionLoaded = false;
    // Seed rand for later
    srand(static_cast<unsigned int>(time(NULL)));
    
	// File menu
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_NEW);
	menuFile->Append(wxID_EXIT);
	
	// Simulation menu
	mSimMenu = new wxMenu;
	mSimMenu->Append(ID_SImSTART, "Start/stop\tSpace", "Start or stop the simulation");
    mSimMenu->Append(ID_INTERSECTION, "Load Intersection", "Load intersection simulation");

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(mSimMenu, "&Simulation");
	SetMenuBar(menuBar);
	CreateStatusBar();
	
	// Prepare the draw panel and show this frame
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	mPanel = new IntersectionDrawPanel(this);
	sizer->Add(mPanel, 1, wxEXPAND);
	
	SetSizer(sizer);
	SetAutoLayout(true);
	Show(true);
	
	mTurnTimer = new wxTimer(this, ID_TURN_TIMER);
    World::get().mMonth = 0;

}

IntersectionFrame::~IntersectionFrame()
{
	delete mTurnTimer;
}

void IntersectionFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void IntersectionFrame::OnIntersection(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this,_("Load Intersection"),"./intersections","","txt Files|*.txt",wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    
    if(openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }
    
    int time = 0;
    std::ifstream ifile(openFileDialog.GetPath());
    auto& intersection = World::get().GetIntersection();
    intersection.clear();
    
    while(ifile.good())
    {
        intersection.push_back(std::vector<std::vector<char>>());
        std::string line;
        std::getline(ifile,line);
        int row = 0;
        while(line != "" && ifile.good())
        {
            intersection[time].push_back(std::vector<char>());
            for(auto c : line)
            {
                intersection[time][row].push_back(c);
            }
            row++;
            std::getline(ifile,line);
        }
        time++;
    }
    
    for(auto& time : intersection)
    {
        for(auto& row : time)
        {
            for(auto& col : row)
            {
                std::cout << col;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    World::get().intersectionLoaded = true;
    mSimMenu->Enable(ID_SImSTART,true);
    mPanel->PaintNow();
}

void IntersectionFrame::OnSimStart(wxCommandEvent& event)
{
	if (!mIsActive)
	{
		// Add timer to run once per second
		mTurnTimer->Start(1000);
		mIsActive = true;
	}
	else
	{
		mTurnTimer->Stop();
		mIsActive = false;
	}
}

void IntersectionFrame::OnTurnTimer(wxTimerEvent& event)
{
    if(World::get().intersectionLoaded)
    {
        World::get().mMonth %= World::get().GetIntersection().size();
        mPanel->PaintNow();
        World::get().mMonth++;
    }
}
