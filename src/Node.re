type nodeType =
  | Entity
  | Collection
  | Property;

type nodeKV = {
  ntype: string,
  label: string,
};

module type Node = {
  type t;
  type node('t) =
    | Node('t);
  let make: nodeKV => node(nodeKV);
};

type t =
  | Node(nodeKV);

let empty = Node({ntype: "", label: ""});

let make = nodeKV => Node(nodeKV);