#include"clsScreens.h"
#include"clsTasks.h"
#include"../Number Guessing Game/clsValidation.h"
#include <iomanip>
int clsTasks::lastIdRecord = 1;
enum enOptions{opExit=0,opViewTasks,opAddTask,opCompleteTask,opRemoveTask};
class clsStartToDo
{
    private:
        static enOptions getChois()
        {
            int result;
            bool isValid =1 ;
            do 
            {
                system("cls");
                clsScreens::showMain(); 
                if(!isValid)
                    std::cout<<"[System] -> enter valid chois from 0 to 4 \n";
                std::cout<<"Enter chois: ";
                isValid=clsValidation::IsBetween(result,0,4);
            }while(!isValid);
            return (enOptions) result;
        }
        static void showTasksScreen(std::vector<clsTask> tasks)
        {
            if (tasks.empty()) {
                std::cout << "No tasks found." << std::endl;
                return;
            }

            // Print table header
            std::cout << std::string(78, '-') << std::endl;
            std::cout<< "|" << std::left << std::setw(10) << "ID"
                    << " | " << std::setw(50) << "Description"
                    << " | " << std::setw(10) << "Completed" << "|"
                    << std::endl;
            std::cout << std::string(78, '-') << std::endl;

            // Print each task
            for (clsTask& task : tasks) {
                std::cout<< "|" << std::left << std::setw(10) << task.getId()
                        << " | " << std::setw(50) << task.getDescription()
                        << " | " << std::setw(10) << (task.getIsComplete() ? "Yes" : "No") << "|"
                        << std::endl;
            }
            std::cout << std::string(78, '-') << std::endl;
        }
        static void selectOption(enOptions option,clsTasks& tasks)
        {
            system("cls");
            switch (option)
            {
            case enOptions::opAddTask:
                break;
            case enOptions::opCompleteTask:
                break;
            case enOptions::opRemoveTask:
                break;
            case enOptions::opViewTasks:
                showTasksScreen(tasks.getTasks());
                break;
             case enOptions::opExit:
                exit(0);
                break;
            }
            clsScreens::pressEnter();
        }
        static void pStart()
        {
            clsTasks tasks("test.txt");
            do 
            {
                enOptions chois = getChois();
                selectOption(chois,tasks);
            }while(1);
        }
    public:
        static void start()
        {
            pStart();
        }
};