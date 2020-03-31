<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
    <p>
      For a guide and recipes on how to configure / customize this project,<br />
      check out the
      <a href="https://cli.vuejs.org" target="_blank" rel="noopener"
        >vue-cli documentation</a
      >.
    </p>
    <h3>Installed CLI Plugins</h3>
    <ul>
      <li>
        <a
          href="https://github.com/vuejs/vue-cli/tree/dev/packages/%40vue/cli-plugin-babel"
          target="_blank"
          rel="noopener"
          >babel</a
        >
      </li>
      <li>
        <a
          href="https://github.com/vuejs/vue-cli/tree/dev/packages/%40vue/cli-plugin-eslint"
          target="_blank"
          rel="noopener"
          >eslint</a
        >
      </li>
    </ul>
    <h3>Essential Links</h3>
    <ul>
      <li>
        <a href="https://vuejs.org" target="_blank" rel="noopener">Core Docs</a>
      </li>
      <li>
        <a href="https://forum.vuejs.org" target="_blank" rel="noopener"
          >Forum</a
        >
      </li>
      <li>
        <a href="https://chat.vuejs.org" target="_blank" rel="noopener"
          >Community Chat</a
        >
      </li>
      <li>
        <a href="https://twitter.com/vuejs" target="_blank" rel="noopener"
          >Twitter</a
        >
      </li>
      <li>
        <a href="https://news.vuejs.org" target="_blank" rel="noopener">News</a>
      </li>
    </ul>
    <h3>Ecosystem</h3>
    <ul>
      <li>
        <a href="https://router.vuejs.org" target="_blank" rel="noopener"
          >vue-router</a
        >
      </li>
      <li>
        <a href="https://vuex.vuejs.org" target="_blank" rel="noopener">vuex</a>
      </li>
      <li>
        <a
          href="https://github.com/vuejs/vue-devtools#vue-devtools"
          target="_blank"
          rel="noopener"
          >vue-devtools</a
        >
      </li>
      <li>
        <a href="https://vue-loader.vuejs.org" target="_blank" rel="noopener"
          >vue-loader</a
        >
      </li>
      <li>
        <a
          href="https://github.com/vuejs/awesome-vue"
          target="_blank"
          rel="noopener"
          >awesome-vue</a
        >
      </li>
    </ul>
  </div>
</template>

<script>
export default {
  name: "HelloWorld",
  props: {
    msg: String
  },
  mounted: function() {
    this.initial();
  },
  methods: {
    initial() {
      let request = window.indexedDB.open("QuizQuestDatabase", 1);

      request.onerror = function(e) {
        console.log("request.onerror", e);
      };

      request.onsuccess = function(e) {
        console.log("request.onsuccess", e);

        const db = request.result;
        const tx = db.transaction("QuestionStore", "readwrite");
        const store = tx.objectStore("QuestionStore");
        const index = store.index("questionText");

        db.onerror = function(e) {
          console.log("db.onerror", e);
        };

        const q1 = store.get(1);
        const qs = index.get("The grass is green.");

        q1.onsuccess = function() {
          console.log("q1.onsuccess", q1.result);
        };

        qs.onsuccess = function() {
          console.log("qs.onsuccess", qs.result);
        };

        const allKey = store.getAllKeys();
        allKey.onsuccess = function(e) {
          console.log("all.key.onsuccess.e", e);
          console.log("all.key.onsuccess.result", allKey.result);
        };

        // store.put({
        //   qID: 1,
        //   questionText: "The sky is blue.",
        //   result: true
        // });

        // store.put({
        //   qID: 2,
        //   questionText: "The grass is green.",
        //   result: true
        // });

        tx.oncomplete = function() {
          db.close();
        };
      };

      request.onupgradeneeded = function(e) {
        console.log("request.onupgradeneeded", e);

        const db = request.result;
        const store = db.createObjectStore("QuestionStore", { keyPath: "qID" });
        const index = store.createIndex("questionText", "questionText", {
          unique: false
        });

        if (index) {
          console.log(index);
        }
      };
    }
  }
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>
