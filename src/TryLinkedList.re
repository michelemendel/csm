/*
 Trying out linked list
 */

/* Nodes */
/* let runLL1 = () => {
     open LinkedList;

     /* let byUuid = (uuid, node: Node.t) => node.uuid == uuid; */

     let emptyNode = Node.empty();

     let root0 = Node.empty();
     let n2: Node.t = {uuid: "n2"};
     let n15: Node.t = {uuid: "n15"};
     let n4: Node.t = {uuid: "n4"};

     let t = insert(n5, empty);
     let t = insert(n15, t);
     let t = insert(n2, t);
     Js.log2("to array: ", toArray(t));
     Js.log2("head: ", head(t));
     Js.log2("tail: ", tail(t) |> toArray);
     Js.log2("tail > head: ", t |> tail |> head);
     let t = insert(n4, t);
     Js.log2("to array: ", toArray(t));
     let t = remove(n15, t);
     Js.log2("removed 15: ", toArray(t));
     let t = insert(n15, t);
     Js.log2("inserted 15: ", toArray(t));

     /*   let t = removeBy(byUuid("n15"), t);
           Js.log2("removed by uuid n15: ", toArray(t));
           Js.log("");
          */
     Js.log2("head: ", head(t));
     Js.log2("tail > head: ", t |> tail |> head);
     Js.log2("contains 2", contains(n2, t) === true);
     Js.log2("does not contain 5", contains(n5, t) === false);
     Js.log2("to array: ", t |> toArray);
     Js.log("iterate over the LinkedList: ");
     LinkedList.iter(a => Js.log2("Node value: ", a), t);
     Js.log2("is empty?", isEmpty(t));
     Js.log2("tail > head: ", tail(t) |> head);
     Js.log2("size: ", size(t));
     Js.log2("to array: ", toArray(t));
   };
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
  LinkedList.iter(a => Js.log2("Node value: ", a), t);
  Js.log2("is empty?", isEmpty(t));
  let t = map(a => a ++ "1", t);
  Js.log2("head: ", head(t));
  Js.log2("tail > head: ", tail(t) |> head);
  Js.log2("size: ", size(t));
  Js.log2("to array: ", toArray(t));
  let res = fold((acc, a) => acc ++ a, "", t);
  Js.log2("fold: sum == " ++ res, res === "1512141");
};