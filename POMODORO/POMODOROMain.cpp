/***************************************************************
 * Name:      POMODOROMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lidia Gozdecka, Bartłomiej Stola, Igor Młynarczyk ()
 * Created:   2024-12-29
 * Copyright: Lidia Gozdecka, Bartłomiej Stola, Igor Młynarczyk ()
 * License:
 **************************************************************/




#include "POMODOROMain.h"
#include <wx/msgdlg.h>
#include <chrono>
#include "P.h"
#include <sstream>
#include <vector>
#include <iomanip>
#include <wx/stdpaths.h>
#include <wx/filename.h>

#include <wx/statbmp.h>
#include <wx/image.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>


#include<string>
#include<fstream>




#undef _
#define _(s) wxString::FromUTF8(s)


//(*InternalHeaders(POMODORODialog)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


//(*IdInit(POMODORODialog)
const long POMODORODialog::ID_RADIOBUTTON1 = wxNewId();
const long POMODORODialog::ID_RADIOBUTTON2 = wxNewId();
const long POMODORODialog::ID_RADIOBUTTON3 = wxNewId();
const long POMODORODialog::ID_STATICTEXT1 = wxNewId();
const long POMODORODialog::ID_STATICBITMAP4 = wxNewId();
const long POMODORODialog::ID_TOGGLEBUTTON1 = wxNewId();
const long POMODORODialog::ID_STATICBITMAP3 = wxNewId();
const long POMODORODialog::ID_STATICTEXT2 = wxNewId();
const long POMODORODialog::ID_STATICTEXT3 = wxNewId();
const long POMODORODialog::ID_BUTTON2 = wxNewId();
const long POMODORODialog::ID_CHOICE1 = wxNewId();
const long POMODORODialog::ID_TEXTCTRL1 = wxNewId();
const long POMODORODialog::ID_BUTTON1 = wxNewId();
const long POMODORODialog::ID_BUTTON4 = wxNewId();
const long POMODORODialog::ID_BUTTON3 = wxNewId();
const long POMODORODialog::ID_BUTTON5 = wxNewId();
const long POMODORODialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(POMODORODialog,wxDialog)
    //(*EventTable(POMODORODialog)
    //*)
END_EVENT_TABLE()

POMODORODialog::POMODORODialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(POMODORODialog)
    wxBoxSizer* Info_Box;
    wxBoxSizer* Last_Box;
    wxBoxSizer* Podsumowanie_Box;
    wxBoxSizer* Start_Box;
    wxBoxSizer* Task_Box;
    wxBoxSizer* Tryby;
    wxBoxSizer* Zegar;
    wxFlexGridSizer* Aplikacja;
    wxGridSizer* Okienko_Main;

    Create(parent, wxID_ANY, _("Pomodoro timer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
    Aplikacja = new wxFlexGridSizer(7, 1, 0, 0);
    Aplikacja->AddGrowableCol(0);
    Aplikacja->AddGrowableRow(0);
    Aplikacja->AddGrowableRow(1);
    Aplikacja->AddGrowableRow(2);
    Aplikacja->AddGrowableRow(3);
    Aplikacja->AddGrowableRow(4);
    Aplikacja->AddGrowableRow(5);
    Aplikacja->AddGrowableRow(6);
    Okienko_Main = new wxGridSizer(3, 1, 0, 0);
    Tryby = new wxBoxSizer(wxHORIZONTAL);
    Pomodoro_Button = new wxRadioButton(this, ID_RADIOBUTTON1, _("Pomodoro"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    Tryby->Add(Pomodoro_Button, 1, wxALL|wxEXPAND, 5);
    Short_Break_Button = new wxRadioButton(this, ID_RADIOBUTTON2, _("Krótka przerwa"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    Tryby->Add(Short_Break_Button, 1, wxALL|wxEXPAND, 5);
    Long_Break_Button = new wxRadioButton(this, ID_RADIOBUTTON3, _("Długa przerwa"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
    Tryby->Add(Long_Break_Button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Okienko_Main->Add(Tryby, 1, wxALL|wxEXPAND, 5);
    Zegar = new wxBoxSizer(wxHORIZONTAL);
    Czas = new wxStaticText(this, ID_STATICTEXT1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    Zegar->Add(Czas, 4, wxALL|wxEXPAND, 5);
    Okienko_Main->Add(Zegar, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Start_Box = new wxBoxSizer(wxHORIZONTAL);
    ObrazekLewy = new wxStaticBitmap(this, ID_STATICBITMAP4, wxBitmap(wxImage(_T("obrazki\\work_big.png"))), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP4"));
    Start_Box->Add(ObrazekLewy, 1, wxALL|wxEXPAND, 5);
    Start = new wxToggleButton(this, ID_TOGGLEBUTTON1, _("Start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
    Start_Box->Add(Start, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    ObrazekPrawy = new wxStaticBitmap(this, ID_STATICBITMAP3, wxBitmap(wxImage(_T("obrazki\\work_big.png"))), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP3"));
    Start_Box->Add(ObrazekPrawy, 1, wxALL|wxEXPAND, 5);
    Okienko_Main->Add(Start_Box, 1, wxALL|wxEXPAND, 5);
    Aplikacja->Add(Okienko_Main, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    Info_Box = new wxBoxSizer(wxVERTICAL);
    NR = new wxStaticText(this, ID_STATICTEXT2, _("#0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    Info_Box->Add(NR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Info = new wxStaticText(this, ID_STATICTEXT3, _("Czas skupienia!"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    Info_Box->Add(Info, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Aplikacja->Add(Info_Box, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    Task_Box = new wxBoxSizer(wxHORIZONTAL);
    Wykonaj_Button = new wxButton(this, ID_BUTTON2, _("Wykonaj"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Task_Box->Add(Wykonaj_Button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Task_Options = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Task_Options->Append(_("Zakończ zadanie"));
    Task_Options->Append(_("Pokaż obecne zadanie"));
    Task_Options->Append(_("Pokaż wszystkie zadania"));
    Task_Options->Append(_("Pokaż ukończone zadania"));
    Task_Options->Append(_("Usuń obecne zadanie"));
    Task_Options->Append(_("Usuń wszystkie zadania"));
    Task_Options->Append(_("Usuń wszystkie ukończone zadania"));
    Task_Box->Add(Task_Options, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Aplikacja->Add(Task_Box, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    Last_Box = new wxBoxSizer(wxHORIZONTAL);
    Add_Task_Text = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Last_Box->Add(Add_Task_Text, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Add_Task_Button = new wxButton(this, ID_BUTTON1, _("Dodaj zadanie"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Last_Box->Add(Add_Task_Button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Aplikacja->Add(Last_Box, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    Podsumowanie_Box = new wxBoxSizer(wxHORIZONTAL);
    Read_session_button = new wxButton(this, ID_BUTTON4, _("Wczytaj poprzednią sesję"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Podsumowanie_Box->Add(Read_session_button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PodsumowanieButton = new wxButton(this, ID_BUTTON3, _("Wygeneruj podsumowanie"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Podsumowanie_Box->Add(PodsumowanieButton, 1, wxALL|wxEXPAND, 5);
    Save_session_button = new wxButton(this, ID_BUTTON5, _("Zapisz bieżącą sesję"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Podsumowanie_Box->Add(Save_session_button, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Aplikacja->Add(Podsumowanie_Box, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    SetSizer(Aplikacja);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(1, false);
    Aplikacja->Fit(this);
    Aplikacja->SetSizeHints(this);

    Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&POMODORODialog::OnPomodoro_ButtonSelect);
    Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&POMODORODialog::OnShort_Break_ButtonSelect);
    Connect(ID_RADIOBUTTON3,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&POMODORODialog::OnLong_Break_ButtonSelect);
    Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&POMODORODialog::OnStartToggle);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&POMODORODialog::OnWykonaj_ButtonClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&POMODORODialog::OnAdd_Task_ButtonClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&POMODORODialog::OnRead_session_buttonClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&POMODORODialog::OnPodsumowanieButtonClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&POMODORODialog::OnSave_session_buttonClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&POMODORODialog::OnTimer1Trigger);
    //*)

    SetIcon(wxICON(aaaa));



    time_point = std:: chrono::high_resolution_clock::now();


    //Dynamicznie przydzielane miejsce na obrazki
    t_sizer = new wxFlexGridSizer(3, 5, 5);

    t_sizer -> Layout();
    Layout();

    Aplikacja->Add(t_sizer, 0, wxEXPAND | wxALL, 5);
    SetSizer(Aplikacja);
    Aplikacja->Fit(this);
    Aplikacja->SetSizeHints(this);



    //Dynamicznie przydzielane miejsce na zadania
    m_sizer = new wxFlexGridSizer(6, 5, 5);

    //m_sizer = FlexGridSizer1;

    m_sizer -> Layout();
    Layout();

    m_sizer->SetFlexibleDirection(wxHORIZONTAL);




    //Dodaje siatkę z obrazkami pomidorkow do ostatniego wiersza mojej glównej siatki
    Aplikacja->Add(m_sizer, 0, wxEXPAND | wxALL, 5);
    SetSizer(Aplikacja);
    Aplikacja->Fit(this);
    Aplikacja->SetSizeHints(this);




    //tworzenie custom koloru
    wxColour zielony(186, 209, 182);




    //zmiana kolorow tła i przyciskow
   SetBackgroundColour(wxColour(244, 137, 128));

   Start->SetBackgroundColour(zielony);
   Add_Task_Button->SetBackgroundColour(zielony);
   PodsumowanieButton->SetBackgroundColour(zielony);
   Wykonaj_Button->SetBackgroundColour(zielony);
   Save_session_button->SetBackgroundColour(zielony);
   Read_session_button->SetBackgroundColour(zielony);
   Task_Options->SetBackgroundColour(zielony);
   Task_Options -> Refresh();

   Layout();
}

POMODORODialog::~POMODORODialog()
{
    //(*Destroy(POMODORODialog)
    //*)
}

void POMODORODialog::OnQuit(wxCommandEvent& event)
{
    Close();
}
//funkcja szukajaca sciezek do plikow graficznych zawartych w projekcie
wxString GetImagePath(const wxString& filename) {
    wxString path = wxStandardPaths::Get().GetExecutablePath();
    path = wxFileName(path).GetPath();  // Pobiera katalog, w którym znajduje się plik wykonywalny

    wxFileName fullPath(path, "obrazki"); // Katalog "obrazki" obok .exe
    fullPath.SetFullName(filename); // Dodajemy nazwę pliku




    return fullPath.GetFullPath();
}


//funkcja zmieniajaca aktualny cykl na sesje pomodoro
void POMODORODialog::OnPomodoro_ButtonSelect(wxCommandEvent& event)
{
    bool value=Pomodoro_Button->GetValue();
    p.SetPomodoro_Button(value);
    p.SetShort_Break_Button(false);
    p.SetLong_Break_Button(false);
    Info->SetLabel(_("Czas na skupienie!!"));

    // Zmiana obrazków
    wxBitmap workImage(wxImage("obrazki/work_big.png"));
    ObrazekLewy->SetBitmap(workImage);
    ObrazekPrawy->SetBitmap(workImage);
}

//funkcja zmieniająca aktualny cykl na krótką przerwę
void POMODORODialog::OnShort_Break_ButtonSelect(wxCommandEvent& event)
{
     bool value=Short_Break_Button->GetValue();
    p.SetShort_Break_Button(value);
    p.SetPomodoro_Button(false);
    p.SetLong_Break_Button(false);
    Info->SetLabel(_("Czas na przerwę!"));

    //Zmiana obrazka na herbatkę
    wxBitmap breakImage(wxImage("obrazki/tea_big.png"));
    ObrazekLewy->SetBitmap(breakImage);
    ObrazekPrawy->SetBitmap(breakImage);

}

//funkcja zmieniajaca aktualny cykl na długa przerwę
void POMODORODialog::OnLong_Break_ButtonSelect(wxCommandEvent& event)
{
     bool value=Long_Break_Button->GetValue();
    p.SetLong_Break_Button(value);
    p.SetShort_Break_Button(false);
    p.SetPomodoro_Button(false);
    Info->SetLabel(_("Czas na dłuższą przerwę!"));


    wxBitmap sleepImage(wxImage("obrazki/sl_big.png"));
    ObrazekLewy->SetBitmap(sleepImage);
    ObrazekPrawy->SetBitmap(sleepImage);


}

//obsługa timera i cykli
void POMODORODialog::OnTimer1Trigger(wxTimerEvent& event)
{
    auto tp = std::chrono::high_resolution_clock::now();
    auto czas = std::chrono::duration_cast<std::chrono::seconds>(tp - time_point).count();

    //Ile minut zostało
    wxString t = wxString::Format("%6.1f", static_cast<double>(czas)*300);

    //  Czy aktywna jest sesja Pomodoro
    if (p.IsTimerRunning() && p.GetPomodoro_Button() && !p.GetShort_Break_Button() && !p.GetLong_Break_Button())
    {
        double tDouble;
        if (t.ToDouble(&tDouble)) {

            double wynik = 25.00 - tDouble / 60.0;

            int cmin = std::floor(wynik);
            double cd = wynik - cmin;
            double sekundy = cd * 60;

            std::ostringstream kwynik;
            kwynik << cmin << ":" << std::setw(2) << std::setfill('0') << static_cast<int>(sekundy);
            std::string wynik1 = kwynik.str();

            Czas->SetLabel(wynik1);

            if (wynik <= 0) {
                p.StopTimer();
                wxMessageBox(_("Pora na przerwę!"), ("Kontroler"), wxICON_NONE); ///zmieniony wygląd LG 01.02.2025
                AddImageToDialog();
                CountPomodoros();
                i++;
                ///BS cykle
                if(i%2==0){
                p.SetPomodoro_Button(false);
                p.SetShort_Break_Button(true);
                p.SetLong_Break_Button(false);

    wxBitmap breakImage(wxImage("obrazki/tea_big.png"));
    ObrazekLewy->SetBitmap(breakImage);
    ObrazekPrawy->SetBitmap(breakImage);
    Pomodoro_Button->SetValue(false);
    Short_Break_Button->SetValue(true);
    Long_Break_Button->SetValue(false);
    Info->SetLabel(_("Pora złapać oddech!"));

    time_point = std:: chrono::high_resolution_clock::now();
    p.StartTimer();}

             else if(i%2!=0){
                p.SetPomodoro_Button(false);
                p.SetShort_Break_Button(false);
                p.SetLong_Break_Button(true);

    wxBitmap breakImage(wxImage("obrazki/sl_big.png"));
    ObrazekLewy->SetBitmap(breakImage);
    ObrazekPrawy->SetBitmap(breakImage);
    Pomodoro_Button->SetValue(false);
    Short_Break_Button->SetValue(false);
    Long_Break_Button->SetValue(true);
    Info->SetLabel(_("Pora na dłuższy odpoczynek!"));

    time_point = std:: chrono::high_resolution_clock::now();
    p.StartTimer();
             }






            }
        }
    }
    // Czy aktywna jest krótka przerwa
    else if (p.IsTimerRunning() && !p.GetPomodoro_Button() && p.GetShort_Break_Button() && !p.GetLong_Break_Button())
    {
        double tDouble;
        if (t.ToDouble(&tDouble)) {
            // Czas początkowy ustawiony na 5 minut
            double wynik = 5.00 - tDouble / 60.0;

            int cmin = std::floor(wynik);
            double cd = wynik - cmin;
            double sekundy = cd * 60;

            std::ostringstream kwynik;
            kwynik << cmin << ":" << std::setw(2) << std::setfill('0') << static_cast<int>(sekundy);
            std::string wynik1 = kwynik.str();

            Czas->SetLabel(wynik1);

            if (wynik <= 0) {
                p.StopTimer();
                wxMessageBox(_("Koniec przerwy!"), ("Kontroler"), wxICON_NONE);

                p.SetPomodoro_Button(true);
                p.SetShort_Break_Button(false);
                p.SetLong_Break_Button(false);

    wxBitmap breakImage(wxImage("obrazki/work_big.png"));
    ObrazekLewy->SetBitmap(breakImage);
    ObrazekPrawy->SetBitmap(breakImage);
    Pomodoro_Button->SetValue(true);
    Short_Break_Button->SetValue(false);
    Long_Break_Button->SetValue(false);
    Info->SetLabel(_("Czas się skupić!"));

    time_point = std:: chrono::high_resolution_clock::now();
    p.StartTimer();


            }
        }
    }
    // Czy aktywna jest długa przerwa
    else if (p.IsTimerRunning() && !p.GetPomodoro_Button() && !p.GetShort_Break_Button() && p.GetLong_Break_Button())
    {
        double tDouble;
        if (t.ToDouble(&tDouble)) {
            // Czas początkowy ustawiony na 15 minut
            double wynik = 15.00 - tDouble / 60.0;

            int cmin = std::floor(wynik);
            double cd = wynik - cmin;
            double sekundy = cd * 60;

            std::ostringstream kwynik;
            kwynik << cmin << ":" << std::setw(2) << std::setfill('0') << static_cast<int>(sekundy);
            std::string wynik1 = kwynik.str();

            Czas->SetLabel(wynik1);

            if (wynik <= 0) {
                p.StopTimer();
                wxMessageBox(_("Koniec przerwy, czas na naukę"), ("Kontroler"), wxICON_NONE); ///zm wyglądu LG 01.02.2025

                p.SetPomodoro_Button(true);
                p.SetShort_Break_Button(false);
                p.SetLong_Break_Button(false);

    wxBitmap breakImage(wxImage("obrazki/work_big.png"));
    ObrazekLewy->SetBitmap(breakImage);
    ObrazekPrawy->SetBitmap(breakImage);
    Pomodoro_Button->SetValue(true);
    Short_Break_Button->SetValue(false);
    Long_Break_Button->SetValue(false);
    Info->SetLabel(_("Czas się skupić!"));

    time_point = std:: chrono::high_resolution_clock::now();
    p.StartTimer();




            }
        }
    }
    // Timer nie uruchomiony i włączone pomodoro
    else if (!p.IsTimerRunning() && p.GetPomodoro_Button() && !p.GetShort_Break_Button() && !p.GetLong_Break_Button())
    {
        // Ustawienie początkowego czasu na 25 minut
        double wynik = 25.00;
        Czas->SetLabel(wxString::Format("%6.1f", wynik));
    }
    // Timer nie jest uruchomiony i włączona krótka przerwa
    else if (!p.IsTimerRunning() && !p.GetPomodoro_Button() && p.GetShort_Break_Button() && !p.GetLong_Break_Button())
    {
        // Ustawienie początkowego czasu na 5 minut
        double wynik = 5.00;
        Czas->SetLabel(wxString::Format("%6.1f", wynik));
    }
    // Timer nieuruhomiony i długa przerwa
    else if (!p.IsTimerRunning() && !p.GetPomodoro_Button() && !p.GetShort_Break_Button() && p.GetLong_Break_Button())
    {
        // Ustawienie początkowego czasu na 15 minut
        double wynik = 15.00;
        Czas->SetLabel(wxString::Format("%6.1f", wynik));
    }
}



//funkcja startująca timer
void POMODORODialog::OnStartToggle(wxCommandEvent& event)
{
   if(!p.IsTimerRunning()){
    time_point = std:: chrono::high_resolution_clock::now();
    p.StartTimer();
    Start->SetLabel("Stop");
   }
   else{
    p.StopTimer();
     time_point = std:: chrono::high_resolution_clock::now();
     Czas->SetLabel(wxString::Format("%6.1f", 1.1));
     Start->SetLabel("Start");
   }


}


//funkcja dodajaca nowe zadanie
void POMODORODialog::OnAdd_Task_ButtonClick(wxCommandEvent& event)
{


    //odczytywanie wpisanego przez uzytkownika zadania
    std::string value = Add_Task_Text->GetValue().ToStdString();
    if (value.empty()) {
        wxMessageBox(_("Nie można dodać pustego zadania"), "Error", wxOK | wxICON_ERROR);
        return;
    }


    //tworzenie zadania
    p.TakeTask(value);

    //dodawanie checkboxa
    AddCheckboxToDialog();





    // Zwiększa okno
    int currentHeight = this->GetSize().GetHeight();
    this->SetSize(this->GetSize().GetWidth(), currentHeight + 30); // Dodajemy 30 bo tyle mniej więcej pikseli zajmie dodane zadanie

    // Odświeża układ
    this->Layout();
    this->Fit();
}

//funkcja wykonujaca odpowiednio wybrana opcje z okna wxChoice
void POMODORODialog::OnWykonaj_ButtonClick(wxCommandEvent& event)
{


    wxString Selected=Task_Options->GetStringSelection();
    if(Selected==_("Pokaż obecne zadanie")){
        p.ShowCurrentTask();
    }
    else if(Selected==_("Zakończ zadanie")){


    wxString selString = Add_Task_Text->GetValue();





    std::string value = selString.ToStdString();


    p.FinishTask(value);
    double value1=p.GetFtaskTableSize();
   std::ostringstream oss;
oss << std::fixed << std::setprecision(0) << value1;
std::string value2 = oss.str();
NR->SetLabel(value2);

CheckBoxChecked(value);

    }

    else if(Selected==_("Pokaż ukończone zadania")){
        p.ShowFinishedTasks();

    }

    else if(Selected==_("Usuń obecne zadanie")){

        wxString selString = Add_Task_Text->GetValue();



        std::string value = selString.ToStdString();
        p.ClearCurrentTask(value);
        cCheckBoxDel(value);
    }

    else if(Selected==_("Usuń wszystkie ukończone zadania")){
        p.ClearAllFinishedTasks();
          NR->SetLabel("0");
          CheckBoxUNChecked();
    }

    else if(Selected==_("Pokaż wszystkie zadania")){
        p.ShowAllTasks();
    }
    else if(Selected==_("Usuń wszystkie zadania")){
        p.ClearAllTasks();
        CheckBoxDel();
    }

    // Do odznaczania obecnego zadania
    else if(Selected==_("Usuń obecnie ukończone zadanie"))
    {
        wxString selString = Add_Task_Text->GetValue();
        std::string value = selString.ToStdString();
        p.ClearCurrentFinishedTask(value);
        cCheckBoxUnChecked(value);
    }


}

//funkcja dodajaca obrazek na dole okna po kazdej ukonczonej sesji
void POMODORODialog::AddImageToDialog(){


    wxImage img("obrazki/pomidorek.png", wxBITMAP_TYPE_PNG);



    if(!img.IsOk()){
        wxLogError("Failed to load pomidorek.png");
        return;
    }else{
    }

    //Konwersja pomidorka na bitmape
    wxBitmap bitmap(img);

    //Tutaj tworzona jest  kontrolka wxStaticBitmap która wyswietla obrazek
    wxStaticBitmap* newImage = new wxStaticBitmap(this, wxID_ANY, bitmap);

    m_sizer->Add(newImage, 0, wxALL | wxALIGN_CENTER, 5);

   // Zwiększa okno
    if((PomodoroCount%6)==0){
    int currentHeight = this->GetSize().GetHeight();
    this->SetSize(this->GetSize().GetWidth(), currentHeight + 70);
    }
    // odświeża układ

    m_sizer->Layout();
    Layout();
    Fit();
}

//funkcja dodajaca chechbox z nazwa nowo dodanego zadania
void POMODORODialog::AddCheckboxToDialog(){


    wxCheckBox* newCheckBox = new wxCheckBox(this, wxID_ANY, "New Checkbox");
    std::string napis = p.GetTaskName();
    newCheckBox->SetLabel(napis);

    newCheckBox->Disable();
    checkboxes.push_back(newCheckBox);


   t_sizer->Add(newCheckBox, 0, wxALL | wxALIGN_LEFT, 5);


   t_sizer->Layout();
   Layout();


}
//Zaznacza checkboxy
void POMODORODialog::CheckBoxChecked(const std::string& target)
{



    for (wxCheckBox* checkbox : checkboxes) {

        std::string value = checkbox->GetLabel().ToStdString();

        if (value == target) {

            checkbox->SetValue(true);

        }
    }



}
// Odznacza checkboxy
void POMODORODialog::CheckBoxUNChecked()
{
    for(wxCheckBox* checkbox: checkboxes)
    {
        checkbox->SetValue(false);
    }
}
// Usuwa aktualnego checkboxa
void POMODORODialog::cCheckBoxDel(const std::string& target)
{


 for (auto it = checkboxes.begin(); it != checkboxes.end(); ) {
    wxCheckBox* checkbox = *it;
    std::string value = checkbox->GetLabel().ToStdString();
    if (value == target) {
        checkbox->Destroy();  // Zwalnia zasoby GUI
        it = checkboxes.erase(it);  // Usuwa wskaźnik z kontenera
    } else {
        ++it;
    }
}



}

// Usuwa wszystkie niezaznaczone zadania
void POMODORODialog::CheckBoxDel()
{


    for (auto it = checkboxes.begin(); it != checkboxes.end(); )
    {
        wxCheckBox* checkbox = *it;
        bool value = checkbox->GetValue();

        if (value == false)
        {
            checkbox->Destroy();
            it = checkboxes.erase(it);
        }
        else
        {
            ++it;
        }
    }



}

//funkcja odznaczajaca okreslony checkbox
void POMODORODialog::cCheckBoxUnChecked(const std::string &target)
{
      for (wxCheckBox* checkbox : checkboxes) {

        std::string value = checkbox->GetLabel().ToStdString();

        if (value == target) {

            checkbox->SetValue(false);

        }
    }
}


//funkcja liczaca kolejne sesje pomodoro (po wywolaniu zwieksza licznik)
void POMODORODialog::CountPomodoros(){
    PomodoroCount++;

}


void POMODORODialog::OnPodsumowanieButtonClick(wxCommandEvent& event)
{




    //zliczanie ukonczonych sesji pomodoro
    std::string komunikat1;
    std::ostringstream oss;
    komunikat1 = _("Liczba ukończonych pomodoro: ");
    oss<<std::fixed<<PomodoroCount;
    std::string PomCount;
    PomCount = oss.str();
    komunikat1 = komunikat1 +  PomCount + " ";

    std::string komunikat2;
    std::ostringstream oss2;

    //zliczanie ukonczonych zadan
    oss2<<p.GetFtaskTableSize();
    std::string TableSize;
    TableSize = oss2.str();
    std::cout << "ftablesize to: "<<TableSize<< " .";
    komunikat2 = _("\n Liczba ukończonych zadań: ") + TableSize + " ";


    std::string komunikat3;
    std::ostringstream oss3;

    oss3<<std::fixed<<std::setprecision(0)<<PomodoroCount *25;
    std::string Minuty;
    Minuty = oss3.str();
    komunikat3 = _("\n Poświęciłaś(-eś) ") + Minuty + _(" minut na pracę. Nieźle!");


    std::string komunikat4;
    std::ostringstream oss4;
    oss4<<std::fixed<<std::setprecision(0)<<ceil((PomodoroCount * 25)/p.GetFtaskTableSize());
    std::string Srednia;
    Srednia = oss4.str();

    komunikat4 =  _("\n Na jedno zadanie średnio potrzebujesz ")+ Srednia + _(" minut. Co za tempo!");

    std::string komunikat;
    komunikat = komunikat1 + komunikat2 + komunikat3+ komunikat4;




    //wyswietlanie podsumowania
    std::cout <<"Zakonczono generowanie podsumowania"<<std::endl;
    wxMessageBox(komunikat, ("Podsumowanie"), wxICON_NONE);

}


// Ta funkcja zapisuje nieukończone zadania, aby potem móc je wywołać w następnej sesji
void POMODORODialog::OnSave_session_buttonClick(wxCommandEvent& event)
{

    double dl = p.GetTaskTableSize();

    std::string npliku = getenv("APPDATA");

    npliku = npliku + "/pomodoro_sesja.txt";
    std::ofstream outFile(npliku);


    //sprawdzanie, czy plik zostal prawidlowo stworzony i otwarty
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file pomodoro_sesja.txt for writing!" << std::endl;
        return;
    }



    //zapis ilosci nieukonczonych zadan
    outFile << dl << " \n";

    //wczytywanie i zapisywanie do pliku kolejnych nieukonczonych zadan
    for(int i = 0; i < dl; i++){

        std::string task = p.GetTaskNameFromTable(i);
        std::cout << task;
        outFile<<task;
        outFile << "\n";
    }
    outFile.close();

    wxMessageBox(_("Bieżąca sesja została zapisana."), ("Zapisywanie sesji"), wxICON_NONE);


}



//funkcja wczytujaca zapisana sesje tj nieukonczone uprzednio zadania
void POMODORODialog::OnRead_session_buttonClick(wxCommandEvent& event)
{

    std::ifstream saved_file;

    //sciezka dostepu do pliku
    std::string npliku = getenv("APPDATA");

    npliku = npliku + "/pomodoro_sesja.txt";

    saved_file.open(npliku);



    if (!saved_file.is_open()) {
        std::cerr << "Failed to open pomodoro_sesja.txt file for reading!" << std::endl;
        return;
    }

    //odczyt liczby zadan do wgrania
    std::string ile_taskow_zostalo_s;
    std::getline(saved_file, ile_taskow_zostalo_s);
    double ile_taskow_zostalo = std::stod(ile_taskow_zostalo_s);


    //odczytywanie i dodawanie kolejnych zadan z pliku
    for(int i=0; i<ile_taskow_zostalo; i++){

        std::string line;
        std::getline(saved_file, line);
        p.TakeTask(line);
        std::cout<<"dorzucam kolejny task z wczytanego pliku";
        std::cout << "nazywa sie: " << line;
        AddCheckboxToDialog();
        Layout();
        Fit();
    }



    //std::string line;

    saved_file.close();

    //odswiezanie okna (zeby dodane zadania odpowiednio się układały)
    t_sizer->Layout();
    Layout();

}





