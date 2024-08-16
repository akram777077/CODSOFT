#include <string>
class clsTask {
private:
    int id;
    std::string description;
    bool isComplete;
    bool isDeleted;

public:
    clsTask(int id, std::string description, bool isComplete = false);

    int getId();
    std::string getDescription();
    bool getIsComplete();
    bool getIsDeleted();
    void edit(std::string newDescription);

    void markComplete();
    void markDelete();
};
clsTask::clsTask(int id, std::string description, bool isComplete)
    : id(id), description(description), isComplete(isComplete), isDeleted(false) {}

void clsTask::edit(std::string newDescription)
{
    this->description = newDescription;
}

int clsTask::getId() {
    return id;
}

std::string clsTask::getDescription() {
    return description;
}

bool clsTask::getIsComplete() {
    return isComplete;
}

bool clsTask::getIsDeleted() {
    return isDeleted;
}

void clsTask::markComplete() {
    isComplete = true;
}

void clsTask::markDelete() {
    isDeleted = true;
}
