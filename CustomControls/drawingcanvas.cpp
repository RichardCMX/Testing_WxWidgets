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
    Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);


    addRect(this->FromDIP(100), this->FromDIP(80), this->FromDIP(210), this->FromDIP(140), 0 ,*wxRED, "Primero");
    addRect(this->FromDIP(130), this->FromDIP(110), this->FromDIP(280), this->FromDIP(210), M_PI/3.0, *wxBLUE, "Segundo");
    // wxColor(R,G,B,T)
    addRect(this->FromDIP(110), this->FromDIP(110), this->FromDIP(300), this->FromDIP(120), -M_PI/4.0, wxColor(255,0,255,128), "Tercero");

    this->draggedObj = nullptr;
    this->shouldRotate = false;

}

void DrawingCanvas::addRect(int width, int height, int centerX, int centerY, double angle, wxColor color, const std::string& text)
{
    GraphicObject obj{
        {-width / 2.0, -height / 2.0, static_cast<double>(width), static_cast<double>(height)},
        color,
        text,
        {}};

        obj.transform.Translate(static_cast<double>(centerX), static_cast<double>(centerY));
        obj.transform.Rotate(angle);

        this->objectList.push_back(obj);

        Refresh(); //Refresh Window with the new object
}

//WXUNUSED avoids unused parameters warnings
void DrawingCanvas::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
    wxAutoBufferedPaintDC dc(this); // Avoids rectangle flickering
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc)
        return;

    for (const auto& object : objectList)
    {

        // Uses the aplied transform
        gc->SetTransform(gc->CreateMatrix(object.transform));

        gc->SetBrush(wxBrush(object.color));
        gc->DrawRectangle(object.rect.m_x, object.rect.m_y, object.rect.m_width, object.rect.m_height);

        gc->SetFont(*wxNORMAL_FONT, *wxWHITE);

        double textWidth, textHeight;
        gc->GetTextExtent(object.text, &textWidth, &textHeight); // Obtain text size to center it properly

        gc->DrawText(object.text, object.rect.m_x + object.rect.m_width / 2.0 - textWidth / 2.0, object.rect.m_y + object.rect.m_height / 2.0 - textHeight / 2.0);
    }
    delete gc;
}

// Determine when the pointer is inside the top rectangle

// clickedObjetIter search on the list the top rectangle using the lambda function

// Lambda syntax
// [external param](parameters){code}
void DrawingCanvas::OnMouseDown(wxMouseEvent& event)
{
    auto clickedObjectIter = std::find_if(objectList.rbegin(), objectList.rend(),
        [event](const GraphicObject& o) {
            wxPoint2DDouble clickPos = event.GetPosition();
            auto inv = o.transform;
            inv.Invert();
            clickPos = inv.TransformPoint(clickPos);
            return o.rect.Contains(clickPos);
        });

    //Check if user clicked on the rectangle and bring it to the top
    if (clickedObjectIter != objectList.rend()) {

        auto forwardIt = std::prev(clickedObjectIter.base());

        objectList.push_back(*forwardIt);
        objectList.erase(forwardIt);

        // set dragged obj to the last item on list
        draggedObj = &(*std::prev(objectList.end()));

        // store on mouse move handler
        lastDragOrigin = event.GetPosition();
        shouldRotate = wxGetKeyState(WXK_ALT);

        Refresh();
    }
}

// If should rotate check if its up/down to make clockwise or counterclockwise
void DrawingCanvas::OnMouseMove(wxMouseEvent& event)
{
    if (draggedObj != nullptr) {
        if (shouldRotate) {
            double absoluteYdiff = event.GetPosition().y - lastDragOrigin.m_y;
            draggedObj->transform.Rotate(absoluteYdiff / 100 * M_PI);
        }
        else {
            auto dragVector = event.GetPosition() - lastDragOrigin;
            auto inv = draggedObj->transform;
            inv.Invert();
            dragVector = inv.TransformDistance(dragVector);
            draggedObj->transform.Translate(dragVector.m_x, dragVector.m_y);
        }
        lastDragOrigin = event.GetPosition();
        Refresh();
    }
}

void DrawingCanvas::OnMouseUp(wxMouseEvent& event)
{
    finishDrag();
    finishRotation();
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent& event)
{
    finishDrag();
    finishRotation();
}

void DrawingCanvas::finishDrag()
{
    draggedObj = nullptr;
}

void DrawingCanvas::finishRotation()
{
    shouldRotate = false;
}


