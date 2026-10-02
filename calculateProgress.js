const fs = require('fs');

const sizes = JSON.parse(fs.readFileSync('functionSizes.json'));

let listCompleted = false;
let listRemaining = false;

let filter = "";

for (const arg of process.argv.slice(2)) {
    if (arg == '-c') {
        listCompleted = true;
    } else if (arg == '-r') {
        listRemaining = true;
    } else if (filter == "")
        filter = arg;
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

    let finishedSize = 0;

    for (const file of fs.readdirSync(classDir)) {
        if (!file.endsWith('.cpp'))
            continue;

        const name = file.substring(0, file.length - 4);

        if (typeof(funcs[name]) != 'number') {
            console.log(`\x1b[0;33mCould not get the function for ${className}/${file}! Is it named correctly?\x1b[0m`);
            continue;
        }

        finishedSize += funcs[name];
    }

    console.log(`${className}: \x1b[1;37m${(finishedSize / totalSize * 100).toPrecision(3)}%\x1b[0m finished. (${finishedSize}b of ${totalSize}b)`);

    if (listCompleted) {
        const files = fs.readdirSync(classDir).sort((a, b) => a[0].localeCompare(b[0]));

        for (const file of files) {
            if (!file.endsWith('.cpp'))
                continue;

            const name = file.substring(0, file.length - 4);

            if (typeof(funcs[name]) != 'number')
                continue;

            console.log(`  - ${file} is \x1b[1;37m${(funcs[name] / totalSize * 100).toPrecision(3)}%\x1b[0m of ${className} (${funcs[name]}b of ${totalSize}b)`);
        }
    }

    if (listRemaining) {

        for (const file of fs.readdirSync(classDir)) {
            if (!file.endsWith('.cpp'))
                continue;

            const name = file.substring(0, file.length - 4);

            delete funcs[name];
        }

        let remFuncs = Object.entries(funcs);

        remFuncs.sort((a, b) => a[0].localeCompare(b[0]));

        for (const [name, size] of remFuncs) {
            console.log(`  - ${name} is \x1b[1;37m${(size / totalSize * 100).toPrecision(3)}%\x1b[0m of ${className} (${funcs[name]}b of ${totalSize}b)`);
        }
    }
}

if (filter == "" && !listRemaining && !listCompleted) {
    console.log("\x1b[90mYou can write a class name as an argument (ex. PlayerObject) and it will only show info about that class");
    console.log("\x1b[90mYou can also include options -r or -c to list remaining and completed functions and their percentages respectively\x1b[0m");
}