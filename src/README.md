## How the AST classes are defined

`class_name: data_members`

```
node
  └─ expression
        ├─ decimal: value
        ├─ fraction: value
        ├─ string lit: value
        ├─ binary_operator: lhs, op, rhs
        ├─ identifier: name
        ├─ block : vector<statement>
        ├─ assignment: lhs, rhs
        └─ function_call: ident, args_list
  └─ statement
        ├─ expr_statement: expr
        └─ variable_declaration: type, ident, assign_expr
```