const fs = require('fs');
const path = require('path');

const sizes = JSON.parse(fs.readFileSync('functionSizes.json'));

let listCompleted = false;
let listRemaining = false;
let sortBySize = false;

let filter = "";

for (const arg of process.argv.slice(2)) {
    if (arg == '-c') {
        listCompleted = true;
    } else if (arg == '-r') {
        listRemaining = true;
    } else if (arg == '-s') {
        sortBySize = true;
    } else if (filter == "")
        filter = arg;
}

const identifierChars = "azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN1234567890_";

function isIdentifierChar(ch) {
    return identifierChars.indexOf(ch) != -1;
}

function fetchEmptyFunctionNames(filePath, className, out) {
    const code = fs.readFileSync(filePath).toString();

    let i = 0;
    while (i < code.length) {
        if (code.substring(i, i + className.length + 2) != (className + '::')) {
            i++;
            continue;
        }

        i += className.length + 2;

        let start = i;

        while (i < code.length && isIdentifierChar(code[i]))
            i++;

        let name = code.substring(start, i);
        out.push(name);
    }
}

function fetchCompletedFunctionsFromClassDir(classDir, className) {
    let completedFuncs = [];

    for (const file of fs.readdirSync(classDir)) {
        if (!file.endsWith('.cpp'))
            continue;

        if (file == "_empty_functions.cpp") {
            fetchEmptyFunctionNames(path.join(classDir, file), className, completedFuncs);
            continue;
        }

        completedFuncs.push(file.substring(0, file.length - 4));
    }

    return completedFuncs;
}

for (const [className, funcs] of Object.entries(sizes)) {
    if (filter != "" && className != filter)
        continue;

    const classDir = `./src/${className}`;

    if (!fs.existsSync(classDir))
        continue;

    let totalSize = 0;
    for (const [_, s] of Object.entries(funcs)) {
        totalSize += s;
    }

    let completedSize = 0;
    let completedCount = 0;

    const completedFuncs = fetchCompletedFunctionsFromClassDir(classDir, className);

    for (const name of completedFuncs) {
        if (typeof(funcs[name]) != 'number') {
            console.log(`\x1b[0;33mCould not get the function for ${className}::${name}! Is it named correctly?\x1b[0m`);
            continue;
        }

        completedSize += funcs[name];
        completedCount++;
    }

    console.log(`${className}: \x1b[1;37m${(completedSize / totalSize * 100).toPrecision(3)}%\x1b[0m finished. (${completedCount}/${Object.entries(funcs).length}) (${completedSize}b of ${totalSize}b)`);

    if (listCompleted) {
        if (sortBySize)
            completedFuncs.sort((a, b) => funcs[a] - funcs[b]);
        else
            completedFuncs.sort((a, b) => a[0].localeCompare(b[0]));

        for (const name of completedFuncs) {
            console.log(`  - ${name} is \x1b[1;37m${(funcs[name] / totalSize * 100).toPrecision(3)}%\x1b[0m of ${className} (${funcs[name]}b of ${totalSize}b)`);
        }
    }

    if (listRemaining) {
        for (const name of completedFuncs)
            delete funcs[name];

        let remFuncs = Object.entries(funcs);

        if (sortBySize)
            remFuncs.sort((a, b) => a[1] - b[1]);
        else
            remFuncs.sort((a, b) => a[0].localeCompare(b[0]));

        for (const [name, size] of remFuncs) {
            console.log(`  - ${name} is \x1b[1;37m${(size / totalSize * 100).toPrecision(3)}%\x1b[0m of ${className} (${funcs[name]}b of ${totalSize}b)`);
        }
    }
}

if (filter == "" && !listRemaining && !listCompleted) {
    console.log("\x1b[90mYou can write a class name as an argument (ex. PlayerObject) and it will only show info about that class");
    console.log("\x1b[90mYou can also include options -r or -c to list remaining and completed functions and their percentages respectively\x1b[0m");
    console.log("\x1b[90mAdd option -s to sort the functions by size\x1b[0m");
}