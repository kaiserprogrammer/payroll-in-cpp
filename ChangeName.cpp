class ChangeName : public ChangeEmployee
{
public:
  std::string name;

  ChangeName(int empId, std::string name, DB* db)
    : ChangeEmployee(empId, db), name(name) {};

  void change() {
    employee->name = name;
  }
};
