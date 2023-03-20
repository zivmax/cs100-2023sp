# CS100-2023-Spring-homework

## Notes before testing you programs

Before you starting to use the testcase privided by the course, you should set up your compiler's exacuting arguments to the following

For C 
```
-fsanitize=signed-integer-overflow -g -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer -ggdb3 -O0 -std=c17 -Wall -Werror -Wextra -Wshadow -Wpedantic
```

For C++
```
-fsanitize=signed-integer-overflow -g -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer -ggdb3 -O0 -std=c++17 -Wall -Werror -Wextra -Wshadow -Wpedantic
```

## A refer configuration of VScode on Linux (wsl): 
### tasks.json in .vscode dir
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
            "label": "C: gcc-11 build active file",
            "command": "/usr/bin/gcc-11",
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

## A refer configuration of VScode on Windows:
### tasks.json in .vscode dir
```json

```
