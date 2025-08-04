#ifndef DRAWING_CANVAS
#define DRAWING_CANVAS

#include <wx/wx.h>

class DrawingCanvas : public wxWindow {
public:
	DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size);
	virtual ~DrawingCanvas() = default;
private:
	void OnPaint(wxPaintEvent& evt);
};

#endif // !DRAWING_CANVAS
