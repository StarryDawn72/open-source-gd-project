# cat
from pathlib import Path

start_string = """
# Open Source GD Project (work in progress)

<p align="center">
  <img src="logo.png" alt="Logo">
</p>

### **Manually verified reconstructions of Geometry Dash functions for modders**

Welcome to the Open Source Geometry Dash Project. This is (hopefully) what I plan to be the most reliable source of information for reverse-engineered function implementations. Basically, I like wasting hours of my spare time and making myself suffer just so I can help the GD modding community. You're welcome 😉.

**What makes my recontructions stand out from others**
- I rename incorrect or imprecise variables from bindings
- I manually verify every function with minimal use of AI
- I override the original and test my reconstruction in-game as proof
- I recover the original intent behind the implementation
- I provide a detailed description of at the top of every function
- I don't post a bunch of slop

If you are in need of a function's code, or want to simply request an addition, please open a PR or message me on discord at @starrydawn72. All pull requests will go through manual confirmation before being added to the repository.

*Note: you often see me renaming member variables from bindings - thats' because some of them are incorrectly named. A list of renamed variables can be found in [the markdown file](./RENAMED_BINDINGS.md)*.

---
**Info:**
- Game version: 2.2081
- Software used: [Hex-Rays IDA Professional 9.3 (With BromaIDA for symbols)](https://hex-rays.com/ida-pro)

---

### **Number of entries per class**
"""

ROOT_DIR = Path(__file__).resolve().parent
SCRIPT_DIR = ROOT_DIR / "src"
README_PATH = ROOT_DIR / "README.md"

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