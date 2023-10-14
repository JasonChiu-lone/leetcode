# pandas schema
import pandas as pd

def top_three_salaries(employee: pd.DataFrame, department: pd.DataFrame) -> pd.DataFrame:
    ret = pd.DataFrame(columns=['Department', 'Employee', 'Salary'])
    for dept_id in department['id'].unique():
        print(f"In department {dept_id}:")
        dept_name = department.loc[department['id']==dept_id, 'name'].iloc[0]
        dept_eply = employee.loc[employee['departmentId'] == dept_id, ['name', 'salary']]
        dept_eply = dept_eply[dept_eply['salary'].rank(method='dense', ascending=False) <= 3]
        dept_eply.columns = ['Employee', 'Salary']
        # dept_eply['Department'] = dept_name
        dept_eply.insert(0, 'Department', dept_name)
        print(dept_eply)
        ret = pd.concat([ret, dept_eply])
    return ret

data = [[1, 'Joe', 85000, 1], [2, 'Henry', 80000, 2], [3, 'Sam', 60000, 2], [4, 'Max', 90000, 1], [5, 'Janet', 69000, 1], [6, 'Randy', 85000, 1], [7, 'Will', 70000, 1]]
employee = pd.DataFrame(data, columns=['id', 'name', 'salary', 'departmentId']).astype({'id':'Int64', 'name':'object', 'salary':'Int64', 'departmentId':'Int64'})
data = [[1, 'IT'], [2, 'Sales']]
department = pd.DataFrame(data, columns=['id', 'name']).astype({'id':'Int64', 'name':'object'})

print("Employee info:")
print(employee)

print(top_three_salaries(employee, department))