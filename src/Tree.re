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
 l, linkedList - The children of a node in the tree
 */

let tree = (u, p, c, l) => Tree(u, p, c, l);

let getUuid =
  fun
  | Empty => ""
  | Tree(u, _, _, _) => u;

let getPUuid =
  fun
  | Empty => ""
  | Tree(_, p, _, _) => getUuid(p);

let byUuid = (u, tree) => getUuid(tree) == u;

let add = (source, target) =>
  switch (target) {
  | Empty => Empty
  | Tree(targetU, p, c, l) =>
    /* Add parent to child */
    let source =
      switch (source) {
      | Empty => Empty
      | Tree(u, _, c, l) => tree(u, target, c, l)
      };
    let l = insert(source, l);
    Tree(targetU, p, c, l);
  };

let delete = (source, target) =>
  switch (target) {
  | Empty => Empty
  | Tree(u, p, c, l) =>
    let l = removeBy(byUuid(getUuid(source)), l);
    Tree(u, p, c, l);
  };

let update = (source, target) => add(source, delete(source, target));

let tatwO = (source, target) => {
  let target = update(source, target);
  target;
};

let rec findRec = (uuid, node) =>
  switch (node) {
  | Empty => Empty
  | Tree(u, _, _, l) =>
    if (uuid == u) {
      node;
    } else {
      LinkedList.fold(findRec(uuid), Empty, l);
    }
  };

let find = (node, tree) => findRec(getUuid(node), tree);

let tatw = (source, target) => {
  let newSource = update(source, target);
  Js.log("---s,t " ++ getUuid(source) ++ "," ++ getUuid(target));
  Js.log("---sP,tP " ++ getPUuid(source) ++ "," ++ getPUuid(target));

  switch (target) {
  | Empty => Js.log("---EMPTY")
  /* target */
  | Tree(u, newTarget, _, l) =>
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

/* let updateX = (source, target) => {
     switch (target) {
     | Empty => Empty
     | Tree(targetU, p, c, l) =>
       /* Add parent to child */
       let source =
         switch (source) {
         | Empty => Empty
         | Tree(u, _, c, l) => tree(u, target, c, l)
         };

       let l = removeBy(byUuid(getUuid(source)), l);
       let l = insert(source, l);
       Tree(targetU, p, c, l);
     };
   }; */

let rec traverse = (fn, level, tree) =>
  switch (tree) {
  | Empty => fn(level, "-", Empty, LinkedList.Empty)
  | Tree(u, p, _, l) when LinkedList.isEmpty(l) => fn(level, u, p, l)
  | Tree(u, p, _, l) =>
    fn(level, u, p, l);
    LinkedList.iter(traverse(fn, level + 1), l);
  };

let printFn = (level, u, p, l) => {
  let d = 4; /* nof spaces */
  let len = Array.length(toArray(l));
  let rootsString =
    switch (len) {
    | 0 => "_"
    | _ =>
      "["
      ++ string_of_array(",", Array.map(a => getUuid(a), toArray(l)))
      ++ "]"
    };
  Js.log(
    fmtLevel(
      level,
      d,
      "(" ++ u ++ "," ++ getUuid(p) ++ "," ++ rootsString ++ ")",
    ),
  );
};

let printTree = tree => traverse(printFn, 0, tree);