/*
 Trying out trees
 */

open Tree;
open Content;

let log = s => Js.log("\n---" ++ s);

let runPart1 = () => {
  /* Predicate by tree UUID */
  /* let byUuid = (uuid, tree) => getUuid(tree) == uuid; */

  let root = treeEmpty("00");
  let tree01 = tree("01", Empty, Content({ntype: "ent", label: "content"}), LinkedList.empty);
  let tree02 = tree("02", Empty, Content.empty, LinkedList.empty);
  let tree03 = treeEmpty("03");
  let tree04 = treeEmpty("04");

  (root, tree01, tree02, tree03, tree04);
};

let runPartRemove = () => {
  log("PartRemove");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let root = root |> update(tree01) |> update(tree02);

  printTree(root);

  let root = delete(tree01, root);
  log("removed 01");
  printTree(root);
};

let runPart2 = () => {
  log("Part2");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let root = root |> update(tree01) |> update(tree02);

  printTree(root);
};

let runPart3 = () => {
  log("Part3");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let root = root |> update(tree01) |> update(tree02);
  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let root = update(tree01, root);

  printTree(root);
};

let runPart4 = () => {
  log("Part4");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  let root = root |> update(tree01) |> update(tree02);
  log("root");
  printTree(root);

  log("Update 01, 02 and 04, then update up to root -> root2");
  let tree01 = tree01 |> update(tree03) |> update(tree04);
  let tree05 = tree("05", Empty, Content.empty, LinkedList.empty);
  let tree02 = tree02 |> update(tree05);
  let tree06 = tree("06", Empty, Content.empty, LinkedList.empty);
  let tree04 = tree04 |> update(tree06);
  let tree01 = tree01 |> update(tree04);
  let root2 = root |> update(tree01) |> update(tree02);
  printTree(root2);

  log("Move 04 from 01 to 05, then update up to root -> root3");
  let tree01 = tree01 |> delete(tree04);
  let root3 = root2 |> update(tree01);
  let tree05 = tree05 |> update(tree04);
  let tree02 = tree02 |> update(tree05);
  let root3 = root3 |> update(tree02);
  printTree(root3);

  log("Looking again at root to see that it hasn't changed");
  printTree(root);

  log("Find 01 in root03");
  let t = find(tree05, root);
  /* printTree(root); */
  printTree(t);
};

let runPart5 = () => {
  log("Part5");
  let (root, tree01, tree02, tree03, tree04) = runPart1();

  log("Root with 01 and 02");
  let root = root |> add(tree01) |> add(tree02);
  printTree(root);

  log("Update 01, 02 and 04, then update up to root");
  let tree05 = tree("05", Empty, Content.empty, LinkedList.empty);
  let tree06 = tree("06", Empty, Content.empty, LinkedList.empty);
  ();
  /*
   let root2a = tatw(tree03, tree01);
   log(getUuid(tree01) ++ "::" ++ getPUuid(tree01));
   printTree(root2a);
   let root2a = tree01 |> tatw(tree03) |> tatw(tree04);
        printTree(root2a);
        let root2b = tree02 |> tatw(tree05);
        printTree(root2b);
        let root2c = tree04 |> tatw(tree06);
        printTree(root2c);
        log("Move 04 from 01 to 05, then update up to root");
        let root3a = tree01 |> delete(tree04);
        printTree(root3a);
        let root3b = tree05 |> update(tree04);
        printTree(root3b);
        let root3c = tree02 |> update(tree05);
        printTree(root3c);

        log("The original root");
        printTree(root);
        */
};

let run = () => {
  runPart4();
          /* runPart5(); */
};