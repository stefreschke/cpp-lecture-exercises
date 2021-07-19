
// Include pre-build node.js module
var process = undefined;

for (var i = 0; i <= 100; i++)
{
    var result = process(i);
    console.log("Call with", i, "results in", result);
}
