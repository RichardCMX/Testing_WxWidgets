#ifndef GRAPHIC_OBJECT
#define GRAPHIC_OBJECT

#include <wx/wx.h>

struct GraphicObject {
	wxRect2DDouble rect;
	wxColor color;
	wxString text;
	wxAffineMatrix2D transform;
};
#endif // !GRAPHIC_OBJECT

