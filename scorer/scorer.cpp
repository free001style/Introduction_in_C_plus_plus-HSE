#include "scorer.h"
#include <tuple>
#include <string>
bool Comp(const Event& a, const Event& b) {
    return std::tie(a.time) < std::tie(b.time);
}
void Insert(ScoreTable& db, const std::string& name, const std::string& tasks) {
    if (db.find(name) == db.end()) {
        db[name] = {tasks};
    } else {
        db[name].insert(tasks);
    }
}
void Erase(ScoreTable& db, const std::string& name, const std::string& tasks) {
    if (db.find(name) != db.end() && db[name].find(tasks) != db[name].end()) {
        db[name].erase(tasks);
    }
}
ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<Event> copy_events = events;
    std::sort(copy_events.begin(), copy_events.end(), Comp);
    ScoreTable res;
    ScoreTable merge_req;
    for (size_t i = 0; i < copy_events.size(); ++i) {
        if (copy_events[i].time <= score_time) {
            if (copy_events[i].event_type == EventType::CheckSuccess) {
                Insert(res, copy_events[i].student_name, copy_events[i].task_name);
            } else if (copy_events[i].event_type == EventType::CheckFailed) {
                if (res.find(events[i].student_name) != res.end()) {
                    res[copy_events[i].student_name].erase(copy_events[i].task_name);
                }
            } else if (copy_events[i].event_type == EventType::MergeRequestOpen) {
                Erase(res, copy_events[i].student_name, copy_events[i].task_name);
                Insert(merge_req, copy_events[i].student_name, copy_events[i].task_name);
            } else {
                Erase(merge_req, copy_events[i].student_name, copy_events[i].task_name);
                Insert(res, copy_events[i].student_name, copy_events[i].task_name);
            }
        }
    }
    for (auto it = res.begin(); it != res.end(); ++it) {
        if (it->second.empty()) {
            res.erase(it->first);
        }
    }
    return res;
}
