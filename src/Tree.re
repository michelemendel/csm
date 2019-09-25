/*
 */
open LinkedList;

type uuid = string;

module type Tree = {
  type t =
    | Tree(uuid, Node.t, linkedList(t));
  /* let root: (string) => tree(n); */
};

type t =
  | Tree(uuid, Node.t, linkedList(t));

let root = uuid => Tree(uuid, Node.empty(), LinkedList.empty);

let uuid = tree => {
  let Tree(uuid, _, _) = tree;
  uuid;
};

/* let rec walk = (fn, tree) =>
   switch (tree) {
   | Leaf(id) => fn(id)
   | Tree(id, children) => {
       List.map(walk(fn), children)}
   }; */