import createModule from "./diff.js";

const toCString = (str) => {
  const len = Module.lengthBytesUTF8(str) + 1;
  const ptr = Module._malloc(len);
  Module.stringToUTF8(str, ptr, len);
  return ptr;
};

const Module = await createModule();

export const diff = (A, B) => {
  const aPtr = toCString(A);
  const bPtr = toCString(B);

  const diffStrPtr = Module._diff(aPtr, bPtr, A.length, B.length);

  const diffStr = Module.UTF8ToString(diffStrPtr);
  const diff = JSON.parse(diffStr);

  Module._free(aPtr);
  Module._free(bPtr);
  Module._free(diffStrPtr);

  return diff;
};
