import { diff } from "../dist/index.js";

self.postMessage({ ready: true });

self.onmessage = (e) => {
  const { textA, textB } = e.data;
  const result = diff(textA, textB);
  self.postMessage({ result });
};
