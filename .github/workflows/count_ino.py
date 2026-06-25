import os

def count_ino_files():
    count = 0
    ino_files = []
    # Walk the directory tree, ignoring .git directory
    for root, dirs, files in os.walk('.'):
        # Ignore .git and build directories
        if '.git' in root or 'build' in root or '.arduino' in root:
            continue
        for file in files:
            if file.endswith('.ino'):
                count += 1
                ino_files.append(os.path.join(root, file))
                
    print("=" * 40)
    print("GitHub Actions - Arduino File Analyzer")
    print("=" * 40)
    print(f"Total .ino files found: {count}")
    print("\nFile list:")
    for path in ino_files:
        print(f"  - {path}")
    print("=" * 40)

if __name__ == '__main__':
    count_ino_files()
