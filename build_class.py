from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
SRC_DIR  = SCRIPT_DIR / "src"
FORBIDDEN_MACROS = [
    "GM GameManager::sharedState()",
    "PL GameManager::sharedState()->getPlayLayer()"
]

########## SETTINGS ##########

FOLDER     = "GJGroundLayer"
CPP_NAME   = "GJGroundLayer"
INCLUDES   = [
    "GJGroundLayer.h"
]
CPP_ORDER  = [
    "showGround",
    "fadeOutGround",
    "fadeInFinished",
    "draw",
    "fadeInGround",
    "toggleVisible01",
    "toggleVisible02",
    "loadGroundSprites",
    "updateGroundPos",
    "updateGround01Color",
    "updateGround02Color",
    "createLine",
    "init",
    "create",
    "updateGroundWidth",
    "updateLineBlend",
    "hideShadows",
    "updateShadows",
    "scaleGround",
    "updateShadowXPos",
    "deactivateGround",
    "positionGround",
    "getGroundY"
]

##############################

def build_macros_string(macros) -> str:
    return "\n".join(macros) + "\n\n"

def build_includes_string() -> str:
    includes_string = ""
    for include in INCLUDES:
        includes_string += '#include "' + include + '"' + "\n"

    if includes_string != "": includes_string += "\n"
    return includes_string

def verify_syntax(dir: Path) -> bool:
    success = True

    for file in sorted(dir.iterdir()):
        if not file.is_file() or file.suffix.lower() != ".cpp": continue

        raw = file.read_text("utf-8")
        raw_lines = raw.split("\n")

        opening_braces = 0
        closing_braces = 0

        for line in raw_lines:
            if line.rstrip() == "{":
                opening_braces += 1

            elif line.rstrip() == "}":
                closing_braces += 1
                if closing_braces != opening_braces:
                    success = False
                    print(f"[ERR] {file.name} contains a function that doesn't have its opening brace on a new line")
                    break

        if opening_braces == 0 or closing_braces == 0:
            success = False
            print(f"[ERR] {file.name} does not contain a function definition.")

    if not success: print("[INFO] Aborting.")
    return success

def main():
    dir: Path = SRC_DIR / FOLDER
    func_string = ""
    function_dict: dict[str, str] = {} # func name, func body
    macros: list[str] = []

    if len(CPP_ORDER) == 0:
        print("[ERR] C++ order of functions was not provided. Aborting.")
        return

    cpp_count = 0
    for file in sorted(dir.iterdir()):
        if not file.is_file() or file.suffix.lower() != ".cpp": continue
        cpp_count += 1

    if len(CPP_ORDER) != cpp_count:
        print("[ERR] Length of C++ order functions does not match directory. Aborting.")
        return

    if not verify_syntax(dir):
        return

    for file in sorted(dir.iterdir()):
        if not file.is_file() or file.suffix.lower() != ".cpp": continue
        func_name = file.name.rstrip(".cpp")

        raw = file.read_text("utf-8")
        raw_lines = raw.split("\n")

        in_function = False
        func_body = ""

        for i, line in enumerate(raw_lines):
            if line.startswith("#define") and line not in macros and line.lstrip("#define").strip() not in FORBIDDEN_MACROS:
                macros.append(line)
            elif line.rstrip() == "{":
                in_function = True
                func_body += "\n\n" + raw_lines[i - 1] + "\n" + "{" + "\n"
            elif line.rstrip() == "}":
                in_function = False
                func_body += "}"
            elif in_function:
                func_body += line + "\n"

        func_body = func_body.lstrip()

        if func_body.strip() == "":
            print(f"[ERR] Unexpected error. Function \"{func_name}\" was somehow empty. Aborting.")
            return

        function_dict[func_name] = func_body

    for function in CPP_ORDER:
        if function not in function_dict or function_dict.get(function) == None:
            print(f"[ERR] Function \"{function}\" was not found in folder. Aborting.")
            return

        func_string += function_dict.get(function, "") + "\n\n"

    func_string = func_string.strip()
    final_string = build_includes_string() + build_macros_string(macros) + func_string

    name = CPP_NAME + ".cpp"
    file_path = SRC_DIR / name

    with open(file_path, "w", encoding="utf-8") as file:
        file.write(final_string)

    print(f"[INFO] Successfully saved {name}.")

if __name__ == "__main__":
    main()