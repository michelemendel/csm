/*
 */
open LinkedList;
open LookupTable;
open Utils;

type uuid = string;

/*
 module type Node = {
   type t =
     | Empty
     | Node(uuid, t, Content.t, linkedList(t));
    make
    getUuid
    getPUuid
    attach
    remove
    update
    printTree
 };
   */

/*
 Legend
 u, uuid - universally unique identifier
 p - parent
 c, content - Here will be stuff
 ls, linkedList - The children of a node
 lt, lookupTable
 */

type t =
  | Empty
  | Node(uuid, t, Content.t, linkedList(t));

let makeTree = () => (
  Node("0", Empty, Content.empty, LinkedList.empty),
  LT.empty,
);

let treeEmpty = uuid => (
  Node(uuid, Empty, Content.empty, LinkedList.empty),
  LT.empty,
);

let node = (u, p, c, ls) => Node(u, p, c, ls);
let tree = (u, p, c, ls) => (Node(u, p, c, ls), LT.empty);

let getUuid =
  fun
  | Empty => ""
  | Node(u, _, _, _) => u;

let getPUuid =
  fun
  | Empty => ""
  | Node(_, p, _, _) => getUuid(p);

let byUuid = (u, node) => getUuid(node) == u;

let string_of_children = ls =>
  string_of_array(",", Array.map(a => getUuid(a), toArray(ls)));
let log = s => Js.log("\n---" ++ s);

let attachLocal = (source, target) =>
  switch (target) {
  | Empty => Empty
  | Node(targetU, p, c, ls) =>
    /* Add parent to child */
    let source =
      switch (source) {
      | Empty => Empty
      | Node(u, _, c, ls) => node(u, target, c, ls)
      };
    let ls = insert(source, ls);
    Node(targetU, p, c, ls);
  };

let removeLocal = (source, target) =>
  switch (target) {
  | Empty => Empty
  | Node(u, p, c, ls) =>
    let ls = removeBy(byUuid(getUuid(source)), ls);
    Node(u, p, c, ls);
  };

let updateLocal = (source, target) =>
  attachLocal(source, removeLocal(source, target));

let attach = (source, target) => (
  attachLocal(fst(source), fst(target)),
  LT.empty,
);

let remove = (source, target) => (
  removeLocal(fst(source), fst(target)),
  LT.empty,
);

/* Probably to update content */
let update = (source, target) => updateLocal(source, target);

/*
 Attach, remove, update requires changes to propagate up to root,
 and the root will be a new object.
 */
let tatwO = (source, target) => {
  let target = update(source, target);
  target;
};

let tatw = (source, target) => {
  let newSource = update(source, target);
  Js.log("---s,t " ++ getUuid(source) ++ "," ++ getUuid(target));
  Js.log("---sP,tP " ++ getPUuid(source) ++ "," ++ getPUuid(target));

  switch (target) {
  | Empty => Js.log("---EMPTY")
  /* target */
  | Node(u, newTarget, _, ls) =>
    Js.log(
      "---u,nS,nT "
      ++ u
      ++ ","
      ++ getUuid(newSource)
      ++ ","
      ++ getUuid(newTarget),
    )
  /* tatw(newSource, newTarget); */
  };

  Empty;
};

let rec printTreeRec = (fn, level, node) =>
  switch (node) {
  | Empty => fn(level, "-", Empty, LinkedList.Empty)
  | Node(u, p, _, ls) when LinkedList.isEmpty(ls) => fn(level, u, p, ls)
  | Node(u, p, _, ls) =>
    fn(level, u, p, ls);
    LinkedList.iter(printTreeRec(fn, level + 1), ls);
  };

let printFn = (level, u, p, ls) => {
  let d = 4; /* nof spaces */
  let len = Array.length(toArray(ls));
  let rootsString =
    switch (len) {
    | 0 => "_"
    | _ => "[" ++ string_of_children(ls) ++ "]"
    };
  Js.log(
    fmtLevel(
      level,
      d,
      "(" ++ u ++ "," ++ getUuid(p) ++ "," ++ rootsString ++ ")",
    ),
  );
};

let printTree = tree => printTreeRec(printFn, 0, fst(tree));

let rec findRec = (uuid: string, tree: t): t =>
  switch (tree) {
  | Empty =>
    log("Empty");
    Empty;
  | Node(u, p, _, ls) =>
    let thisIsTheNode = u == uuid;
    log(
      "Not empty: "
      ++ u
      ++ "="
      ++ uuid
      ++ "->"
      ++ string_of_bool(thisIsTheNode)
      ++ " ["
      ++ string_of_children(ls)
      ++ "]",
    );

    if (thisIsTheNode) {
      tree;
    } else {
      LinkedList.fold(
        (_acc, head) => {
          let _ = findRec(uuid, head);
          head;
        },
        Empty,
        ls,
      );
    };
  };

/* let rec findRecX = (uuid, ls: linkedList(t)): t =>
     /* Js.log("linkedlist: " ++ string_of_array(":", toArray(ls))); */
     switch (ls) {
     | Empty =>
       Js.log("--empty");
       Empty;
     | LL(h, t) =>
       printTree(h);
       Js.log2(
         "h:uuid (" ++ getUuid(h) ++ ") == uuid(" ++ uuid ++ "): ",
         getUuid(h) == uuid,
       );
       if (getUuid(h) == uuid) {
         Js.log("found it");
         h;
       } else {
         /*         switch(t){
                          | Empty => Empty
                          | Node(u, p, c, ls) =>
                    Js.log("tail: " ++ string_of_array(",", toArray(ls))); */
         findRecX(
           uuid,
           Empty,
         );
       };
     };

   let find = (node, root) => findRec(getUuid(node), root);
   let findX = (node, root) =>
     findRecX(getUuid(node), insert(root, LinkedList.Empty)); */