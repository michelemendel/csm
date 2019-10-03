/*
 Trying out trees
 */

/* open Content; */
open Tree;
open LookupTable;
open Printf;

let log = s => Js.log("\n---" ++ s);

let runPart1 = () => {
  let root = makeRoot();
  let node01 = nodeEmpty("01");
  let node02 = nodeEmpty("02");
  let node03 = nodeEmpty("03");
  let node04 = nodeEmpty("04");

  (root, node01, node02, node03, node04);
};

let runPart3 = () => {
  log("Part3");
  let (root, node01, node02, node03, node04) = runPart1();

  let root = root |> attach(node01) |> attach(node02);
  let node01 = node01 |> attach(node03) |> attach(node04);
  let root = attach(node01, root);

  printTree(root);
};

let runPart4 = () => {
  log("Part4");
  let (root, node01, node02, node03, node04) = runPart1();

  let root = root |> attach(node01) |> attach(node02);
  log("root");
  printTree(root);

  log("Update 01, 02 and 04, then update up to root -> root2");
  let node01 = node01 |> attach(node03) |> attach(node04);
  let node05 = node("05", Empty, Content.empty, LinkedList.empty);
  let node02 = node02 |> attach(node05);
  let node06 = node("06", Empty, Content.empty, LinkedList.empty);
  let node04 = node04 |> attach(node06);
  let node01 = node01 |> attach(node04);
  let root2 = root |> attach(node01) |> attach(node02);
  printTree(root2);

  log("Move 04 from 01 to 05, then update up to root -> root3");
  let node01 = node01 |> remove(node04);
  let root3 = root2 |> attach(node01);
  let node05 = node05 |> attach(node04);
  let node02 = node02 |> attach(node05);
  let root3 = root3 |> attach(node02);
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
  LT.iter((uuid, node) => print_endline(sprintf("%s %s", uuid, getUuid(fst(node)))), lt);

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

let run = () =>
  /* runPart4(); */
  runPart5();