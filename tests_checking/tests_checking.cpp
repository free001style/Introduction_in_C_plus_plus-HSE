#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> name_list;
    std::vector<std::string> ans;
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            name_list.push_front(student_actions[i].name);
        } else if (student_actions[i].side == Side::Bottom) {
            name_list.push_back(student_actions[i].name);
        }
    }
    for (size_t i = 0; i < queries.size(); ++i) {
        ans.push_back(name_list[queries[i] - 1]);
    }
    return ans;
}
