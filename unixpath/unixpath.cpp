#include "unixpath.h"
#include <stack>

std::string Normalize(const std::string_view& new_path) {
    std::string path{new_path};
    std::string answer;
    std::string dir;
    std::stack<std::string> stack_fir;
    answer.append("/");
    for (size_t i = 0; i < path.size(); ++i) {
        dir.clear();
        while (path[i] == '/') {
            ++i;
        }
        while (i < path.size() && path[i] != '/') {
            dir.push_back(path[i]);
            ++i;
        }
        if (dir.compare(".") == 0) {
            continue;
        } else if (dir.compare("..") == 0) {
            if (!stack_fir.empty()) {
                stack_fir.pop();
            }
        } else if (!dir.empty()) {
            stack_fir.push(dir);
        }
    }
    std::stack<std::string> stack_sec;
    while (!stack_fir.empty()) {
        stack_sec.push(stack_fir.top());
        stack_fir.pop();
    }
    while (!stack_sec.empty()) {
        std::string temp = stack_sec.top();
        if (stack_sec.size() != 1) {
            answer.append(temp + "/");
        } else {
            answer.append(temp);
        }
        stack_sec.pop();
    }
    return answer;
}
std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string res;
    if (path[0] == '/') {
        return Normalize(path);
    }
    res += current_working_dir;
    res += '/';
    res += path;
    return Normalize(res);
}
