define(["require"], function(require) {
  "use strict";
  function classA() {
    this.func1 = function() {
      console.log("classA.func1 inner");
    };
  }

  classA.prototype.func1 = function() {
    console.log("classA.func2 outter");
  };

  return classA;
});
