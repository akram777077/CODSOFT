#include <string>
#include <sstream>
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

    std::string toLine() const;
    static clsTask fromLine(const std::string& line);
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

std::string clsTask::toLine() const {
    std::stringstream ss;
    ss << id << "|" << description << "|" << isComplete;
    return ss.str();
}

clsTask clsTask::fromLine(const std::string& line) {
    std::stringstream ss(line);
    std::string temp;
    int id;
    std::string description;
    bool isComplete;

    std::getline(ss, temp, '|');
    id = std::stoi(temp);

    std::getline(ss, description, '|');

    std::getline(ss, temp, '|');
    isComplete = std::stoi(temp);

    clsTask task(id, description,isComplete);
    return task;
}