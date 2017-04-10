

#pragma once
#include <wx/app.h>

class IntersectionApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	class IntersectionFrame* mFrame;
};
