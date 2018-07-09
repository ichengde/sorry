window.onerror = function(msg, file, line, col, error) {
	    // callback is called with an Array[StackFrame]
	StackTrace.fromError(error).then(function(stackframes){StackTrace.report(stackframes, 'http://127.0.0.1:5525/')});
};

throw new Error('test error');
