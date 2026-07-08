# cat
import os
from pathlib import Path

start_string = """
### **Manually verified reconstructions of Geometry Dash functions for modders (work in progress)**
---

Basically, I like wasting hours of my spare time and making myself suffer just so I can help the GD modding community. You're welcome 😉.

**What makes my recontructions stand out from others**
- I take RobTop's coding patterns into account
- I recover the original intent behind the implementation
- I manually verify every function with minimal use of Generative AI
- I provide a detailed description of at the top of every function
- I don't post a bunch of slop

---

### **Number of entries**
"""

SCRIPT_DIR = Path(__file__).resolve().parent
README_PATH = SCRIPT_DIR / "README.md"

def get_entry_string(directory):
    directory = Path(directory)
    if not directory.exists() or not directory.is_dir():
        return "[!ERR_1]"

    result = []

    for item in sorted(directory.iterdir()):
        if item.is_dir():
            cpp_count = sum(
                1
                for file in item.iterdir()
                if file.is_file() and file.suffix.lower() == ".cpp"
            )
            if (item.name != ".git"):
                result.append(f"{item.name}: **{cpp_count}**")

    return '\n'.join(result) if result else "[!ERR_2]"


def update():
    final_string = start_string + get_entry_string(SCRIPT_DIR)
    with README_PATH.open("w", encoding="utf-8") as file:
        file.write(final_string)

    print(f"updated {README_PATH}")

if __name__ == "__main__":
    update()