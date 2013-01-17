class DeleteEmployee : public Transaction
{
public:
  int empId;
  DB* db;

  DeleteEmployee(int empId, DB* db)
    : empId(empId), db(db) {};

  void execute() {
    db->deleteEmployee(empId);
  }
};
