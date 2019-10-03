/*
 Trying out trees
 */

/* open Content; */
open Tree;
open LookupTable;
open Printf;

let log = s => Js.log("\n---" ++ s);

let runPart1 = () => {
  let tree = makeTree();
  let node01 = nodeEmpty("01");
  let node02 = nodeEmpty("02");
  let node03 = nodeEmpty("03");
  let node04 = nodeEmpty("04");

  (tree, node01, node02, node03, node04);
};

let runPart3 = () => {
  log("Part3");
  let (tree, node01, node02, node03, node04) = runPart1();

  /* let root = root |> attach(node01) |> attach(node02);
      let node01 = node01 |> attach(node03) |> attach(node04);
      let root = attach(node01, root);
     */
  let tree = tree @@ (node01, root) @@ (node02, root);
  let tree = tree @@ (node01, node03) @@ (node01, node04);
  let tree = tree @@ (node01, tree);

  printTree(tree);
};

let runPart4 = () => {
  log("Part4");
  let (tree, node01, node02, node03, node04) = runPart1();

  let tree = tree |> attach(node01) |> attach(node02);
  log("tree");
  printTree(tree);

  log("Update 01, 02 and 04, then update up to tree -> root2");
  let node05 = node("05", Empty, Content.empty, LinkedList.empty);
  let node06 = node("06", Empty, Content.empty, LinkedList.empty);

  let node01 = node01 |> attach(node03) |> attach(node04);
  let node02 = node02 |> attach(node05);
  let node04 = node04 |> attach(node06);
  let node01 = node01 |> update(node04);

  let root2 = tree |> update(node01) |> update(node02);
  printTree(root2);

  log("Move 04 from 01 to 05, then update up to tree -> root3");
  let node01 = node01 |> remove(node04);
  let root3 = root2 |> attach(node01);
  let node05 = node05 |> update(node04);
  let node02 = node02 |> update(node05);
  let root3 = root3 |> update(node02);
  printTree(root3);

  log("Looking again at tree to see that it hasn't changed");
  printTree(tree);
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
  let node03 = nodeEmpty("03");
  let node04 = nodeEmpty("04");
  let lt = addLT("03", node03, lt);
  let lt = addLT("04", node04, lt);

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

let run = () => runPart4();
/* runPart5(); */