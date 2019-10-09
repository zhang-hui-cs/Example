define(["require", "class-a"], function(require, classA) {
  "use strict";
  const targetDiv = document.getElementById("targetCanvas");
  if (targetDiv !== null) {
    targetDiv.tabIndex = 0;
    targetDiv.addEventListener("keydown", event =>
      console.log("keyDown fired")
    );
  }
});
