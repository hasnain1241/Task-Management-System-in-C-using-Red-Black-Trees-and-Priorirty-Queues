# Task Management System using Red-Black Trees

This project is a **Task Management System** implemented in C++ using **Red-Black Trees**. The system efficiently handles task creation, deletion, and searching, ensuring operations remain balanced and fast. Red-Black Trees are a self-balancing binary search tree, and they ensure that the task management system performs consistently well, even under heavy usage.

## Features

- **Add Task**: Insert a new task with a priority and description into the system.
- **Delete Task**: Remove a task from the system by its priority or description.
- **Search Task**: Search for tasks by priority or keyword.
- **Display Tasks**: Display all tasks in the system, either sorted by priority or filtered by certain criteria.
- **Modify Task**: Update the description or priority of an existing task.
- **Balanced Performance**: Red-Black Tree ensures logarithmic time complexity for insertion, deletion, and search operations, making the system efficient even with large numbers of tasks.

## Red-Black Tree Properties

The Red-Black Tree ensures that:
- Every node is either red or black.
- The root is always black.
- Red nodes cannot have red children.
- Every path from a node to its leaves has the same number of black nodes.

These properties ensure that the tree remains balanced, preventing the worst-case performance that can occur with unbalanced binary search trees.

### 4. Example Commands
- **Add Task**: `add_task(priority, "Task description")`
- **Delete Task**: `delete_task(priority)`
- **Search Task**: `search_task(priority)`
- **Display Tasks**: `display_all_tasks()`
- **Modify Task**: `modify_task(priority, "Updated task description")`


## Contributions

Contributions, issues, and feature requests are welcome! Feel free to check out the [issues page](https://github.com/yourusername/task-management-system/issues).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
