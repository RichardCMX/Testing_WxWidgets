#include <wx/wx.h>
#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/gbsizer.h>
#include "bufferedbitmap.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame("Advance Window Test", wxDefaultPosition, wxDefaultSize);
	frame->Show(true);
	return true;
}

/*
wxFrame(parent, id, title, position, size)
nullptr implies top-level window
wxID_ANY implies wxWidgets assigns the ID
*/
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	

	const auto margin = FromDIP(10);
	auto mainSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	this->SetBackgroundColour(panel->GetBackgroundColour());

	/*
	auto sizer = new wxGridSizer(form.size(), 2, margin, margin);
	*/
	/*
	auto sizer = new wxFlexGridSizer(form.size(), 2, margin, margin);
	*/
	auto sizer = new wxGridBagSizer(margin, margin);
	
	auto nameLabel = new wxStaticText(panel, wxID_ANY, "File name:");
	auto kindLabel = new wxStaticText(panel, wxID_ANY, "Kind:");
	auto sizeLabel = new wxStaticText(panel, wxID_ANY, "Size:");
	auto dimensionsLabel = new wxStaticText(panel, wxID_ANY, "Dimensions:");

	auto kindValue = new wxStaticText(panel, wxID_ANY, "PNG");
	auto sizeValue = new wxStaticText(panel, wxID_ANY, "1.2 MB");
	auto dimensionsValue = new wxStaticText(panel, wxID_ANY, "1024x768");

	auto nameText = new wxTextCtrl(panel, wxID_ANY);
	nameText->SetEditable(false);

	auto loadButton = new wxButton(panel, wxID_ANY, "Load...");

	auto nameFormSizer = new wxBoxSizer(wxHORIZONTAL);

	nameFormSizer->Add(nameText, 1, wxEXPAND|wxRIGHT, margin);
	nameFormSizer->Add(loadButton, 0, wxALIGN_CENTER_VERTICAL);

	auto bitmap = new BufferedBitmap(panel, wxID_ANY, wxBitmap(wxSize(1,1)), wxDefaultPosition, FromDIP(wxSize(100, 100)));
	bitmap->SetBackgroundColour(wxColour(0, 0, 0));

	sizer->Add(nameLabel, {0,0}, {1,1}, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	sizer->Add(kindLabel, { 1,0 }, { 1,1 }, wxALIGN_RIGHT);
	sizer->Add(sizeLabel, { 2,0 }, { 1,1 }, wxALIGN_RIGHT);
	sizer->Add(dimensionsLabel, { 3,0 }, { 1,1 }, wxALIGN_RIGHT);

	sizer->Add(kindValue, { 1,1 }, { 1,1 }, wxEXPAND);
	sizer->Add(sizeValue, { 2,1 }, { 1,1 }, wxEXPAND);
	sizer->Add(dimensionsValue, { 3,1 }, { 1,1 }, wxEXPAND);

	sizer->Add(nameFormSizer, { 0,1 }, { 1,3 }, wxEXPAND);
	sizer->Add(bitmap, { 1,2 }, { 3,2 }, wxEXPAND);

	sizer->AddGrowableCol(2);
	sizer->AddGrowableRow(3);
	
	panel->SetSizer(sizer);
	
	mainSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
	this->SetSizerAndFit(mainSizer);
	
	wxInitAllImageHandlers();

	loadButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent &event)
		{
			wxFileDialog openFileDialog(this, "Open Image", "", "","Image files (*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp|All files (*.*)|*.*",wxFD_OPEN | wxFD_FILE_MUST_EXIST);
			
			if (openFileDialog.ShowModal() == wxID_CANCEL)
				return;

			wxString path = openFileDialog.GetPath();
			wxImage image;
			if (!image.LoadFile(path))
			{
				wxMessageBox("Could not load image file '%s'.", path);
				return;
			}
			//set bitmap
			bitmap->SetBitmap(wxBitmap(image));
			nameText->SetValue(path);

			wxFile file(path);

			kindValue->SetLabel(wxFileName(path).GetExt().Upper());
			sizeValue->SetLabel(wxString::Format("%d KB", static_cast<int>(file.Length()/1024)));
			dimensionsValue->SetLabel(wxString::Format("%dx%d", image.GetWidth(), image.GetHeight()));
			this->Layout();
			this->Fit();
		});
		
}