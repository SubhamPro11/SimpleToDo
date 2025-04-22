# SimpleToDo

A lightweight and efficient command-line to-do list manager written in C.

## Features

- Add new tasks to your list
- View all your tasks with completion status
- Mark tasks as completed
- Remove specific tasks
- Clear all tasks at once
- Persistent storage (tasks are saved between sessions)
- Simple and intuitive command-line interface

## Installation

### Prerequisites
- GCC compiler or equivalent C compiler
- Standard C libraries

### Compilation
Clone the repository or download the source code, then compile using GCC:

```bash
gcc simple_todo.c -o simple_todo
```

## Usage

Run the program:

```bash
./simple_todo
```

### Menu Options

The program presents a simple menu interface with the following options:

1. **Add a new task**: Enter a description for your new task
2. **View all tasks**: Display all tasks with their completion status
3. **Mark a task as completed**: Select a task by number to mark as done
4. **Remove a task**: Delete a specific task from your list
5. **Clear all tasks**: Remove all tasks from your list (with confirmation)
6. **Save and exit**: Save your tasks to file and quit the program

## File Storage

Tasks are automatically saved to a file named `tasks.txt` in the same directory as the executable. This ensures your tasks persist between sessions.

The file format uses a simple structure:
- Each task is stored on a separate line
- Each line starts with a completion status (0 for incomplete, 1 for complete)
- The task description follows, separated by a pipe character (|)

## Example

```
$ ./simple_todo
Loaded 3 tasks from file.

===== TO-DO LIST MANAGER =====
1. Add a new task
2. View all tasks
3. Mark a task as completed
4. Remove a task
5. Clear all tasks
6. Save and exit
=============================
Enter your choice: 2

----- Your To-Do List -----
1. [ ] Buy groceries
2. [X] Pay bills
3. [ ] Call dentist
---------------------------

```

## Technical Details

- Written in standard C99
- Uses structures to organize task data
- Maximum of 100 tasks by default (can be modified in the source code)
- Maximum task description length of 100 characters (modifiable)

## Customization

You can modify the following constants in the source code:
- `MAX_TASKS`: Maximum number of tasks that can be stored
- `MAX_TASK_LENGTH`: Maximum length of task descriptions
- `FILENAME`: Name of the file where tasks are saved

## License

This project is open source, available under the MIT License.

## Contributing

Contributions are welcome! Feel free to submit pull requests or open issues to improve the functionality.