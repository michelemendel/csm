/*
 */
open LinkedList;
open Utils;

type uuid = string;

module type Tree = {
  type t =
    | Tree(uuid, t, Content.t, linkedList(t));
};

type t =
  | Empty
  | Tree(uuid, t, Content.t, linkedList(t));

let treeEmpty = uuid => Tree(uuid, Empty, Content.empty, LinkedList.empty);

/*
 Legend
 u, uuid - universally unique identifier
 p - parent
 c, content - Here will be stuff
 ls, linkedList - The children of a node in the tree
 */

let tree = (u, p, c, ls) => Tree(u, p, c, ls);

let getUuid =
  fun
  | Empty => ""
  | Tree(u, _, _, _) => u;

let getPUuid =
  fun
  | Empty => ""
  | Tree(_, p, _, _) => getUuid(p);

let byUuid = (u, tree) => getUuid(tree) == u;

let string_of_children = ls => string_of_array(",", Array.map(a => getUuid(a), toArray(ls)));
let log = s => Js.log("\n---" ++ s);

let add = (source, target) =>
  switch (target) {
  | Empty => Empty
  | Tree(targetU, p, c, ls) =>
    /* Add parent to child */
    let source =
      switch (source) {
      | Empty => Empty
      | Tree(u, _, c, ls) => tree(u, target, c, ls)
      };
    let ls = insert(source, ls);
    Tree(targetU, p, c, ls);
  };

let delete = (source, target) =>
  switch (target) {
  | Empty => Empty
  | Tree(u, p, c, ls) =>
    let ls = removeBy(byUuid(getUuid(source)), ls);
    Tree(u, p, c, ls);
  };

let update = (source, target) => add(source, delete(source, target));

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
  | Tree(u, newTarget, _, ls) =>
    Js.log("---u,nS,nT " ++ u ++ "," ++ getUuid(newSource) ++ "," ++ getUuid(newTarget))
  /* tatw(newSource, newTarget); */
  };

  Empty;
};

/* let updateX = (source, target) => {
     switch (target) {
     | Empty => Empty
     | Tree(targetU, p, c, ls) =>
       /* Add parent to child */
       let source =
         switch (source) {
         | Empty => Empty
         | Tree(u, _, c, ls) => tree(u, target, c, ls)
         };

       let ls = removeBy(byUuid(getUuid(source)), ls);
       let ls = insert(source, ls);
       Tree(targetU, p, c, ls);
     };
   }; */

let rec traverse = (fn, level, tree) =>
  switch (tree) {
  | Empty => fn(level, "-", Empty, LinkedList.Empty)
  | Tree(u, p, _, ls) when LinkedList.isEmpty(ls) => fn(level, u, p, ls)
  | Tree(u, p, _, ls) =>
    fn(level, u, p, ls);
    LinkedList.iter(traverse(fn, level + 1), ls);
  };

let printFn = (level, u, p, ls) => {
  let d = 4; /* nof spaces */
  let len = Array.length(toArray(ls));
  let rootsString =
    switch (len) {
    | 0 => "_"
    | _ => "[" ++ string_of_children(ls) ++ "]"
    };
  Js.log(fmtLevel(level, d, "(" ++ u ++ "," ++ getUuid(p) ++ "," ++ rootsString ++ ")"));
};

let printTree = tree => traverse(printFn, 0, tree);

let rec findRec = (uuid: string, tree: t): t => {
  switch (tree) {
  | Empty =>
    log("Empty");
    Empty;
  | Tree(u, p, _, ls) =>
    log("Not empty: " ++ u ++ "=" ++ uuid ++ "->" ++ string_of_bool(u == uuid));
    log("tail: " ++ string_of_children(ls));
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

let rec findRecX = (uuid, ls: linkedList(t)): t => {
  /* Js.log("linkedlist: " ++ string_of_array(":", toArray(ls))); */
  switch (ls) {
  | Empty =>
    Js.log("--empty");
    Empty;
  | LL(h, t) =>
    printTree(h);
    Js.log2("h:uuid (" ++ getUuid(h) ++ ") == uuid(" ++ uuid ++ "): ", getUuid(h) == uuid);
    if (getUuid(h) == uuid) {
      Js.log("found it");
      h;
    } else {
      /*         switch(t){
                       | Empty => Empty
                       | Tree(u, p, c, ls) =>
                 Js.log("tail: " ++ string_of_array(",", toArray(ls))); */
      findRecX(
        uuid,
        Empty,
      );
    };
  };
};

let find = (node, root) => findRec(getUuid(node), root);
let findX = (node, root) => findRecX(getUuid(node), insert(root, LinkedList.Empty));