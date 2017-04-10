
#pragma once
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/menu.h>

class IntersectionFrame : public wxFrame
{
public:
	IntersectionFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~IntersectionFrame();
private:
	void OnExit(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnSimStart(wxCommandEvent& event);
    void OnIntersection(wxCommandEvent& event);
    void OnTurnTimer(wxTimerEvent& event);
	
	wxDECLARE_EVENT_TABLE();
private:
	// Panel for drawing
	class IntersectionDrawPanel* mPanel;
	
	// Simulation menu
	wxMenu* mSimMenu;
	
	// Turn timer
	wxTimer* mTurnTimer;
    
	
	bool mIsActive;
};
