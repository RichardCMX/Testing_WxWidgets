#include "MyApp.hpp"
#include "MainFrame.hpp"

//Macro para implemetar App
wxIMPLEMENT_APP(App);

// Cuerpo de la funcion OnInit() que inicializa la ventana y la muestra
bool App::OnInit() {
	wxInitAllImageHandlers(); // registra todos los handlers, incluido PNG

	// Puntero que guarda direcciones necesarias para el objeto MainFrame
	MainFrame* mainFrame = new MainFrame("C++ GUI");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}