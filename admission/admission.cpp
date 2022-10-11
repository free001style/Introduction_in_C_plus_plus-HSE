#include "admission.h"
#include <algorithm>
#include <map>
#include <tuple>

bool Comp(const Applicant& a, const Applicant& b) {
    return std::tie(b.points, a.student.birth_date.year, a.student.birth_date.month, a.student.birth_date.day,
                    a.student.name) < std::tie(a.points, b.student.birth_date.year, b.student.birth_date.month,
                                               b.student.birth_date.day, b.student.name);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    //зафиксируем искодный порядок студентов а также создадим копию applicants чтобы отсортировать
    AdmissionTable ans;
    std::vector<Applicant> copy_app = applicants;
    std::map<std::string, int> fix_app;
    for (size_t i = 0; i < applicants.size(); ++i) {
        fix_app[applicants[i].student.name] = i;
    }
    bool pass = false;
    std::sort(copy_app.begin(), copy_app.end(), Comp);            //сортировка
    for (int i = 0; i < copy_app.size(); ++i) {                   //проход по всем студентам
        for (int j = 0; j < copy_app[i].wish_list.size(); ++j) {  //проход по их универам
            for (int k = 0; k < universities.size(); ++k) {       //поиск нужного универа
                if (copy_app[i].wish_list[j] == universities[k].name &&
                    universities[k].max_students >
                        ans[universities[k].name].size()) {  //поиск + проверка на наличие мест
                    ans[copy_app[i].wish_list[j]].push_back(&applicants[fix_app[copy_app[i].student.name]].student);
                    pass = true;
                    break;
                }
            }
            if (pass) {  //если поступил то выходим до главного цикла если нет то остаёмся во втором
                pass = false;
                break;
            }
        }
    }
    return ans;
}
