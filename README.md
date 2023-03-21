# CS100-2023-Spring-homework

## Notes before testing you programs

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


## A refer Debug configuration of VScode on Linux (wsl): 
### `tasks.json` in `.vscode` dir
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
### `lanuch.json` in `.vscode` dir
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


## A refer configuration of VScode on Windows:
### `tasks.json` in `.vscode` dir
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

### `lanuch.json` in `.vscode` dir
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
