var stack3 = function (str) {

    var error = new Error(str);
    StackTrace.fromError(error).then(report).catch(function (err) { console.log(err.message); })

}

var stack2 = function (str) {
    stack3(str + 'om');
}

var stack1 = function () {

    console.log("stack1");
    stack2('bo');

}

var report = function (stackframes) {
    console.log(stackframes);
    StackTrace.report(stackframes, 'http://127.0.0.1:5525/stacktrace');
};

window.onerror = function (msg, file, line, col, error) {
    // msg, file, line, col,
    // callback is called with an Array[StackFrame]
    console.log(arguments);
    if (error) {
        StackTrace.fromError(error)
            .then(report);
    }
};

window.onload = function () {
    stack1();
}



function a() {
    console.log('a');
    console.log(this);
}
a.prototype.a = 'aaa';

function b() {
    console.log('b');
    console.log(this);
}

b.prototype.b = 'bbb';

function c() {
    console.log('c');
    console.log(this);
}
c.prototype.c = 'ccc';

function d() {
    console.log('d');
    console.log(this);
}
d.prototype.d = 'ddd';


var main = function () {
    a();
    setTimeout(b, 0);
    setTimeout(c, 0);
    d();
}

main();