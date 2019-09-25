type nodeType =
  | Entity
  | Collection
  | Property;

/* module type Node = {
     type t;
     type nodeKV = {uuid: string};
     type node('t) =
       | Node('t);
     let make: nodeKV => node(nodeKV);
   };
    */

type t = {ntype: string};

type node('a) =
  | Node('a);

let empty = () => {ntype: "-"};

/* let make = nodeKV => Node(nodeKV); */