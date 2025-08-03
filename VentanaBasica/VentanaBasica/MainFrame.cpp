#include "MainFrame.hpp"
#include <wx/wx.h>


// Recordar que el valor -1 en parametros de size o point indica por defecto
// Instanciacion de la ventana, con un único parametro definido (titulo)

	// En caso de un solo boton, estos son iguales:
	// this->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
	// button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
	// panel->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

	// En este caso (dos o mas botones) this disparara cualquier boton dentro de la ventana
	// this->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

// Los eventos tecla son detectados dependiendo donde se encuentre en la interfaz al momento
	//Evento de presionar tecla SOLO SE DETECTA EN EL PANEL NO EN LOS BOTONES
	//panel->Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyEvent, this);
	//Evento de presionar tecla SOLO SE DETECTA EN EL BOTON1
	//btn1->Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyEvent, this);

// Si se desea detectar estos eventos independientemente del elemento enfocado usar  CHAR_HOOK

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	// Se crea un nuevo panel para la ventana en la interfaz de esta clase
	wxPanel* panel = new wxPanel(this);
	// Se crea un nuevo panel para la ventana en la interfaz de esta clase
	wxButton* btn1= new wxButton(panel, wxID_ANY, "Button 1 ", wxPoint(300, 150), wxSize(200, 100));
	wxButton* btn2 = new wxButton(panel, wxID_ANY, "Button 2 ", wxPoint(300, 350), wxSize(200, 100));
	wxImage image;


	if (!image.LoadFile("Transporte.png", wxBITMAP_TYPE_PNG)) {
		// Handle error: image not found or invalid format
		return;
	}
	wxBitmap bitmap(image);

	//Evento de presionar tecla SOLO SE DETECTA EN EL PANEL NO EN LOS BOTONES
	panel->Bind(wxEVT_CHAR_HOOK, &MainFrame::OnKeyEvent, this);
	btn1->SetBackgroundColour(*wxRED); // Sets the background color to red
	btn2->SetBitmap(bitmap);


	CreateStatusBar();

}

	void MainFrame::OnKeyEvent(wxKeyEvent & evt) {
		wxChar keyChar = evt.GetUnicodeKey();
		// WXK_NONE son caracteres de control (enter, ctrl, etc)
		if (keyChar == WXK_NONE) {
			int keyCode = evt.GetKeyCode();
			wxLogStatus("Evento tecla %d", keyCode);
		}
		else {
			wxLogStatus("Evento tecla %c", keyChar);
		}
	}
