/*
 */
open LinkedList;
open Utils;

type uuid = string;
type puuid = string;

module type Tree = {
  type t =
    | Tree(uuid, puuid, Content.t, linkedList(t));
};

type t =
  | Tree(uuid, puuid, Content.t, linkedList(t));

let treeEmpty = uuid => Tree(uuid, "_", Content.empty, LinkedList.empty);

let tree = (uuid, puuid, content, linkedList) => Tree(uuid, puuid, content, linkedList);

let getUuid =
  fun
  | Tree(uuid, _, _, _) => uuid;

let byUuid = (uuid, tree) => getUuid(tree) == uuid;

/* let add = (source, target) => {
     switch (target) {
     | Tree(uuid, puuid, content, linkedList) => Tree(uuid, puuid, content, insert(source, linkedList))
     };
   }; */

let update = (source, target) => {
  switch (target) {
  | Tree(targetUuid, puuid, content, linkedList) =>
    /* Add parents uuid (puuid) to child */
    let source =
      switch (source) {
      | Tree(uuid, _, content, linkedList) => tree(uuid, targetUuid, content, linkedList)
      };

    let linkedList = removeBy(byUuid(getUuid(source)), linkedList);
    let linkedList = insert(source, linkedList);
    Tree(targetUuid, puuid, content, linkedList);
  };
};

let delete = (source, target) => {
  switch (target) {
  | Tree(uuid, puuid, content, linkedList) =>
    let linkedList = removeBy(byUuid(getUuid(source)), linkedList);
    Tree(uuid, puuid, content, linkedList);
  };
};

let rec traverse = (fn, level, tree) =>
  switch (tree) {
  | Tree(uuid, puuid, _, roots) when LinkedList.isEmpty(roots) => fn(level, uuid, puuid, roots)
  | Tree(uuid, puuid, _, roots) =>
    fn(level, uuid, puuid, roots);
    LinkedList.iter(traverse(fn, level + 1), roots);
  };

let printFn = (level, uuid, puuid, branches) => {
  let d = 4; /* nof spaces */
  let len = Array.length(toArray(branches));
  let rootsString =
    switch (len) {
    | 0 => "_"
    | _ => "[" ++ string_of_array(",", Array.map(a => getUuid(a), toArray(branches))) ++ "]"
    };
  Js.log(fmtLevel(level, d, "(" ++ uuid ++ "," ++ puuid ++ "," ++ rootsString ++ ")"));
};

let printTree = tree => traverse(printFn, 0, tree);