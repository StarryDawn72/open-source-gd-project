const fs = require('fs');

const sizes = JSON.parse(fs.readFileSync('functionSizes.json'));

let listAll = process.argv.length >= 2 && process.argv[2] == 'all';

for (const [className, funcs] of Object.entries(sizes)) {
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

    if (listAll) {
        for (const file of fs.readdirSync(classDir)) {
            if (!file.endsWith('.cpp'))
                continue;

            const name = file.substring(0, file.length - 4);

            if (typeof(funcs[name]) != 'number')
                continue;

            console.log(`  - ${file} is \x1b[1;37m${(funcs[name] / totalSize * 100).toPrecision(3)}%\x1b[0m of ${className} (${funcs[name]}b of ${totalSize}b)`);
        }
    }
}

if (!listAll)
    console.log("Add argument 'all' to show all functions and their percentages");