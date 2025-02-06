#ifndef P_H_INCLUDED
#define P_H_INCLUDED

#include <vector>
#include <string>
class P{
public:
    P();
    void SetPomodoro_Button(bool value);
    void SetLong_Break_Button(bool value);
    void SetShort_Break_Button(bool value);

    bool GetPomodoro_Button();
    bool GetLong_Break_Button();
    bool GetShort_Break_Button();

    bool IsTimerRunning();


    void StartTimer();
    void StopTimer();

    void TakeTask(const std::string &value);
    void FinishTask(const std::string &value);
    void ShowCurrentTask();
    void ShowFinishedTasks();
    double GetFtaskTableSize();
    double GetTaskTableSize();
    void ClearAllTasks();

    void ClearCurrentTask(const std::string &value);
    void ShowAllTasks();
    void ClearAllFinishedTasks();
    void ClearCurrentFinishedTask(const std::string &value);





    void AddImageToDialog();
    void AddCheckboxToDialog();



    std::string LastTask;
    std::string GetTaskName();
    std::string GetTaskNameFromTable(int t);


private:
    bool __Pomodoro_Button;
    bool __Short_Break_Button;
    bool __Long_Break_Button;

    bool IsTimeRunning;
    std::vector<std::string> TaskTable;
    std::vector<std::string> FTaskTable;




friend void AddCheckboxToDialog();




};







#endif // P_H_INCLUDED
