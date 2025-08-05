#include "drawingcanvas.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>


//wxFULL_REPAINT_ON_RESIZE ensures the native window are created correctly
DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size)
    : wxWindow(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
}

//WXUNUSED avoids unused parameters warnings
void DrawingCanvas::OnPaint(wxPaintEvent& WXUNUSED(evt)) {
    wxAutoBufferedPaintDC dc(this); // Avoids rectangle flickering
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc)
        return;

    // DIP = Density Independent Pixels; aquí la ventana ya existe, así que es seguro.
    wxPoint rectOrigin = FromDIP(wxPoint(189, 200));
    wxSize rectSize = FromDIP(wxSize(100, 80));

    gc->SetBrush(*wxRED_BRUSH);
    gc->DrawRectangle(rectOrigin.x, rectOrigin.y,
        rectSize.GetWidth(), rectSize.GetHeight());
    
    gc->SetFont(*wxNORMAL_FONT, *wxWHITE);
    wxString text = "Texto";

    double textWidth, textHeight;
    gc->GetTextExtent(text, &textWidth, &textHeight); // Obtain text size to center it properly
 
    gc->DrawText(text, rectOrigin.x + rectSize.GetWidth() / 2.0 - textWidth/2.0 , rectOrigin.y + rectSize.GetHeight() / 2.0 - textHeight/ 2.0 );

    delete gc;
}
