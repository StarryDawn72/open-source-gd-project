# cat
from pathlib import Path

start_string = """
<p align="center">
  <img src="banner.png" alt="Logo">
</p>

<h1 align="center">Manually verified reconstructions of Geometry Dash functions for modders</h1>

Welcome to the Open Source Geometry Dash Project. This is (hopefully) what I plan to be the most reliable source of information for reverse-engineered function implementations. Basically, I like wasting hours of my spare time and making myself suffer just so I can help the GD modding community.

## Verified for accuracy

Complex functions are verified by overriding the original and testing the behavior in-game.

*Note: if you see member variables that don't exist in the Geode bindings, that's because some of were renamed. A list of them can be found in [the markdown file](./RENAMED_BINDINGS.md)*.

## Information

- Game versions: 2.2081, 2.2091
- Software used for reversing: [Hex-Rays IDA Professional 9.3](https://hex-rays.com/ida-pro) with [BromaIDA for symbols](https://github.com/Stazzical/BromaIDA)

## Contribution (please read)

If you are in need of a function's code that isn't already on this list, or want to simply request an addition, please open a PR or message me on discord at @starrydawn72. All pull requests will go through manual confirmation before being added to the repository.
<br>
<br>
**Rules for submitting a function** through a pull request:
- Decompilation must be done in IDA, reconstructions using Ghidra will not be accepted
- Its behavior must be tested in-game by overriding the original using a Geode mod
- Member variables featured in [RENAMED_BINDINGS.md](./RENAMED_BINDINGS.md) must use their new name
- The function's opening brace should be on the next line (for consistency)
- Always prefer C-style casts over static_cast to match RobTop's coding style (e.g. `(RingObject*)m_touchingRings->objectAtIndex(i)`)

You should view the existing reconstructions on this repo to get an idea of the style before submission.

## Shortcut links to entries per class

"""

ROOT_DIR = Path(__file__).resolve().parent
VERSIONS_DIR = ROOT_DIR / "versions"
README_PATH = ROOT_DIR / "README.md"

HTML_START = "<details>\n"
HTML_END = "</details>\n"
SUMMARY_START = "\t<summary> <b>"
SUMMARY_MID = "</b>  ("
SUMMARY_END = ")</summary>\n"
UL_START = "\t<ul>\n"
UL_END = "\t</ul>\n"
LI_START = "\t\t<li><a href=\"./versions/"
LI_MID = ".cpp\">"
LI_END = "</a></li>\n"
LI_SLASH = "/"

FINISHED_CLASSES = {
    "2.2081": {
        "AnimatedShopKeeper",
        "CCCircleWaveDelegate",
        "CCCircleWave",
        "GJFlyGroundLayer",
        "GJGroundLayer"
    },
    "2.2091": {}
}

def get_others_string(version):
    return f"""<details>
        <summary> <b>Other</b> (1)</summary>
        <ul>
            <li><a href="./versions/{version}/FreeFunctions.cpp">Free Functions</a></li>
        </ul>
    </details>
    """


def get_entry_string(directory, version):
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

            if item.name == ".git": continue
            
            complete = item.name in FINISHED_CLASSES[version]

            complete_string = " ✔️" if complete else ""
            
            entry = HTML_START + SUMMARY_START + item.name + complete_string + SUMMARY_MID + f"{cpp_count}" + SUMMARY_END + UL_START
            li_strings = ""
            
            for cpp_file in item.iterdir():
                if cpp_file.is_file() and cpp_file.suffix.lower() == ".cpp":
                    trimmed_name = cpp_file.name.replace(".cpp", "")
                    current_li = LI_START + version + "/" + item.name + LI_SLASH + trimmed_name + LI_MID + trimmed_name + LI_END
                    li_strings += current_li

            entry += li_strings + UL_END + HTML_END
            result.append(entry)

    return ''.join(result) + get_others_string(version) if result else "[!ERR_2]"

def update():
    version_entries = []

    for item in sorted(VERSIONS_DIR.iterdir()):
        if item.is_dir():
            version_entries.append("## " + item.name + "\n\n" + get_entry_string(item, item.name) + "\n")

    version_entries.reverse()

    final_string = start_string + "".join(version_entries)

    with README_PATH.open("w", encoding="utf-8") as file:
        file.write(final_string)

    print(f"updated {README_PATH}")

if __name__ == "__main__":
    update()