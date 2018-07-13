var report = function(stackframes) {
    console.log(stackframes);
    StackTrace.report(stackframes, 'http://127.0.0.1:5525/');
};

window.onerror = function(msg, file, line, col, error) {
    // msg, file, line, col,
    // callback is called with an Array[StackFrame]
    console.log(arguments);
    if (error) {
        StackTrace.fromError(error)
            .then(report);
    }
};

window.onload = function() {


    var error = new Error('BOOM!');
    var callback = function(stackframes) {
        var stringifiedStack = stackframes.map(function(sf) {
            return sf.toString();
        }).join('\n');
        console.log(stringifiedStack);
    };

    var errback = function(err) { console.log(err.message); };
    StackTrace.fromError(error).then(report).catch(errback)
}