window.onerror = function(msg, file, line, col, error) {
	    // callback is called with an Array[StackFrame]
	StackTrace.fromError(error).then(function(stackframes){StackTrace.report(stackframes, 'http://193.112.22.19:8080/')}); 
};

throw new Error('test error');
