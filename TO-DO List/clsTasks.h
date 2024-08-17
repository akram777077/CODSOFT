#include "clsTask.h"
#include <vector>
#include <fstream>
#include <string>

class clsTasks {
private:
    std::vector<clsTask> tasks;
    std::string fileName;
    bool loadFromFile();
public:
    static int lastIdRecord;
    
    clsTasks(std::string fileName);

    bool editTask(std::string newDescription, int id);
    bool deleteTask(int id);
    bool completeTask(int id);
    bool saveToFile();
    std::vector<clsTask> getTasks();
    void addTask(clsTask task);
    bool isEmpty();
    static int getLastId();
};

clsTasks::clsTasks(std::string fileName) : fileName(fileName) {
    loadFromFile();
}

bool clsTasks::loadFromFile() {
    std::ifstream inFile(fileName);
    if (!inFile) {
        return 0;
    }

    tasks.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        clsTask task = clsTask::fromLine(line);
        tasks.push_back(task);
        lastIdRecord = task.getId()+1;
    }

    inFile.close();
    return 1;
}

bool clsTasks::editTask(std::string newDescription, int id) {
    for (auto& task : tasks) {
        if (task.getId() == id && !task.getIsDeleted()) {
            task.edit(newDescription);
            return 1;
        }
    }
    return 0;
}

bool clsTasks::deleteTask(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id && !task.getIsDeleted()) {
            task.markDelete();
            return 1;
        }
    }
    return 0;
}

bool clsTasks::completeTask(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id && !task.getIsDeleted()) {
            task.markComplete();
            return 1;
        }
    }
    return 0;
}

bool clsTasks::saveToFile() {
    std::ofstream outFile(fileName);
    if (!outFile) {
        return false;
    }

    for (clsTask& task : tasks) {
        if(!task.getIsDeleted())
            outFile << task.toLine() << std::endl;
    }

    outFile.close();
    return true;
}

std::vector<clsTask> clsTasks::getTasks() {
    return tasks;
}

void clsTasks::addTask(clsTask task)
{
    tasks.push_back(task);
    lastIdRecord++;
}

int clsTasks::getLastId()
{
    return lastIdRecord;
}

bool clsTasks::isEmpty()
{
    return tasks.empty();
}