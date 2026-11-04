/*
    You shouldn't run this
*/

import { XMLParser } from "fast-xml-parser";
import fs from "fs";

const xmlData = fs.readFileSync("./libcocos2dcpp_2.2081_32.so.xml");

const parser = new XMLParser({ignoreAttributes: false});
let obj = parser.parse(xmlData);

let functions = {};

function getRangeSize(range) {
    return parseInt(range['@_END'], 16) - parseInt(range['@_START'], 16) + 1;
}

for (const func of obj.PROGRAM.FUNCTIONS.FUNCTION) {
    let name = func['@_NAME'].split('::');

    if (name.length != 2 || name[0].startsWith('<'))
        continue;

    if (!functions[name[0]])
        functions[name[0]] = {};

    if (name[0] == name[1]) {
        let oname = func.REGULAR_CMT;
        if (oname) {
            if (Array.isArray(oname))
                oname = oname[0];

            name = oname.split('(')[0].split('::');
        }
    }

    const ranges = func.ADDRESS_RANGE;

    let totalSize = 0;

    if (Array.isArray(ranges)) {
        for (const range of ranges)
            totalSize += getRangeSize(range);
    } else
        totalSize = getRangeSize(ranges);

    if (typeof(functions[name[0]][name[1]]) == 'number')
        functions[name[0]][name[1]] += totalSize;
    else
        functions[name[0]][name[1]] = totalSize;
}

fs.writeFileSync("./allFunctionSizes.json", JSON.stringify(functions, null, 4));