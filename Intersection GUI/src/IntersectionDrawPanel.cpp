
#include "IntersectionDrawPanel.h"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include "World.h"
#include <iostream>

BEGIN_EVENT_TABLE(IntersectionDrawPanel, wxPanel)
	EVT_PAINT(IntersectionDrawPanel::PaintEvent)
END_EVENT_TABLE()

IntersectionDrawPanel::IntersectionDrawPanel(wxFrame* parent)
: wxPanel(parent)
{
	
}

void IntersectionDrawPanel::PaintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void IntersectionDrawPanel::PaintNow()
{
	wxClientDC dc(this);
	Render(dc);
}

void IntersectionDrawPanel::Render(wxDC& dc)
{
	
	// Draw the grid
    if(World::get().intersectionLoaded)
    {
        int yDim = (int) World::get().GetIntersection()[0].size();
        if(yDim > 22)
        {
            dc.SetUserScale(22.0/yDim, 22.0/yDim);
        }
        // Clear
        dc.SetBackground(*wxWHITE_BRUSH);
        dc.Clear();
     	DrawIntersectionGrid(dc);
    }
    else{
        // Clear
        dc.SetBackground(*wxWHITE_BRUSH);
        dc.Clear();
    }
    //DrawStats(dc);
}

void IntersectionDrawPanel::DrawCars(wxDC& dc)
{
    auto& intersection = World::get().GetIntersection()[World::get().mMonth];
    for(int y = 0; y < intersection.size(); y++)
    {
        for(int x = 0; x < intersection[0].size(); x++)
        {
            if(intersection[y][x] == '0')
            {
                
                wxPoint points[4];
                points[0] = wxPoint(x*30+10,y*30+10);
                points[1] = wxPoint(x*30+40,y*30+10);
                points[2] = wxPoint(x*30+40,y*30+40);
                points[3] = wxPoint(x*30+10,y*30+40);
                dc.SetBrush(*wxBLACK_BRUSH);
                dc.SetPen(*wxBLACK_PEN);
                dc.DrawPolygon(4,points);
            }
            else if(intersection[y][x] == '.')
            {
                //dc.SetBrush(*wxWHITE_BRUSH);
                //dc.DrawRectangle(x, y, 15, 15);

            }
            else
            {
                int input = static_cast<int>(intersection[y][x]);
                input%=7;
                if(intersection[y][x] == 'A')
                {
                    input = 1;
                }
                DrawCar(dc, x, y, input);
            }
        }
    }
}

void IntersectionDrawPanel::DrawCar(wxDC& dc, int x, int y, int input)
{
    x = x*30 + 10;
    y = y*30 + 10;
    y -= 5; // shift car up a little
    
    // offset for effect so it doesnt look werid when cars passing each other
    y -= World::get().mMonth%2;
    
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawCircle(x + 22, y + 25,3); // front tire
    dc.DrawCircle(x + 9, y + 25,3); // back tire
    
    
    dc.SetBrush(*wxRED_BRUSH);

    switch(input)
    {
        case 1: dc.SetBrush(*wxRED_BRUSH);
            break;
        case 2: dc.SetBrush(*wxBLUE_BRUSH);
            break;
        case 3: dc.SetBrush(*wxYELLOW_BRUSH);
            break;
        case 4: dc.SetBrush(*wxCYAN_BRUSH);
            break;
        case 5: dc.SetBrush(*wxLIGHT_GREY_BRUSH);
            break;
        case 6: dc.SetBrush(*wxGREEN_BRUSH);
            break;
        case 7: dc.SetBrush(*wxRED_BRUSH);
    }
    
    // car
    wxPoint points[9];
    points[0] = wxPoint(x + 26,y + 25); // bottom right
    points[1] = wxPoint(x + 5, y + 25);  // bottom left
    points[2] = wxPoint(x + 5, y + 20);
    points[3] = wxPoint(x + 10, y + 20);
    points[4] = wxPoint(x + 11, y + 15);
    points[5] = wxPoint(x + 17, y + 15);
    points[6] = wxPoint(x + 20, y + 20);
    points[7] = wxPoint(x + 25, y + 20);
    points[8] = wxPoint(x + 26, y + 25);
    

    dc.DrawPolygon(9,points);
}

void IntersectionDrawPanel::DrawIntersectionGrid(wxDC& dc)
{
    int yDim = (int) World::get().GetIntersection()[0].size();
    int xDim = (int) World::get().GetIntersection()[0][0].size();
    
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawRectangle(10, 10, xDim*30, yDim*30);
    for(int i = 40; i < xDim*30; i+=30)
    {
        dc.DrawLine(i,10,i,yDim*30 + 10);
    }
    for(int i = 40; i < yDim*30; i+=30)
    {
        dc.DrawLine(10,i,xDim*30 + 10, i);
    }
    DrawCars(dc);
}
