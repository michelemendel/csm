/*
 Trying out trees
 */

open LinkedList;
open Tree;
open Node;

let runT1 = () => {
  /* Predicate by node UUID */
  let byUuid = (uuid, tree) => getUuid(tree) == uuid;

  let root0 = treeEmpty("00");
  let root01 = tree("01", Node({ntype: "ent", label: "node"}), LinkedList.empty);
  let root02 = tree("02", Node.empty, LinkedList.empty);
  let root03 = treeEmpty("03");

  let root0 = root0 |> add(root01) |> add(root02);
  addx(root03, root01);

  Js.log("Traverse 0");
  walk(root0);

  Js.log("Traverse 01");
  walk(root01);
};