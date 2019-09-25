/*
 */
open LinkedList;
open Node;

type uuid = string;

module type Tree = {
  type t =
    | Tree(uuid, Node.t, linkedList(t));
};

type t =
  | Tree(uuid, Node.t, linkedList(t));

let treeEmpty = uuid => Tree(uuid, Node.empty, LinkedList.empty);

let tree = (uuid, node, linkedList) => Tree(uuid, node, linkedList);

let add = (root, tree) => {
  switch (tree) {
  | Tree(uuid, node, linkedList) => Tree(uuid, node, LinkedList.insert(root, linkedList))
  };
};

let addx = (root, tree) => {
  switch (tree) {
  | Tree(_, _, linkedList) =>
    let _ = LinkedList.insert(root, linkedList);
    ();
  };
};

let getUuid =
  fun
  | Tree(uuid, _, _) => uuid;

let rec walk = tree =>
  switch (tree) {
  | Tree(uuid, _, roots) when LinkedList.isEmpty(roots) => Js.log("LEAF: " ++ uuid ++ "\n")
  | Tree(uuid, _, roots) =>
    Js.log3("NODE: " ++ uuid, Array.map(a => getUuid(a), toArray(roots)), "\n");
    LinkedList.iter(walk, roots);
  };