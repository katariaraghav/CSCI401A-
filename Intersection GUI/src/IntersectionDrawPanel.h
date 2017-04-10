

#pragma once
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <string>

class IntersectionDrawPanel : public wxPanel
{
 
public:
	IntersectionDrawPanel(wxFrame* parent);
	void PaintNow();
 
protected:
	void PaintEvent(wxPaintEvent & evt);
	void Render(wxDC& dc);
	void DrawGrid(wxDC& dc);
    void DrawIntersectionGrid(wxDC& dc);
    void DrawCars(wxDC& dc);
    void DrawCar(wxDC& dc, int x, int y);
 
	DECLARE_EVENT_TABLE()
	
private:

};

