/*
 Trying out trees
 */

open Content;
open Tree;
open LookupTable;
open Printf;

let log = s => Js.log("\n---" ++ s);

let runPart1 = () => {
  /* Predicate by tree UUID */
  /* let byUuid = (uuid, tree) => getUuid(tree) == uuid; */

  let root = makeTree();

  let tree01 = treeEmpty("01");
  let tree02 = treeEmpty("02");
  let tree03 = treeEmpty("03");
  let tree04 = treeEmpty("04");

  (root, tree01, tree02, tree03, tree04);
};

let runPart3 = () => {
  log("Part3");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let root = root |> attach(tree01) |> attach(tree02);
  let tree01 = tree01 |> attach(tree03) |> attach(tree04);
  let root = attach(tree01, root);

  printTree(root);
};

let runPart4 = () => {
  log("Part4");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let root = root |> attach(tree01) |> attach(tree02);
  log("root");
  printTree(root);

  log("Update 01, 02 and 04, then update up to root -> root2");
  let tree01 = tree01 |> attach(tree03) |> attach(tree04);
  let tree05 = tree("05", Empty, Content.empty, LinkedList.empty);
  let tree02 = tree02 |> attach(tree05);
  let tree06 = tree("06", Empty, Content.empty, LinkedList.empty);
  let tree04 = tree04 |> attach(tree06);
  let tree01 = tree01 |> attach(tree04);
  let root2 = root |> attach(tree01) |> attach(tree02);
  printTree(root2);

  log("Move 04 from 01 to 05, then update up to root -> root3");
  let tree01 = tree01 |> remove(tree04);
  let root3 = root2 |> attach(tree01);
  let tree05 = tree05 |> attach(tree04);
  let tree02 = tree02 |> attach(tree05);
  let root3 = root3 |> attach(tree02);
  printTree(root3);

  log("Looking again at root to see that it hasn't changed");
  printTree(root);
};

let logOp = (uuid, lt) =>
  switch (getLT(uuid, lt)) {
  | None => log(uuid ++ " doesn't exists")
  | Some(node) => log(getUuid(fst(node)))
  };

let print = lt =>
  LT.iter(
    (uuid, node) =>
      print_endline(sprintf("%s %s", uuid, getUuid(fst(node)))),
    lt,
  );

let runPart5 = () => {
  let lt = makeLT();
  let tree03 = treeEmpty("03");
  let tree04 = treeEmpty("04");
  let lt = addLT("03", tree03, lt);
  let lt = addLT("04", tree04, lt);

  print(lt);

  logOp("03", lt);
  /* log(getUuid(get("03", lt))); */
  log(string_of_bool(existsLT("03", lt)));
  log(string_of_int(lenLT(lt)));

  let lt = removeLT("03", lt);

  print(lt);
  logOp("03", lt);
  /* log(getUuid(get("03", lt))); */
  log(string_of_bool(existsLT("03", lt)));
  log(string_of_int(lenLT(lt)));
};

let run = () =>
  /* runPart4(); */
  runPart5();