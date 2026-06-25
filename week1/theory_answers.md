# Module 1: Theory Questions (Q9 & Q10)

## Q9. Explain the difference between `git pull`, `git fetch`, and `git clone`. When would you use each?

| Git Command | Definition & Behavior | When to Use |
| :--- | :--- | :--- |
| **`git clone`** | Downloads an entire existing remote repository (history, branches, files) and creates a local copy of it on your system. It also automatically sets up a tracking remote named `origin`. | Use this when you want to start working on a project that is already hosted on GitHub/GitLab and you do not have a local copy yet. |
| **`git fetch`** | Downloads commits, files, and references from a remote repository into your local repository's tracking database, but does **not** merge or modify your current working directory files. | Use this when you want to check what your team members have pushed to the remote repository, compare changes, or review code before merging it into your local branch. |
| **`git pull`** | Combines `git fetch` and `git merge` in a single command. It fetches the changes from the remote branch and immediately merges them into your current checked-out local branch. | Use this when you are ready to update your local working files with the latest changes from the remote repository. |

---

## Q10. What is a `.gitignore` file? Write a `.gitignore` for an Arduino project that excludes compiled output files, OS-specific files, and IDE config folders.

### What is a `.gitignore` file?
A `.gitignore` file is a plain text file placed in the root of a Git repository. It tells Git which files or directories to ignore and not track in the repository. This is crucial for avoiding commits of generated files (like compiler build outputs, temporary files, OS-specific artifacts, or sensitive configuration files like passwords/API keys) that shouldn't be shared with other developers or uploaded to remote repositories.

### Recommended `.gitignore` for Arduino/C++ projects:
```gitignore
# Compiled output files (firmware binaries)
*.hex
*.elf
*.bin
*.eep
*.lst
*.map
*.sym
*.lss

# Object and Dependency files
*.o
*.d

# OS-specific files
.DS_Store
Thumbs.db
desktop.ini

# IDE-specific configurations and build folders
.vscode/
build/
.arduino/
cmake-build-*/
.vs/
*.suo
*.user
```
