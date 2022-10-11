#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

class Scorer {
private:
    ScoreTable res_;
    ScoreTable merge_req_;
    ScoreTable checking_;
    void Insert(ScoreTable& db, const std::string& st_name, const std::string& tasks) {
        if (db.find(st_name) == db.end()) {
            db[st_name] = {tasks};
        } else {
            db[st_name].insert(tasks);
        }
    }
    void Erase(ScoreTable& db, const std::string& st_name, const std::string& task) {
        ScoreTable::iterator pos = db.find(st_name);
        if (pos != db.end()) {
            std::set<TaskName>& tasks = pos->second;
            tasks.erase(task);
        }
    }
    void EmptySpace(ScoreTable& res) {
        for (auto it = res.begin(); it != res.end();) {
            if (it->second.empty()) {
                it = res.erase(it);
            } else {
                ++it;
            }
        }
    }

public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();
    ScoreTable GetScoreTable() const;
};