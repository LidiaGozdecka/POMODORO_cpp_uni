/***************************************************************
 * Name:      POMODOROMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lidia Gozdecka, Bartłomiej Stola, Igor Młynarczyk ()
 * Created:   2024-12-29
 * Copyright: Lidia Gozdecka, Bartłomiej Stola, Igor Młynarczyk ()
 * License:
 **************************************************************/

#ifndef POMODOROMAIN_H
#define POMODOROMAIN_H
#include<chrono>
#include "P.h"
#include <wx/statbmp.h>
#include <wx/image.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include<fstream>
#include<wx/wx.h>


//(*Headers(POMODORODialog)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/timer.h>
//*)

class POMODORODialog: public wxDialog
{
    public:

        POMODORODialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~POMODORODialog();
        void AddImageToDialog();
        void AddCheckboxToDialog();
        void CountPomodoros();
        void CheckBoxChecked(const std::string& target);
        void CheckBoxUNChecked();
        void cCheckBoxDel(const std::string& target);
        void CheckBoxDel();
        void cCheckBoxUnChecked(const std::string &target);


        int PomodoroCount = 0;





    private:
        std::vector <wxCheckBox*> checkboxes;
        int i=1;

    P p;

    std::chrono::time_point<std::chrono::high_resolution_clock> time_point;


    wxFlexGridSizer* m_sizer;
    wxFlexGridSizer* Aplikacja;


    wxFlexGridSizer* t_sizer;


    wxPanel* m_panel;


        //(*Handlers(POMODORODialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPomodoro_ButtonSelect(wxCommandEvent& event);
        void OnShort_Break_ButtonSelect(wxCommandEvent& event);
        void OnLong_Break_ButtonSelect(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnStartToggle(wxCommandEvent& event);
        void OnAdd_Task_ButtonClick(wxCommandEvent& event);
        void OnWykonaj_ButtonClick(wxCommandEvent& event);
        void OnPodsumowanieClick(wxCommandEvent& event);
        void OnPodsumowanieButtonClick(wxCommandEvent& event);
        void OnSave_session_buttonClick(wxCommandEvent& event);
        void OnRead_session_buttonClick(wxCommandEvent& event);
        void OnWykonaj_ButtonClick1(wxCommandEvent& event);
        //*)

        //(*Identifiers(POMODORODialog)
        static const long ID_RADIOBUTTON1;
        static const long ID_RADIOBUTTON2;
        static const long ID_RADIOBUTTON3;
        static const long ID_STATICTEXT1;
        static const long ID_STATICBITMAP4;
        static const long ID_TOGGLEBUTTON1;
        static const long ID_STATICBITMAP3;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_BUTTON2;
        static const long ID_CHOICE1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON4;
        static const long ID_BUTTON3;
        static const long ID_BUTTON5;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(POMODORODialog)
        wxButton* Add_Task_Button;
        wxButton* PodsumowanieButton;
        wxButton* Read_session_button;
        wxButton* Save_session_button;
        wxButton* Wykonaj_Button;
        wxChoice* Task_Options;
        wxRadioButton* Long_Break_Button;
        wxRadioButton* Pomodoro_Button;
        wxRadioButton* Short_Break_Button;
        wxStaticBitmap* ObrazekLewy;
        wxStaticBitmap* ObrazekPrawy;
        wxStaticText* Czas;
        wxStaticText* Info;
        wxStaticText* NR;
        wxTextCtrl* Add_Task_Text;
        wxTimer Timer1;
        wxToggleButton* Start;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // POMODOROMAIN_H
