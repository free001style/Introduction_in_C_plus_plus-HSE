#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    Erase(checking_, student_name, task_name);
    EmptySpace(checking_);
    Erase(res_, student_name, task_name);
    EmptySpace(res_);
}
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    Insert(checking_, student_name, task_name);
    if (merge_req_[student_name].find(task_name) == merge_req_[student_name].end()) {
        Insert(res_, student_name, task_name);
    }
    EmptySpace(res_);
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    Insert(merge_req_, student_name, task_name);
    Erase(res_, student_name, task_name);
    EmptySpace(res_);
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    Erase(merge_req_, student_name, task_name);
    EmptySpace(merge_req_);
    if (checking_[student_name].find(task_name) != checking_[student_name].end()) {
        Insert(res_, student_name, task_name);
    }
    EmptySpace(res_);
}
void Scorer::Reset() {
    res_.clear();
    merge_req_.clear();
    checking_.clear();
}
ScoreTable Scorer::GetScoreTable() const {
    return res_;
}
