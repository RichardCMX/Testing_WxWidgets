#ifndef MAIN_FRAME
#define MAIN_FRAME
#include <wx/wx.h>

// Clase donde se declara la ventana principal a partir de atributos de wxFrame
class MainFrame : public wxFrame {
public:
	//Atributo de ventana con titulo de ventana como parametro
	MainFrame(const wxString& title);
private:
	// Metodo que procesa el uso de un boton
	void OnKeyEvent(wxKeyEvent& evt);


};
#endif // MAIN_FRAME


