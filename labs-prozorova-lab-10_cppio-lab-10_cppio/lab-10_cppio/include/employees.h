#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <vector>
#include <ostream>

class Employee {
public:
    Employee(const char *name, int32_t base_salary);
    Employee() { _name = nullptr, _base_salary = 0; }
    virtual ~Employee();

    virtual int32_t salary() const = 0;

private:
    char *_name;

protected:
    void setName(const char *name);
    int32_t _base_salary;

public:
    virtual std::ostream &write(std::ostream &os) const;
    virtual std::istream &read(std::istream &is);
    virtual std::ofstream &fwrite(std::ofstream &ofs) const;
    virtual std::ifstream &fread(std::ifstream &ifs);

public:
    friend std::ostream &operator<<(std::ostream &os, const Employee &emp);
    friend std::istream &operator>>(std::istream &is, Employee &emp);
    friend std::ofstream &operator<<(std::ofstream &os, const Employee &emp);
    friend std::ifstream &operator>>(std::ifstream &is, Employee &emp);
};

class Developer : public Employee {
public:
//    explicit Developer(const char *name, int32_t base_salary, bool has_bonus);
//    Developer() : Employee(), _has_bonus(false) {}
    Developer(const char *name = "", int32_t base_salary = 0, bool has_bonus = false);

    int32_t salary() const override;

    std::ostream &write(std::ostream &os) const override;
    std::istream &read(std::istream &is) override;
    std::ofstream &fwrite(std::ofstream &os) const override;
    std::ifstream &fread(std::ifstream &is) override;

private:
//    char *_name{};
//    int32_t _base_salary{}; 
    bool _has_bonus;
};


class SalesManager : public Employee {
public:
//    explicit SalesManager(const char *name, int32_t base_salary, int32_t sold_nm, int32_t price);
//    SalesManager() : Employee(), _sold_nm(0), _price(0) {}
    SalesManager(const char *name = "", int32_t base_salary = 0, int sold_nm = 0, int price = 0);

    int32_t salary() const override;

    std::ostream &write(std::ostream &os) const override;
    std::istream &read(std::istream &is) override;
    std::ofstream &fwrite(std::ofstream &os) const override;
    std::ifstream &fread(std::ifstream &is) override;

private:
//    [[maybe_unused]] char *_name{};
//    int32_t _base_salary{};
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray() = default;
    ~EmployeesArray();

    void add(Employee *e);
    int32_t total_salary() const;

    friend std::ostream &operator<<(std::ostream &os, const EmployeesArray &emp);
    friend std::istream &operator>>(std::istream &is, EmployeesArray &emp);
    friend std::ofstream &operator<<(std::ofstream &os, const EmployeesArray &emp);
    friend std::ifstream &operator>>(std::ifstream &is, EmployeesArray &emp);

private:
    std::vector<Employee *> employees;
};

#endif
