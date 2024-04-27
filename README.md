# CS100: C and C++ Programming

*By [ShanghaiTech University](https://www.shanghaitech.edu.cn/)*
## Course Introduction
Programming is an essential skill across many engineering disciplines. 

This course is designed for beginning undergraduate students and focuses on the programming languages C and C++. These powerful low-level languages are ideal for the efficient implementation of resource-intensive programs. 

The course spans 16 weeks and emphasizes practical skills, highlighted by weekly recitations. 
In these sessions, groups of approximately 20-30 students will review and expand on class material through interactive coding exercises. 

The grading structure is heavily weighted towards practical experience, with the majority of the score derived from homework. A midterm exam provides a traditional assessment of knowledge.

## Learning Goals

### Cognitive Competence:
- Learn C and C++ features, including recent standards.
- Understand various programming paradigms such as sequential, object-oriented, recursive, and functional programming.
- Explore polymorphism and the standard template library.
- Study concurrency and modern C++ standards.
- Acquire knowledge in cross-compilation, profiling, debugging, and interfacing.

### Comprehensive Qualities:
- Develop problem-solving and modular thinking skills.
- Acquire practical engineering skills for solving real-world problems efficiently.

## Instructional Pedagogy
- **Lectures:** 4 hours per week for 16 weeks.
- **Recitations:** 2 hours per week for 15 weeks, starting from week 2.
- **Homework Assignments:** 8 total; 4 initial assignments of smaller volume, followed by 4 larger and more challenging assignments.
- **Midterm Exam:** One exam to assess understanding.
- **Quizzes:** Two quizzes to monitor class attendance.
- **Online Forum:** Piazza used for answering questions.
- **Office Hours:** Provided by both the Professor and Teaching Assistants.


## Technique Notes 

### Notes before testing you programs

Personally, I strongly recommend using WSL as the environment, else, use Visual studio on windows.

because you should ensure your program won't cause any mem leak, and they provides tools for checking it

Before you starting to use the testcase privided by the course, you should set up your compiler's exacuting arguments to the following

For C 
```bash
-ggdb3 -O2 -std=c17 -Wall -Werror -Wextra -Wshadow -Wpedantic
```

For C++
```bash
-ggdb3 -O2 -std=c++17 -Wall -Werror -Wextra -Wshadow -Wpedantic
```

if you are using Linux (WSL), the fsantitazer should be used too
```bash
-fsanitize=signed-integer-overflow -g -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer 
```


### A refer Debug configuration of VScode on Linux (wsl): 
#### `tasks.json` in `.vscode` dir
```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C++: g++ build active file",
            "command": "/usr/bin/g++",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}",
                "-Wall",
                "-Wextra",
                "-Werror",
                "-Wshadow",
                "-Wpedantic",
                "-fsanitize=address",
                "-fno-omit-frame-pointer",
                "-fsanitize=signed-integer-overflow",
                "-fsanitize=undefined",
                "-ggdb3",
                "-O0",
                "-std=c++17",
                "-g",
                "-lm",
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": false
            },
            "detail": "To compile C++ code."
        },
        {
            "type": "cppbuild",
            "label": "C: gcc build active file",
            "command": "/usr/bin/gcc",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}",
                "-Wall",
                "-Wextra",
                "-Werror",
                "-Wshadow",
                "-Wpedantic",
                "-fsanitize=address",
                "-fno-omit-frame-pointer",
                "-fsanitize=signed-integer-overflow",
                "-fsanitize=undefined",
                "-ggdb3",
                "-O0",
                "-std=c17",
                "-g",
                "-lm",
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "To compile C code."
        }
    ],
    "version": "2.0.0"
}
```
#### `lanuch.json` in `.vscode` dir
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "GDB 调试",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "/usr/bin/gdb",
        },
    ]
}
```


### A refer configuration of VScode on Windows:
#### `tasks.json` in `.vscode` dir
```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc.exe 生成活动文件",
            "command": "D:\\Program Files\\mingw64\\bin\\gcc.exe", // ！！！ replace this with your compiler path
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
                "-Wall",
                "-Wextra",
                "-Werror",
                "-Wshadow",
                "-Wpedantic",
                "-ggdb3",
                "-O0",
                "-std=c17",
                "-g",
                "-lm",
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": "build",
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
```

#### `lanuch.json` in `.vscode` dir
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "GDB 调试",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "D:\\Program Files\\mingw64\\bin\\gbd.exe", // ！！！ replace this with your debugger path
        },
    ]
}
```
