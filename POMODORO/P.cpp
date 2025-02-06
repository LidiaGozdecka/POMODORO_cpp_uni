#include "P.h"
#include <chrono>
#include <wx/msgdlg.h>
#include<iostream>

#undef _
#define _(s) wxString::FromUTF8(s)

// Konstruktor klasy P inicjalizujący przyciski i stan timera
P::P(): __Pomodoro_Button(true),__Short_Break_Button(false),__Long_Break_Button(false), IsTimeRunning(false){
}

// Funkcje ustawiające wartości dla poszczególnych przycisków
void P::SetPomodoro_Button(bool value){
    __Pomodoro_Button = value;
}
void P::SetShort_Break_Button(bool value){
    __Short_Break_Button = value;
}
void P::SetLong_Break_Button(bool value){
    __Long_Break_Button = value;
}

// Funkcje zwracające wartości przycisków
bool P::GetPomodoro_Button(){
    return __Pomodoro_Button;
}
bool P::GetShort_Break_Button(){
    return __Short_Break_Button;
}
bool P::GetLong_Break_Button(){
    return __Long_Break_Button;
}
bool P::IsTimerRunning(){
    return IsTimeRunning;
}

// Funkcje zarządzające startem i zatrzymaniem timera
void P::StartTimer(){
    IsTimeRunning = true;
}
void P::StopTimer(){
    IsTimeRunning = false;
}

// Dodaje nowe zadanie do listy zadań
void P::TakeTask(const std::string &value){
    TaskTable.push_back(value);
    //wxMessageBox(_("Wyzwanie przyjęte!"), _(" "), wxICON_NONE);
    LastTask = value;
}

// Pobiera nazwę ostatniego zadania
std::string P::GetTaskName(){
    return LastTask;
}

// Pobiera nazwę zadania z tabeli na podstawie indeksu
std::string P::GetTaskNameFromTable(int i){
    return TaskTable.at(i);
}

// Wyświetla aktualne zadanie
void P::ShowCurrentTask(){
    if(TaskTable.empty()){
        LastTask = _( "Brak zadań" );
        wxMessageBox(LastTask, _("Aktualne zadanie"), wxICON_NONE);
    } else {
        wxMessageBox(TaskTable.back(), _("Aktualne zadanie"), wxICON_NONE);
    }
}

// Kończy zadanie i przenosi je do listy ukończonych
void P::FinishTask(const std::string &value){
    if(value.empty()){
        wxMessageBox(_("Brak wartości"), _("Wykonaj zadanie"), wxICON_NONE);
        return;
    }
    if(TaskTable.empty()){
        wxMessageBox(_("Lista zadań jest pusta"), _("Wykonaj zadanie"), wxICON_NONE);
        return;
    }
    auto dt = std::find(TaskTable.begin(), TaskTable.end(), value);
    if(dt == TaskTable.end()){
        wxMessageBox(_("Nie znaleziono zadania"), _("Wykonaj zadanie"), wxICON_NONE);
        return;
    }

    // Przenosi zadanie do listy ukończonych i usuwa je z aktualnych
    FTaskTable.push_back(value);
    ///tutaj
    wxMessageBox(wxString::Format(_("Dodano zadanie: '%s'. Liczba zadań: %d"), value, (int)FTaskTable.size()), "Task(s) Finished");
    TaskTable.erase(dt);
}

// Wyświetla ukończone zadania
void P::ShowFinishedTasks(){
    if(FTaskTable.empty()){
        wxMessageBox(_("Brak ukończonych zadań"), _("Ukończone zadania"), wxICON_NONE);
        return;
    }
    wxString finishedTasks;
    for (const auto& task : FTaskTable){
        finishedTasks += wxString::FromUTF8(task) + "\n";
    }
    wxMessageBox(finishedTasks, _("Ukończone zadania"));
}

// Zwraca liczbę ukończonych i aktualnych zadań
double P::GetFtaskTableSize(){
    return FTaskTable.size();
}
double P::GetTaskTableSize(){
    return TaskTable.size();
}

// Usuwa konkretne zadanie z listy aktualnych
void P::ClearCurrentTask(const std::string &value){
    if(value.empty()){
        wxMessageBox(_("Brak wartości"), _("Usuwanie zadania"), wxICON_NONE);
        return;
    }
    if(TaskTable.empty()){
        wxMessageBox(_("Lista zadań jest pusta. Nie można usunąć zadań"), _("Usuwanie zadania"), wxICON_NONE);
        return;
    }
    auto it = std::find(TaskTable.begin(), TaskTable.end(), value);
    if(it == TaskTable.end()){
        wxMessageBox(wxString::Format(_("Nie odnaleziono zadania '%s'"), value) , _("Usuwanie zadania"), wxICON_NONE);
        return;
    }
    TaskTable.erase(it);
    ///tutaj
    wxMessageBox(wxString::Format(_("Usunięto zadanie '%s'. Liczba pozostałych zadań: %d"), value, (int)TaskTable.size()), "Tasks cleared");
}

// Wyświetla wszystkie aktualne zadania
void P::ShowAllTasks(){
    if(TaskTable.empty()){
        wxMessageBox(_("Nie dodano żadnych zadań"), _("Aktualne zadania"), wxICON_NONE );
        return;
    }
    wxString allTasks;
    for (const auto& task : TaskTable){
        allTasks += wxString::FromUTF8(task) + "\n";
    }
    wxMessageBox(allTasks, _("Aktualne zadania"), wxICON_NONE);
}

// Usuwa wszystkie ukończone zadania
void P::ClearAllFinishedTasks(){
    FTaskTable.clear();
    wxMessageBox(_("Usunięto ukończone zadania."), _("Usuwanie ukończonych zadań"), wxICON_NONE);
}

// Usuwa wszystkie aktualne zadania
void P::ClearAllTasks(){
    TaskTable.clear();
    wxMessageBox(_("Usunięto wszystkie zadania"), _("Usuwanie aktualnych zadań"), wxICON_NONE);
}

// Usuwa konkretne zadanie z listy ukończonych i przenosi je do aktualnych(do ponownego wykonania)
void P::ClearCurrentFinishedTask(const std::string &value){
    if(value.empty()){
        wxMessageBox("Pusta wartość", _(" "), wxICON_NONE);
        return;
    }
    if(FTaskTable.empty()){
        wxMessageBox(_("Lista ukończonych zadań jest pusta. Nie można odznaczyć zadania"), _(" "), wxICON_NONE);
        return;
    }
    auto it = std::find(FTaskTable.begin(), FTaskTable.end(), value);
    if(it == FTaskTable.end()){
        wxMessageBox(wxString::Format(_("Nie odnaleziono zadania '%s'"), value), _(" "), wxICON_NONE);
        return;
    }
    TaskTable.push_back(value);
    FTaskTable.erase(it);
    wxMessageBox((wxString::Format(_("Usunięto zadanie '%s'. Liczba pozostałych zadań: %d"), value, (int)FTaskTable.size()), "zadań odznaczonych"), _(" "), wxICON_NONE);
}
