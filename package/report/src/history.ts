class Dep {
    id = null;
    subs = [];
    static watch: any;

    constructor() {
        this.id = new Date()
    }
    defined() {
        Dep.watch.add(this);
    }
    notify() {
        this.subs.forEach((e) => {
            if (typeof e.update === 'function') {
                try {
                    e.update.apply(e)
                } catch (err) {
                    console.warn(err)
                }
            }
        })
    }

}

class Watch {

    name = null;
    id = new Date();
    callBack = null;

    constructor(name, fn) {
        this.name = name;
        this.id = new Date();
        this.callBack = fn;
    }
    add(dep) {
        dep.subs.push(this);
    }
    update() {
        var cb = this.callBack;
        cb(this.name);
    }
}

var addHistoryMethod = (function () {
    var historyDep = new Dep();
    return function (name) {
        if (name === 'historychange') {
            return function (name, fn) {
                var event = new Watch(name, fn)
                Dep.watch = event;
                historyDep.defined();
                Dep.watch = null;
            }
        } else if (name === 'pushState' || name === 'replaceState') {
            var method = history[name];
            return function () {
                method.apply(history, arguments);
                historyDep.notify();
            }
        }

    }
}())


history.pushState = addHistoryMethod('pushState');
history.replaceState = addHistoryMethod('replaceState');
const addHistoryListener = addHistoryMethod('historychange');


export const historyWatch = function (e) {
    addHistoryListener('hashchange', e)
    window.addEventListener("hashchange", e)
}
