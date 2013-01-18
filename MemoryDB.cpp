#include <map>

class MemoryDB : public DB
{
  int id = 0;
  int nextId() {
    return ++id;
  }

public:
  map<int,Employee*> employees;
  map<int,Employee*> members;

  Employee* getEmployee(int empId) {
    if (employees.find(empId) != employees.end()) {
      return employees.find(empId)->second;
    } else {
      return NULL;
    }
  }

  void addEmployee(Employee* e) {
    e->empId = nextId();
    employees.insert(pair<int, Employee*>(e->empId, e));
  }

  void deleteEmployee(int empId) {
    map<int, Employee*>::iterator it = employees.find(empId);
    delete(it->second);
    employees.erase(it);
  }

  std::vector<Employee*> getEmployees() {
    std::vector<Employee*> remployees;
    for(map<int, Employee*>::iterator it = employees.begin();
        it != employees.end();
        ++it) {
      remployees.push_back(it->second);
    }
    return remployees;
  }

  Employee* getUnionMember(int memberId) {
    if (members.find(memberId) != members.end()) {
      return members.find(memberId)->second;
    } else {
      return NULL;
    }
  }

  void addUnionMember(Employee* m) {
    m->memberId = nextId();
    members.insert(pair<int, Employee*>(m->memberId, m));
  }

  void deleteMember(int memberId) {
    members.erase(members.find(memberId));
  }

  void deletePointer(Employee* e) {
    // no deletion since it's an InMemoryDB
  };
};
