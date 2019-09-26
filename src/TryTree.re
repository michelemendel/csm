/*
 Trying out trees
 */

open Tree;
open Content;

let runPart1 = () => {
  /* Predicate by tree UUID */
  /* let byUuid = (uuid, tree) => getUuid(tree) == uuid; */

  let root = treeEmpty("00");
  let tree01 = tree("01", "", Content({ntype: "ent", label: "content"}), LinkedList.empty);
  let tree02 = tree("02", "", Content.empty, LinkedList.empty);
  let tree03 = treeEmpty("03");
  let tree04 = treeEmpty("04");

  (root, tree01, tree02, tree03, tree04);
};

let runPartRemove = () => {
  Js.log("\n-----PartRemove");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let root = root |> update(tree01) |> update(tree02);

  printTree(root);

  let root = delete(tree01, root);
  Js.log("\n-----removed 01");
  printTree(root);
};

let runPart2 = () => {
  Js.log("\n-----Part2");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let root = root |> update(tree01) |> update(tree02);

  printTree(root);
};

let runPart3 = () => {
  Js.log("\n-----Part3");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let root = root |> update(tree01) |> update(tree02);
  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let root = update(tree01, root);

  printTree(root);
};

let runPart4 = () => {
  Js.log("\n-----Part4");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let root = root |> update(tree01) |> update(tree02);
  Js.log("\n-----root");
  printTree(root);

  /* Update 01, 02 and 04, then update up to root  */
  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let tree05 = tree("05", "", Content.empty, LinkedList.empty);
  let tree02 = tree02 |> update(tree05);
  let tree06 = tree("06", "", Content.empty, LinkedList.empty);
  let tree04 = tree04 |> update(tree06);
  let tree01 = tree01 |> update(tree04);
  let root2 = root |> update(tree01) |> update(tree02);
  Js.log("\n-----root2");

  printTree(root2);
  /* Move 04 from 01 to 05, then update up to root */
  let tree01 = tree01 |> delete(tree04);
  let root3 = root2 |> update(tree01);
  let tree05 = tree05 |> update(tree04);
  let tree02 = tree02 |> update(tree05);
  let root3 = root3 |> update(tree02);
  Js.log("\n-----root3");
  printTree(root3);

  Js.log("\n-----root");
  printTree(root);
};