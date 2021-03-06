// rule 110 implementation on wip-lang
// https://en.wikipedia.org/wiki/Rule_110

import "./helpers.wip"

const size = 64;

var arr1: *int = allocate(size * 8);
var arr2: *int = allocate(size * 8);

var i = 0;

while i < size {
  *(arr1 + i) = 0;
  ++i;
}
*(arr1 + size - 1) = 1;

print("\nRule 110:\n");

var j = size;
while j-- {
  drawLine(arr1, size);
  processLine(arr1, arr2, size);

  const tmpArr = arr1;
  arr1 = arr2;
  arr2 = tmpArr;
}
