"use strict";

var requiredTools = ["python", "make"];

requiredTools.forEach(function (tool) {
    try {
        require("child_process").execSync(`${tool} --version`);
    } catch (err) {
        console.error(
            `Error: ${tool} is required to build this package, but it's not installed.`
        );
        process.exit(1);
    }
});
