/*
 Trying out linked list
 */

/* Strings */
let runLL2 = () => {
  open LinkedList;
  let t = insert("5", empty);
  let t = insert("15", t);
  let t = insert("2", t);
  Js.log2("to array: ", toArray(t));
  Js.log2("head: ", head(t));
  Js.log2("tail: ", tail(t) |> toArray);
  Js.log2("tail > head: ", tail(t) |> head);
  let t = insert("4", t);
  Js.log2("to array: ", toArray(t));
  let t = remove("5", t);
  Js.log2("head: ", head(t));
  Js.log2("tail > head: ", tail(t) |> head);
  Js.log2("contains 2", contains("2", t) === true);
  Js.log2("does not contain 5", contains("5", t) === false);
  Js.log2("to array: ", toArray(t));
  Js.log("iterate over the LinkedList: ");
  LinkedList.iter(a => Js.log2("Content value: ", a), t);
  Js.log2("is empty?", isEmpty(t));
  let t = map(a => a ++ "1", t);
  Js.log2("head: ", head(t));
  Js.log2("tail > head: ", tail(t) |> head);
  Js.log2("size: ", size(t));
  Js.log2("to array: ", toArray(t));
  let res = fold((acc, a) => acc ++ a, "", t);
  Js.log2("fold: sum == " ++ res, res === "1512141");
};