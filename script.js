const textA = document.getElementById("textA");
const textB = document.getElementById("textB");
const output = document.getElementById("output");
const diffBtn = document.getElementById("diffBtn");
const clearA = document.getElementById("clearA");
const clearB = document.getElementById("clearB");
const timerEl = document.getElementById("timer");
const realtimeCheckbox = document.getElementById("realtime");
const exampleFrankenstein = document.getElementById("exampleFrankenstein");
const exampleStranger = document.getElementById("exampleStranger");

const worker = new Worker("worker.js", { type: "module" });

function autoResize(textarea) {
  textarea.style.height = "auto";
  textarea.style.height = textarea.scrollHeight + "px";
}

let timerInterval = null;
let startTime = 0;

function renderResult(result) {
  output.innerHTML = "";
  for (const { type, value } of result) {
    const span = document.createElement("span");
    span.textContent = value;
    if (type === 1) span.className = "add";
    else if (type === -1) span.className = "del";
    output.appendChild(span);
  }
}

function startTimer() {
  clearInterval(timerInterval);
  startTime = performance.now();
  timerInterval = setInterval(() => {
    timerEl.textContent =
      ((performance.now() - startTime) / 1000).toFixed(3) + "s";
  }, 10);
}

function stopTimer() {
  clearInterval(timerInterval);
  timerEl.textContent =
    ((performance.now() - startTime) / 1000).toFixed(3) + "s";
}

function runDiff() {
  startTimer();
  worker.postMessage({ textA: textA.value, textB: textB.value });
}

worker.onmessage = (e) => {
  if (e.data.ready) {
    runDiff();
  } else if (e.data.result) {
    stopTimer();
    renderResult(e.data.result);
  }
};

diffBtn.addEventListener("click", runDiff);

textA.addEventListener("input", () => {
  autoResize(textA);
  if (realtimeCheckbox.checked) runDiff();
});

textB.addEventListener("input", () => {
  autoResize(textB);
  if (realtimeCheckbox.checked) runDiff();
});

clearA.addEventListener("click", () => {
  textA.value = "";
  autoResize(textA);
  if (realtimeCheckbox.checked) runDiff();
});

clearB.addEventListener("click", () => {
  textB.value = "";
  autoResize(textB);
  if (realtimeCheckbox.checked) runDiff();
});

async function loadExample(fileA, fileB) {
  const [contentA, contentB] = await Promise.all([
    fetch(fileA).then((r) => r.text()),
    fetch(fileB).then((r) => r.text()),
  ]);
  textA.value = contentA;
  textB.value = contentB;
  autoResize(textA);
  autoResize(textB);
  runDiff();
}

exampleFrankenstein.addEventListener("click", () => {
  loadExample(
    "examples/frankenstein/1818.txt",
    "examples/frankenstein/1831.txt"
  );
});

exampleStranger.addEventListener("click", () => {
  loadExample("examples/stranger/ward.txt", "examples/stranger/gilbert.txt");
});

autoResize(textA);
autoResize(textB);
setTimeout(() => textA.focus(), 100);
